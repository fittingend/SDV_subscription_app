#include "vpackage_management_app.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "ara/core/string.h"

using ara::com::ServiceHandleContainer;
using ara::core::Future;
using ara::core::String;

using ara::vucm::pkgmgr::VehiclePackageManagement;

using ara::ucm::TransferStateType;

namespace eevp {
namespace ota {

template <class VehiclePackageManagementService>
ara::ucm::CampaignFailureType
VehiclePackageManagementApp<VehiclePackageManagementService>::GetCampaignResolution(
        const std::uint64_t timestampGE,
        const std::uint64_t timestampLT) {
    auto out = (service_->GetCampaignHistory(timestampGE, timestampLT).get()).CampaignHistory;
    return {out.CampaignError.CampaignFailure};
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::GetRequiredSwInfo(
        ara::ucm::SwClusterInfoVectorType& SwInfo) {
    SwInfo = (service_->GetSwClusterInfo().get()).SwInfo;
    // Return value should be false
    // when it couldn't get information of installed Software Clusters
    return true;
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::IsCorrectStatus(
        ara::ucm::TransferStateType askedStatus) {
    while (CurrentStatusToString(currentStatus_).size() == 0) {
        logger_.LogInfo() << "Waiting for status field.";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    if (currentStatus_ != askedStatus) {
        logger_.LogError() << "Current status" << CurrentStatusToString(currentStatus_) << "incorrect; should be"
                           << CurrentStatusToString(askedStatus);
        return false;
    }
    return true;
}

template <class VehiclePackageManagementService>
void
VehiclePackageManagementApp<VehiclePackageManagementService>::OnStatusChange() {
    std::unique_lock<std::mutex> lck(transferMutex_);
    service_->TransferState.GetNewSamples(
        [this](auto sample) {
            this->currentStatus_ = *sample;

            if (CurrentStatusToString(currentStatus_).size() > 0) {
                logger_.LogInfo() << "Transfer state transition notification :"
                                  << CurrentStatusToString(currentStatus_);
                statusBuffer_.push_back(CurrentStatusToString(currentStatus_));
            } else {
                logger_.LogError() << "Empty status field.";
            }
        },
        1);
    lck.unlock();
    campaignCond_.notify_one();
}

template <class VehiclePackageManagementService>
ara::core::Vector<ara::core::String>
VehiclePackageManagementApp<VehiclePackageManagementService>::GetStatusBuffer() {
    std::unique_lock<std::mutex> lck(transferMutex_);
    if (statusBuffer_.empty()) {
        logger_.LogInfo() << "Status buffer empty.";
        return {};
    }
    return statusBuffer_;
}

template <class VehiclePackageManagementService>
void
VehiclePackageManagementApp<VehiclePackageManagementService>::FlushStatusBuffer() {
    if (statusBuffer_.empty()) {
        logger_.LogInfo() << "Status buffer empty.";
        return;
    }
    statusBuffer_.clear();
}

template <class VehiclePackageManagementService>
std::shared_ptr<VehiclePackageManagementService>
VehiclePackageManagementApp<VehiclePackageManagementService>::GetService() {
    return service_;
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::UpdateStatus() {
    if (service_->TransferState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        logger_.LogError() << "TransferState field callback already subscribed";
        return false;
    }

    // Register event receive callback
    service_->TransferState.SetReceiveHandler(
        [this]() { VehiclePackageManagementApp<VehiclePackageManagementService>::OnStatusChange(); });

    // Subscribe to field
    auto subscription_result = service_->TransferState.Subscribe(1);
    if (subscription_result.HasValue()) {
        logger_.LogInfo() << "Callback registered.";
    } else {
        logger_.LogError() << "Subscription failed with error: " << subscription_result.Error();
        return false;
    }

    // Initial update of service.
    // This is necessary in case application is being re-attached to the service
    // after a crash.
    auto state = service_->TransferState.Get();
    this->currentStatus_ = state.get();

    // service_ got initialized via callback.
    logger_.LogInfo() << "Transfer status field callbacks registered.";
    return true;
}

template <class VehiclePackageManagementService>
void
VehiclePackageManagementApp<VehiclePackageManagementService>::OnPackageRequested() {
    std::unique_lock<std::mutex> lck(requestMutex_);
    service_->RequestedPackage.GetNewSamples(
        [this](auto sample) {
            this->requestedPackage_ = (*sample).Name;

            if (requestedPackage_.size() > 0) {
                logger_.LogInfo() << "Requested Package full name:" << requestedPackage_;
                std::size_t last_path_separator_position(requestedPackage_.find_last_of("/"));
                if (last_path_separator_position != ara::core::String::npos) {
                    requestedPackage_
                        = requestedPackage_.substr(last_path_separator_position + 1, ara::core::String::npos);
                }
                requestedPackageList_.push_back(requestedPackage_);
            } else {
                logger_.LogError() << "Empty RequestedPackage field.";
            }
            dataReady_ = true;
        },
        1);
    lck.unlock();
    requestCond_.notify_one();
}

template <class VehiclePackageManagementService>
ara::core::Vector<ara::core::String>
VehiclePackageManagementApp<VehiclePackageManagementService>::GetRequestedPackages() {
    std::unique_lock<std::mutex> lck(requestMutex_);
    if (requestedPackageList_.empty()) {
        logger_.LogInfo() << "Requested packages is not available yet, waiting for it...";
        requestCond_.wait(lck, [this] { return dataReady_; });
    } else {
        logger_.LogInfo() << "Requested packages already has" << requestedPackageList_.size() << "items.";
    }

    return requestedPackageList_;
}

template <class VehiclePackageManagementService>
void
VehiclePackageManagementApp<VehiclePackageManagementService>::FlushRequestedPackageList() {
    if (requestedPackageList_.empty()) {
        logger_.LogInfo() << "Requested package list empty.";
        return;
    }
    requestedPackageList_.clear();
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::UpdateRequestedPackage() {
    if (service_->TransferState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        logger_.LogError() << "RequestedPackage field callback already subscribed";
        return false;
    }

    // Register event receive callback
    service_->RequestedPackage.SetReceiveHandler(
        [this]() { VehiclePackageManagementApp<VehiclePackageManagementService>::OnPackageRequested(); });

    // Subscribe to field
    auto subscription_result = service_->RequestedPackage.Subscribe(1);
    if (subscription_result.HasValue()) {
        logger_.LogInfo() << "Callback registered.";
    } else {
        logger_.LogError() << "Subscription failed with error: " << subscription_result.Error();
        return false;
    }

    // Initial update of service.
    // This is necessary in case application is being re-attached to the service
    // after a crash.
    auto package = service_->RequestedPackage.Get();
    this->requestedPackage_ = package.get().Name;

    // service_ got initialized via callback.
    logger_.LogInfo() << "Requested package field callback registered.";
    return true;
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::TransferVehiclePackage(
        const ara::core::String& packagePath,
        DataTransfer<VehiclePackageManagementService>& dataTransfer) {
    std::vector<uint8_t> buffer;
    bool found = LoadBinaryFile(packagePath, buffer);
    if (!found) {
        logger_.LogError() << "Transfer failed. Vehicle Package not found at path" << packagePath;
        return false;
    }
    requestedPackageList_.clear();

    if (!dataTransfer.InitSession(buffer.size())) {
        logger_.LogError() << "Initialization of transfer with size " + (ara::core::String)std::to_string(buffer.size()) + " failed";
        return false;
    }

    lastTransferId_ = dataTransfer.GetTransferId();
    std::string transferPackageStr(std::begin(lastTransferId_), std::end(lastTransferId_));

    if (!dataTransfer.Transfer(buffer)) {
        logger_.LogError() << "Transfer of Vehicle package associated with TransferId" << transferPackageStr.c_str() << "failed";
        return false;
    }

    if (!dataTransfer.ExitSession()) {
        logger_.LogError() << "Exiting Vehicle package transfer associated with TransferId" << transferPackageStr.c_str()
                           << "failed";
        return false;
    }
    logger_.LogInfo() << "Transfer of Vehicle Package was successful for session" << transferPackageStr.c_str();
    return true;
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::TransferSoftwarePackage(
        const ara::core::String& testDataLocation,
        const ara::core::String& swPackage,
        DataTransfer<VehiclePackageManagementService>& dataTransfer) {
    std::vector<uint8_t> buffer;
    bool found = LoadBinaryFile((testDataLocation + "/" + swPackage + ".zip"), buffer);
    if (!found) {
        logger_.LogError() << "Transfer failed. Software Package not found at path"
                           << testDataLocation + "/" + swPackage + ".zip";
        return false;
    }

    if (!dataTransfer.InitSession(swPackage, (uint64_t)buffer.size())) {
        logger_.LogError() << "Initialization of Software Package transfer with name" << swPackage << "failed";
        return false;
    }

    lastTransferId_ = dataTransfer.GetTransferId();
    std::string transferPackageStr(std::begin(lastTransferId_), std::end(lastTransferId_));

    if (!dataTransfer.Transfer(buffer)) {
        logger_.LogError() << "Transfer of Software package associated with TransferId" << transferPackageStr.c_str() << "failed";
        return false;
    }

    if (!dataTransfer.ExitSession()) {
        logger_.LogError() << "Exiting Software package transfer associated with TransferId" << transferPackageStr.c_str()
                           << "failed";
        return false;
    }
    logger_.LogInfo() << "Transfer of Software Package was successful for session" << transferPackageStr.c_str();
    return true;
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::TransferVehiclePackage(
        const ara::core::String& packagePath) {
    DataTransfer<VehiclePackageManagementService> dataTransfer(service_);
    return this->TransferVehiclePackage(packagePath, dataTransfer);
}

template <class VehiclePackageManagementService>
bool
VehiclePackageManagementApp<VehiclePackageManagementService>::TransferSoftwarePackage(
        const ara::core::String& testDataLocation,
        const ara::core::String& swPackage) {
    DataTransfer<VehiclePackageManagementService> dataTransfer(service_);
    return this->TransferSoftwarePackage(testDataLocation, swPackage, dataTransfer);
}

bool
LoadBinaryFile(const ara::core::String& filePath, std::vector<uint8_t>& binaryPackage) {
    bool fileFound = false;
    std::ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        char c;
        while (ifs.get(c)) {
            binaryPackage.push_back(c);
        }

        fileFound = true;
    }
    ifs.close();

    return fileFound;
}

const ara::core::String
CurrentStatusToString(ara::ucm::TransferStateType status) {
    switch (status) {
        case ara::ucm::TransferStateType::kIdle:
            return "Idle";

//        case ara::ucm::TransferStateType::kSyncing:
//            return "Syncing";

        case ara::ucm::TransferStateType::kTransferring:
            return "Transferring";

        case ara::ucm::TransferStateType::kUpdating:
            return "Updating";

        case ara::ucm::TransferStateType::kCancelling:
            return "Cancelling";

        default:
            return "Unknown";
    }
}

template class VehiclePackageManagementApp<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy>;

}  // namespace ota
}  // namespace eevp
