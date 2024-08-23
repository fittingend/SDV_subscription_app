#include <regex>
#include <boost/filesystem.hpp>  // boost::filesystem::exists boost::filesystem::create_directory

#include "apd/rest/serialize/serialize.h"
#include "apd/rest/uri.h"
#include "apd/rest/ogm/copy.h"

#include "hawkbit_client.h"
#include "json_helper.h"
#include <iomanip>

using namespace apd::rest;
using namespace eevp::ucm::ota;
using namespace ara::ucm::vehpkgmgr::proxy;

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

HawkbitClient::HawkbitClient(VehiclePackageManagementApp<VehiclePackageManagementProxy>& app)
    : sleepTime_(std::chrono::seconds(1))
    , restClient_("OTA_REST_CLIENT_HAWKBIT")
    , logger_(CreateLogger("OHBC", "Hawkbit Client Logger", ara::log::LogLevel::kVerbose))
    , serviceApp_(app)
{
    logger_.LogInfo() << "Initialize HawkbitClient";
}

bool HawkbitClient::Init(const ConfigClass& config)
{
    HawkbitInit(config);

    if (!boost::filesystem::exists(config_->downloadLocation)) {
        boost::filesystem::create_directories(config_->downloadLocation);
    }

    return true;
}

bool HawkbitClient::StartServiceSync()
{
    HawkbitStartServiceSync();
    return true;
}

bool HawkbitClient::GetBinary(const apd::rest::Uri& downloadUrl, const String& file, String& checkSum, int& httpCode)
{
    // logger_.LogInfo() << "Get " << downloadUrl.GetPath().GetAsString() << " / " << file;

    Pointer<Request> serverRequest = std::make_unique<Request>(RequestMethod::kGet, downloadUrl);

    FILE* fp = fopen(file.c_str(), "wb");
    if (fp == nullptr) {
        // logger_.LogError() << "Failed to open file for download: " << file;
        return false;
    }
    boost::uuids::detail::sha1 sha;

    // Setup request headers
    RequestHeader& header = serverRequest->GetHeader();
    header.SetField("Accept", "application/octet-stream");

    if (!(config_->authToken).empty()) {
        header.SetField("Authorization", "TargetToken " + config_->authToken);
    } else if (!(config_->gatewayToken).empty()) {
        header.SetField("Authorization", "GatewayToken " + config_->authToken);
    }

    // perform request
    auto task = restClient_.Send(*serverRequest);
    Pointer<Reply> rep = task.get();
    auto& responseHeader = rep->GetHeader();

    const auto& data = rep->ReleaseBinary().get();

    httpCode = responseHeader.GetStatus();

    if (httpCode == 200) {
        logger_.LogInfo() << "Download complete, binary data of length: " << data->size();
        // Checksum
        sha.process_bytes(data->c_str(), data->size());

        size_t count = 1;
        if (fwrite(data->c_str(), data->size(), count, fp) != count) {
            logger_.LogError() << "Writing to file failed!\n";
            fclose(fp);
            return false;
        }

        unsigned int digest[5];
        sha.get_digest(digest);
        std::stringstream ss;
        for (int i = 0; i < 5; ++i) {
            ss << std::setw(2 * 4) << std::setfill('0') << std::hex << digest[i];
        }
        ss >> checkSum;

    } else {
        logger_.LogError() << "HTTP request failed, Code: " << httpCode << "\n";
    }

    fclose(fp);
    return true;
}

int HawkbitClient::RestRequest(const apd::rest::RequestMethod& method,
    const apd::rest::Uri& url,
    bool request,
    apd::rest::Pointer<apd::rest::ogm::Object>& restRequest,
    bool response,
    apd::rest::Pointer<apd::rest::ogm::Object>& restResponse)
{
    int httpCode = 0;

    Pointer<Request> serverRequest = nullptr;

    if (request) {
        serverRequest = std::make_unique<Request>(method, url, std::move(restRequest));
    } else {
        serverRequest = std::make_unique<Request>(method, url);
    }

    RequestHeader& header = serverRequest->GetHeader();
    // Setup request headers
    header.SetField("Accept", "application/json;charset=UTF-8");

    if (!(config_->authToken).empty()) {
        header.SetField("Authorization", "TargetToken " + config_->authToken);
    } else if (!(config_->gatewayToken).empty()) {
        header.SetField("Authorization", "GatewayToken " + config_->authToken);
    }

    if (request) {
        header.SetField("Content-Type", "application/json;charset=UTF-8");
    }

    try {
        // perform request
        auto task = restClient_.Send(*serverRequest);
        Pointer<Reply> rep = task.get();
        auto& responseHeader = rep->GetHeader();

        httpCode = responseHeader.GetStatus();

        logger_.LogInfo() << "Status: " << httpCode;

        if (httpCode == 200) {
            if (response) {
                const auto& rootObj = rep->GetObject().get();
                restResponse = ogm::Copy(&rootObj);
            }
        } else {
            logger_.LogError() << "HTTP request failed: " << httpCode;
        }
    } catch (const std::exception& e) {
        logger_.LogError() << "HTTP request failed by throwing an exception: " << e.what();
    }

    return httpCode;
}

bool HawkbitClient::Feedback(const apd::rest::Uri& url,
    const String& id,
    const String& detail,
    const String& finished,
    const String& execution)
{
    Pointer<ogm::Object> restResponse = nullptr;
    Pointer<ogm::Object> restRequest = ogm::Object::Make();
    std::unordered_map<String, String> table;

    /*
    logger_.LogInfo() << "Feedback: " << url.GetPath().GetAsString()
                      << " " << id
                      << " " << detail
                      << " " << finished
                      << " " << execution;
    */

    JsonBuildStatus(restRequest, id, detail, finished, execution, table, 0);

    int status = RestRequest(RequestMethod::kPost, url, true, restRequest, false, restResponse);
    // logger_.LogInfo() << "Feedback status : " << status << "URL : " << url.GetPath().GetAsString();

    return (status == 200);
}

bool HawkbitClient::FeedbackProgress(const apd::rest::Uri& url, const String& id, int progress, const String& detail)
{
    Pointer<ogm::Object> restResponse = nullptr;
    Pointer<ogm::Object> restRequest = ogm::Object::Make();
    std::unordered_map<String, String> table;

    JsonBuildStatus(restRequest, id, detail, "none", "proceeding", table, progress);

    int status = RestRequest(RequestMethod::kPost, url, true, restRequest, false, restResponse);
    // logger_.LogInfo() << "Feedback progress status: " << status << " URL : " << url.GetPath().GetAsString();

    return (status == 200);
}

apd::rest::Uri HawkbitClient::BuildApiURL(const String& path)
{
    if (config_->ssl) {
        StringView element{"https://" + config_->hawkbitServer + path};
        return Uri(element);
    } else {
        StringView element{"http://" + config_->hawkbitServer + path};
        return Uri(element);
    }
}

bool HawkbitClient::HawkbitProgress(const String& msg)
{
    if (actionId_) {
        Uri feedbackURL = BuildApiURL(String("/" + config_->tenantId + "/controller/v1/" + config_->targetName
            + "/deploymentBase/" + *actionId_ + "/feedback"));

        FeedbackProgress(feedbackURL, *actionId_, 3, msg);
        return true;
    }
    return false;
}

bool HawkbitClient::Identify()
{
    Pointer<ogm::Object> restResponse = nullptr;
    Pointer<ogm::Object> restRequest = ogm::Object::Make();

    logger_.LogInfo() << "Identifying ourself to hawkbit server";

    String dataURL = "/" + config_->tenantId + "/controller/v1/" + config_->targetName + "/configData";
    Uri uri = BuildApiURL(dataURL);

    JsonBuildStatus(restRequest, String(), String(), String("success"), String("closed"), *config_->device, 0);

    int status = RestRequest(RequestMethod::kPut, uri, true, restRequest, false, restResponse);

    if (status == 200) {
        logger_.LogInfo() << "Identifying successful";
        return true;
    } else {
        logger_.LogError() << "Identifying failed";
        return false;
    }
}

bool HawkbitClient::TransferVehiclePackage(std::string const& dataLocation, std::string const& vehiclepackage)
{
    // logger_.LogInfo() << "Transferring" << dataLocation + "/" + vehiclepackage;
    return serviceApp_.TransferVehiclePackage(dataLocation + "/" + vehiclepackage);
}

bool HawkbitClient::TransferSoftwarePackages(std::string const& dataLocation)
{
    bool result = true;

    const auto packages = serviceApp_.GetRequestedPackages();   // requestedPackage list
    for (auto& swPackage : packages) {
        logger_.LogInfo() << "Transferring" << dataLocation + "/" + swPackage + ".zip";
        result &= serviceApp_.TransferSoftwarePackage(dataLocation, swPackage);
    }
    return result;
}

bool HawkbitClient::Deploy(Uri& feedbackURL, NewSoftwareDeploymentData& deploymentData)
{
    String msg;
    if (!TransferVehiclePackage(deploymentData.filesLocation, deploymentData.vehiclePackage.filename)) {
        msg = "Transfer of Vehicle Package " + deploymentData.vehiclePackage.filename + " failed";
        Feedback(feedbackURL, *actionId_, msg, "failure", "closed");
        return false;
    }
    if (!TransferSoftwarePackages(deploymentData.filesLocation)) {
        msg = "Transfer of SoftwarePackages failed";
        Feedback(feedbackURL, *actionId_, msg, "failure", "closed");
        return false;
    }
    return true;
}

void HawkbitClient::DownloadAndDeploy(std::shared_ptr<std::queue<std::unique_ptr<HawkbitChunkSpecification>>> chunks)
{
    NewSoftwareDeploymentData deploymentData;
    String msg;
    std::unique_ptr<HawkbitChunkSpecification> currentChunk;
    std::unique_ptr<HawkbitArtifactSpecification> currentArtifact;
    Uri feedbackURL = BuildApiURL(String("/" + config_->tenantId + "/controller/v1/" + config_->targetName
        + "/deploymentBase/" + *actionId_ + "/feedback"));
    logger_.LogInfo() << "DownloadThread Started";

    CleanDirectory(config_->downloadLocation);
    deploymentData.filesLocation = config_->downloadLocation;

    while (!chunks->empty()) {
        uint32_t artifactCount = 0;
        currentChunk = std::move(chunks->front());
        chunks->pop();
        while (!(currentChunk->artifactsQueue.empty())) {
            currentArtifact = std::move(currentChunk->artifactsQueue.front());
            currentChunk->artifactsQueue.pop();
            FileInformation fileInformation = {currentArtifact->fileInformation.filename,
                currentArtifact->fileInformation.size,
                currentArtifact->fileInformation.sha1};

            // setup checkSum
            String checkSum;
            int status = 0;
            bool res = GetBinary(Uri(currentArtifact->downloadURL),
                (config_->downloadLocation + "/" + currentArtifact->fileInformation.filename),
                checkSum,
                status);

            if (!res) {
                msg = "Download failed. Status: " + status;
                Feedback(feedbackURL, *actionId_, msg, "failure", "closed");
                chunks.reset();
                actionId_.reset();
                return;

            } else {
                msg = "Download complete.";
                // first downloaded artifact is treated as vehicle package
                if (artifactCount == 0) {
                    deploymentData.vehiclePackage = fileInformation;
                    // logger_.LogInfo() << "Vehicle Package:" << deploymentData.vehiclePackage.filename;
                } else {
                    deploymentData.swPackages.push_back(fileInformation);
                    // logger_.LogInfo() << "SW Package:" << fileInformation.filename;
                }
            }

            // validate checkSum
            if (currentArtifact->fileInformation.sha1.compare(checkSum) != 0) {
                msg = "Software: " + currentChunk->name + " V" + currentChunk->version + "["
                    + currentArtifact->fileInformation.filename + "]" + "\nInvalid checksum: " + checkSum
                    + " Checksum expected : " + currentArtifact->fileInformation.sha1;
                Feedback(feedbackURL, *actionId_, msg, "failure", "closed");
                chunks.reset();
                actionId_.reset();
                return;
            } else {
                msg = "File checksum OK.\n";
            }
            artifactCount++;
        }
    }

    FeedbackProgress(feedbackURL, *actionId_, 1, msg);
    msg = "All files' checksums OK.\n";
    FeedbackProgress(feedbackURL, *actionId_, 2, msg);

    if (!Deploy(feedbackURL, deploymentData)) {
        msg = "Deployment failed!";
        Feedback(feedbackURL, *actionId_, msg, "failure", "closed");
        // logger_.LogInfo() << msg;
        return;
    }

    msg = "Software installed successfully.";
    Feedback(feedbackURL, *actionId_, msg, "success", "closed");
    // logger_.LogInfo() << msg;

    actionId_.reset();
    return;
}

bool HawkbitClient::ProcessDeployment(apd::rest::Pointer<apd::rest::ogm::Object>& requestRoot)
{

    String deployment;
    Pointer<ogm::String> deploymentLink;
    std::smatch groups;
    Uri getResourceURL;
    Uri feedbackURL;

    // get deployment url
    deploymentLink = JsonGetString(requestRoot, "_links.deploymentBase.href");

    if (deploymentLink == nullptr) {
        logger_.LogError() << "Failed to parse deployment base response. Key not found";
        return false;
    }

    deployment = deploymentLink->GetValue();
    // logger_.LogInfo() << "Deployment link: " << deployment;

    // get resource id and action id from url
    if (!std::regex_search(deployment, groups, std::regex("/deploymentBase/(.+)[?]c=(.+)$"))) {
        logger_.LogError() << "Failed to parse deployment base response. Id not recognized";
        return false;
    }

    actionId_.reset(new String(groups[1].str()));

    // build urls for deployment resource info
    getResourceURL = BuildApiURL(String("/" + config_->tenantId + "/controller/v1/" + config_->targetName
        + "/deploymentBase/" + *actionId_ + "?c=" + groups[2].str()));
    feedbackURL = BuildApiURL(String("/" + config_->tenantId + "/controller/v1/" + config_->targetName
        + "/deploymentBase/" + *actionId_ + "/feedback"));

    std::shared_ptr<std::queue<std::unique_ptr<HawkbitChunkSpecification>>> chunksQueue
        = std::make_shared<std::queue<std::unique_ptr<HawkbitChunkSpecification>>>();

    do {
        Pointer<ogm::Object> restResponse = nullptr;
        Pointer<ogm::Object> restRequest = ogm::Object::Make();
        int status;
        Pointer<ogm::Array> jsonChunks = nullptr;
        Pointer<ogm::Object> jsonChunk = nullptr;
        String downloadURL;

        // get deployment resource
        status = RestRequest(RequestMethod::kGet, getResourceURL, false, restRequest, true, restResponse);
        if (status != 200 || restResponse == nullptr) {
            logger_.LogError() << "Failed to get resource from hawkbit server. Status: ";
            break;
        }

        jsonChunks = JsonGetArray(restResponse, "deployment.chunks");

        if (jsonChunks == nullptr || jsonChunks->GetSize() == 0) {
            Feedback(feedbackURL, *actionId_, "Failed to parse deployment resource.", "failure", "closed");
            logger_.LogError() << "Failed to parse deployment resource.";
            break;
        }

        for (uint i = 0; (jsonChunk = JsonArrayGetElement(jsonChunks, i)) != nullptr; i++) {

            std::unique_ptr<HawkbitChunkSpecification> chunk = std::make_unique<HawkbitChunkSpecification>();
            chunk->version = JsonGetString(jsonChunk, "version")->GetValue();
            chunk->name = JsonGetString(jsonChunk, "name")->GetValue();
            chunk->part = JsonGetString(jsonChunk, "part")->GetValue();
            Pointer<ogm::Array> jsonArtifacts = JsonGetArray(jsonChunk, "artifacts");

            if (jsonArtifacts == nullptr || jsonArtifacts->GetSize() == 0) {
                Feedback(feedbackURL, *actionId_, "Failed to parse deployment resource.", "failure", "closed");
                logger_.LogError() << "Failed to parse deployment resource.";
                continue;
            }

            Pointer<ogm::Object> jsonArtifact = nullptr;
            for (uint j = 0; (jsonArtifact = JsonArrayGetElement(jsonArtifacts, j)) != nullptr; j++) {
                // get artifact information
                std::unique_ptr<HawkbitArtifactSpecification> artifact
                    = std::make_unique<HawkbitArtifactSpecification>();

                artifact->fileInformation.filename = JsonGetString(jsonArtifact, "filename")->GetValue();
                artifact->fileInformation.size = JsonGetInt(jsonArtifact, "size");
                artifact->fileInformation.sha1 = JsonGetString(jsonArtifact, "hashes.sha1")->GetValue();

                // favour https download
                Pointer<ogm::String> downloadURLOgm;
                downloadURLOgm = JsonGetString(jsonArtifact, "_links.download.href");
                if (downloadURLOgm == nullptr) {
                    downloadURLOgm = JsonGetString(jsonArtifact, "_links.download-http.href");

                    if (downloadURLOgm == nullptr) {
                        Feedback(feedbackURL, *actionId_, "Failed to parse deployment resource.", "failure", "closed");
                        continue;
                    } else {
                        artifact->downloadURL = downloadURLOgm->GetValue();
                    }
                }

                /*
                logger_.LogInfo() << "New software ready for download. (Name: " << artifact->fileInformation.filename
                                  << " Version: " << chunk->version << " Size: " << artifact->fileInformation.size
                                  << " URL: " << artifact->downloadURL << ")";
                */
                chunk->artifactsQueue.push(std::move(artifact));
            }
            chunksQueue->push(std::move(chunk));
        }
        DownloadAndDeploy(chunksQueue);
    } while (false);
    return true;
}

void HawkbitClient::CleanDirectory(std::string pathToDir)
{
    // logger_.LogInfo() << "Cleaning directory:" << pathToDir;
    boost::filesystem::path path_to_remove(pathToDir);
    for (boost::filesystem::directory_iterator end_dir_it, it(path_to_remove); it != end_dir_it; ++it) {
        boost::filesystem::remove_all(it->path());
    }
}

void HawkbitClient::HawkbitInit(const ConfigClass& config)
{
    if (!config.isInitializedCorrectly) {
        logger_.LogError() << "Something wrong with config file";
        return;
    }
    config_ = &config;

    logger_.LogInfo() << "HawkbitClient is successfully initialized";
}

void HawkbitClient::HawkbitPullCallback()
{
    while (continueExecution_) {
        // build hawkBit get tasks URL
        String stringTask = "/" + config_->tenantId + "/controller/v1/" + config_->targetName;

        Uri uri = BuildApiURL(stringTask);

        Pointer<ogm::Object> restResponse = nullptr;
        Pointer<ogm::Object> restRequest = nullptr;

        logger_.LogInfo() << "Checking for new software...";

        int status = RestRequest(RequestMethod::kGet, uri, false, restRequest, true, restResponse);
        if (status == 200) {
            if (restResponse != nullptr) {
                // get hawkbit sleep time (how often should we check for new software)
                hawkbitIntervalCheckSec_ = JsonGetSleeptime(restResponse, DEFAULT_SLEEP_TIME_SEC);
                logger_.LogInfo() << "Got hawkbit sleep time: " << hawkbitIntervalCheckSec_;
                // analyse the jsonResponseParser content
                if (JsonContains(restResponse, "_links.configData")) {
                    // hawkBit has asked us to identify ourself
                    Identify();
                }

                if (JsonContains(restResponse, "_links.deploymentBase")) {
                    // hawkBit has a new deployment for us
                    ProcessDeployment(restResponse);
                } else {
                    logger_.LogInfo() << "No new software.";
                }

                if (JsonContains(restResponse, "_links.cancelAction")) {
                    // TO DO: implement me
                    logger_.LogInfo() << "cancel action not supported";
                }
            } else {
                logger_.LogError() << "No response received!";
            }

            // sleep as long as specified by hawkbit
            sleepTime_ = hawkbitIntervalCheckSec_;

        } else if (status == 401) {
            if (!(config_->authToken).empty()) {
                logger_.LogError() << "Failed to authenticate. Check if auth_token is correct?";
            } else if (!(config_->gatewayToken).empty()) {
                logger_.LogError() << "Failed to authenticate. Check if gateway_token is correct?";
            }

            sleepTime_ = std::chrono::seconds(config_->retryWait);
        } else {
            logger_.LogError() << "Scheduled check for new software failed status code: " << status;
            sleepTime_ = std::chrono::seconds(config_->retryWait);
        }
        std::this_thread::sleep_for(sleepTime_);
    }
    restClient_.Stop(apd::rest::ShutdownPolicy::kGraceful).wait();
    logger_.LogInfo() << "Hawkbit Client stopped";
}

void HawkbitClient::StopServiceSync()
{
    logger_.LogInfo() << "Stopping Hawkbit Client";
    continueExecution_ = false;
    serviceThread_.join();
}

void HawkbitClient::HawkbitStartServiceSync()
{
    serviceThread_ = std::move(std::thread(&HawkbitClient::HawkbitPullCallback, this));
}

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp
