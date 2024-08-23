#include "OtaClient.h"

#include "ara/exec/execution_client.h"

using namespace ara::vucm::pkgmgr::proxy;

namespace eevp {
namespace ota {

std::atomic_bool OtaClient::mRunning(false);

class VehiclePackageManagementListener : public eevp::ota::vucm::IVehiclePackageManagementListener {
public:
    VehiclePackageManagementListener(OtaClient* otaClientPtr) : otaClient(otaClientPtr) {}

    void notifyRequestedPackage(const ara::ucm::SwNameVersionType& requestedPackage) {
        otaClient->notifyRequestedPackage(requestedPackage);
    }

    void notifySafetyState(const bool& safetyState) {
        otaClient->notifySafetyState(safetyState);
    }

    void notifyTransferState(const ara::ucm::TransferStateType& transferState) {
        otaClient->notifyTransferState(transferState);
    }

private:
    OtaClient* otaClient;
};

class OtaMonitoringListener : public IOtaMonitoringListener {
public:
    OtaMonitoringListener(OtaClient* otaClientPtr) : otaClient(otaClientPtr) {}

    void requestServiceInstall(const ara::core::String& serviceName) {
        otaClient->requestServiceInstall(serviceName);
    }

    void requestServiceUpdate(const ara::core::String& serviceName) {
        otaClient->requestServiceUpdate(serviceName);
    }

    void requestVersionInfo(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap) {
        otaClient->requestServiceInfoMap(requestServiceInfoMap);
    }

    void resetUcmTest() {
        otaClient->resetUcmTest();
    }

private:
    OtaClient* otaClient;
};

class OtaSubscriptionListener : public IOtaSubscriptionListener {
public:
    OtaSubscriptionListener(OtaClient* otaClientPtr) : otaClient(otaClientPtr) {}

    void requestAppInstall(const ara::core::String& appName) {
        otaClient->requestAppInstall(appName);
    }

    void requestAppUpdate(const ara::core::String& appName) {
        otaClient->requestAppUpdate(appName);
    }

    void requestVersionInfo(eevp::ota::subscription::type::RequestAppInfoMap& requestAppInfoMap) {
        otaClient->requestAppInfoMap(requestAppInfoMap);
    }

private:
    OtaClient* otaClient;
};

OtaClient::OtaClient() :
        dataTransfer{nullptr},
        vehiclePackageManagementProxyImpl{nullptr},
        otaMonitoringSkeletonImpl{nullptr},
        otaSubscriptionSkeletonImpl{nullptr},
        mLogger(ara::log::CreateLogger("OTAC", "SWC", ara::log::LogLevel::kInfo)) {
    // std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);

    pOtaUtils = OtaUtils::getInstance();

#ifdef UCM_TEST
    serviceInfoMap = {
        {"RearCurtain", {"RearCurtain", "1.0.0",    1718601691}},
        {"MoodLamp",    {"MoodLamp",    "1.0.0",    1718601691}},
        {"app03",       {"app03",       "0.0.3",    1718600000}},
        {"app04",       {"app04",       "0.0.4",    1718600000}},
        {"app05",       {"app05",       "0.0.5",    1718600000}},
        {"app06",       {"app06",       "0.0.6",    1718600000}},
        {"app07",       {"app07",       "0.0.7",    1718600000}},
        {"app08",       {"app08",       "0.0.8",    1718600000}},
        {"app09",       {"app09",       "0.0.9",    1718600000}},
        {"app10",       {"app10",       "0.0.10",   1718600000}},
    };

    appInfoMap = {
        {"RearCurtain", {"RearCurtain", "1.0.0",    1718601691}},
        {"MoodLamp",    {"MoodLamp",    "1.0.0",    1718601691}},
        {"app03",       {"app03",       "0.0.3",    1718600000}},
        {"app04",       {"app04",       "0.0.4",    1718600000}},
        {"app05",       {"app05",       "0.0.5",    1718600000}},
        {"app06",       {"app06",       "0.0.6",    1718600000}},
        {"app07",       {"app07",       "0.0.7",    1718600000}},
        {"app08",       {"app08",       "0.0.8",    1718600000}},
        {"app09",       {"app09",       "0.0.9",    1718600000}},
        {"app10",       {"app10",       "0.0.10",   1718600000}},
    };
#endif
}

OtaClient::~OtaClient() {
}

void
OtaClient::SignalHandler(std::int32_t /*signal*/) {
    mRunning = false;
}

bool
OtaClient::Start() {
    mLogger.LogInfo() << "OtaClient Start";

    mRunning = true;

    if (!setRunningState()) {
        return false;
    }

    if (!startVehiclePackageManagementProxy()) {
        return false;
    }

    if (!startMonitoringStub()) {
        return false;
    }

    if (!startSubscriptionStub()) {
        return false;
    }

    dataTransfer = std::make_shared<DataTransfer>();
    dataTransfer->setVUCMProxy(vehiclePackageManagementProxyImpl);

    return true;
}

void
OtaClient::Run(int ac, char** av) {
    mLogger.LogInfo() << "OtaClient Run";

#ifdef HAWKBIT
    std::shared_ptr<VehiclePackageManagementApp<VehiclePackageManagementProxy>> app;
    app = std::make_unique<VehiclePackageManagementApp<VehiclePackageManagementProxy>>(vehiclePackageManagementProxyImpl->getVehiclePackageManagementProxy());

    std::string configFile = "/opt/OTAClient/etc/config.ini";

    if (app->UpdateStatus() && app->UpdateRequestedPackage()) {
        mLogger.LogInfo() << "Start Provider";
        RunHawkbitProvider(*app, configFile);
    }
#else
    while (mRunning) {
        mLogger.LogInfo() << "OtaClient is alive";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

#ifdef UCM_TEST
        ara::ucm::SwClusterInfoVectorType swInfo;
        if (vehiclePackageManagementProxyImpl->getSwClusterInfo(swInfo)) {
            if (swInfo.size() == 0) {
                mLogger.LogInfo() << "empty data";
                if (pOtaUtils->isInstall()) {
                    std::vector<std::string> packages = {
                        INSTALL_SOFTWARE_PACKAGE,
                    };
                    std::thread ucmtest_thread(&OtaClient::ucmtest, this, packages);
                    ucmtest_thread.detach();
                }
            } else {
                for (auto& info : swInfo) {
                    mLogger.LogInfo() << "name : " << info.Name.c_str() << " / "
                                      << "version : " << info.Version.c_str() << " / "
                                      << "state : " << static_cast<uint8_t>(info.State);
                }
                if (pOtaUtils->isUpdate()) {
                    std::vector<std::string> packages = {
                        UPDATE_SOFTWARE_PACKAGE,
                    };
                    std::thread ucmtest_thread(&OtaClient::ucmtest, this, packages);
                    ucmtest_thread.detach();
                }
            }
        }
#endif
    }
#endif
}

void
OtaClient::Terminate() {
    mLogger.LogInfo() << "OtaClient Terminate";

    mRunning = false;
}

void
OtaClient::notifyRequestedPackage(const ara::ucm::SwNameVersionType& requestedPackage) {
    // NOT NEED
}

void
OtaClient::notifySafetyState(const bool& safetyState) {
    // NOT NEED
}

void
OtaClient::notifyTransferState(const ara::ucm::TransferStateType& transferState) {
    // NOT NEED
}

void
OtaClient::requestServiceInstall(const eevp::type::String& serviceName) {
#ifdef UCM_TEST
    std::vector<std::string> packages = {
        REMOVE_SOFTWARE_PACKAGE,
        INSTALL_SOFTWARE_PACKAGE
    };
    std::thread ucmtest_thread(&OtaClient::ucmtest, this, packages);
    ucmtest_thread.detach();
#else
    std::thread deployment_thread(&OtaClient::deployment, this, serviceName);
    deployment_thread.detach();
#endif
}

void
OtaClient::requestServiceUpdate(const eevp::type::String& serviceName) {
#ifdef UCM_TEST
    std::vector<std::string> packages = {
        UPDATE_SOFTWARE_PACKAGE
    };
    std::thread ucmtest_thread(&OtaClient::ucmtest, this, packages);
    ucmtest_thread.detach();
#else
    std::thread deployment_thread(&OtaClient::deployment, this, serviceName);
    deployment_thread.detach();
#endif
}

void
OtaClient::requestServiceInfoMap(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap) {
    requestServiceInfoMap = serviceInfoMap;
}

void
OtaClient::resetUcmTest() {
#ifdef UCM_TEST
    std::vector<std::string> packages = {
        REMOVE_SOFTWARE_PACKAGE,
        INSTALL_SOFTWARE_PACKAGE
    };
    std::thread ucmtest_thread(&OtaClient::ucmtest, this, packages);
    ucmtest_thread.detach();
#endif
}

void
OtaClient::requestAppInstall(const eevp::type::String& appName) {
    std::thread deployment_thread(&OtaClient::deployment, this, appName);
    deployment_thread.detach();
}

void
OtaClient::requestAppUpdate(const eevp::type::String& appName) {
    std::thread deployment_thread(&OtaClient::deployment, this, appName);
    deployment_thread.detach();
}

void
OtaClient::requestAppInfoMap(eevp::ota::subscription::type::RequestAppInfoMap& requestAppInfoMap) {
    requestAppInfoMap = appInfoMap;
}

bool
OtaClient::setRunningState() {
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "OtaClient Running State";
    } else {
        mLogger.LogInfo() << exec.Error().Message();
        return false;
    }
    return true;
}

bool
OtaClient::startVehiclePackageManagementProxy() {
    vehiclePackageManagementProxyImpl = std::make_shared<eevp::ota::vucm::VehiclePackageManagementProxyImpl>();
    auto vehiclePackageManagementListener = std::make_shared<VehiclePackageManagementListener>(this);
    vehiclePackageManagementProxyImpl->setEventListener(vehiclePackageManagementListener);
    vehiclePackageManagementProxyImpl->init();
    return true;
}

bool
OtaClient::startMonitoringStub() {
    ara::core::InstanceSpecifier specifierMonitoring("OTAClient/AA/PPortOtaMonitoring");
    otaMonitoringSkeletonImpl = std::make_shared<eevp::ota::monitoring::OtaMonitoringSkeletonImpl>(specifierMonitoring);
    auto otaMonitoringListener = std::make_shared<OtaMonitoringListener>(this);
    otaMonitoringSkeletonImpl->setEventListener(otaMonitoringListener);
    otaMonitoringSkeletonImpl->OfferService();
    return true;
}

bool
OtaClient::startSubscriptionStub() {
    ara::core::InstanceSpecifier specifierSubscription("OTAClient/AA/PPortOtaSubscription");
    otaSubscriptionSkeletonImpl = std::make_shared<eevp::ota::subscription::OtaSubscriptionSkeletonImpl>(specifierSubscription);
    auto otaSubscriptionListener = std::make_shared<OtaSubscriptionListener>(this);
    otaSubscriptionSkeletonImpl->setEventListener(otaSubscriptionListener);
    otaSubscriptionSkeletonImpl->OfferService();
    return true;
}

void
OtaClient::deployment(const eevp::type::String& packageName) {
    ara::core::String targetManifest;
    ara::core::String targetPackage;

    while (vehiclePackageManagementProxyImpl->getTransferState()
            != ara::ucm::TransferStateType::kIdle) {
        mLogger.LogInfo() << "wait until idle";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    targetManifest
        .append(OTA_PACKAGE_DIR).append("/").append(packageName).append("/").append(VEHICLE_PACKAGE_MANIFEST_JSON);
    targetPackage
        .append(OTA_PACKAGE_DIR).append("/").append(packageName).append("/").append(packageName).append(".tar");

    mLogger.LogInfo() << __func__ << targetManifest.c_str();
    mLogger.LogInfo() << __func__ << targetPackage.c_str();

    sessionInfo.clear();
    if (pOtaUtils->parseVpmJson(targetManifest, sessionInfo)) {
        mLogger.LogInfo() << "* package-name : " << sessionInfo.packageName.c_str();
        mLogger.LogInfo() << "* software-cluster : " << sessionInfo.softwareCluster.c_str();
        mLogger.LogInfo() << "* version : " << sessionInfo.version.c_str();
        mLogger.LogInfo() << "* action-type : " << sessionInfo.actionType.c_str();
    } else {
        return;
    }

    if (!dataTransfer->dataTransferVehiclePackage(targetManifest)) {
        return;
    }

    if (!dataTransfer->dataTransferSoftwarePackage(packageName, targetPackage)) {
        return;
    }

    while (vehiclePackageManagementProxyImpl->getTransferState()
            != ara::ucm::TransferStateType::kIdle) {
        mLogger.LogInfo() << "wait until idle";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

#if 0
    ara::ucm::SwClusterInfoVectorType swInfo;
    if (vehiclePackageManagementProxyImpl->getSwClusterInfo(swInfo)) {
        mLogger.LogInfo() << "getSwClusterInfo success : size = " << swInfo.size();
        if (swInfo.size() != 0) {
            for (auto& package : swInfo) {
                if (!dataTransfer->dataTransferSoftwarePackage(package.Name, targetPackage)) {
                    break;
                }
            }
        } else {
            if (!dataTransfer->dataTransferSoftwarePackage(packageName, targetPackage)) {
                return;
            }
        }
    } else {
        mLogger.LogInfo() << "getSwClusterInfo fail";
    }
#endif
}

#ifdef UCM_TEST
void
OtaClient::ucmtest(const std::vector<std::string>& packages) {
    ara::core::String targetManifest;
    ara::core::String targetPackage;

    while (vehiclePackageManagementProxyImpl->getTransferState()
            != ara::ucm::TransferStateType::kIdle) {
        mLogger.LogInfo() << "wait until idle";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    for (const auto& it : packages) {
        mLogger.LogInfo() << __func__ << it.c_str();
        targetManifest.clear();
        targetPackage.clear();

        targetManifest
            .append(OTA_TEST_PACKAGE_DIR).append("/").append(it).append("/").append(VEHICLE_PACKAGE_MANIFEST_JSON);
        targetPackage
            .append(OTA_TEST_PACKAGE_DIR).append("/").append(it).append("/").append(it).append(".tar");

        mLogger.LogInfo() << __func__ << targetManifest.c_str();
        mLogger.LogInfo() << __func__ << targetPackage.c_str();

        sessionInfo.clear();
        if (pOtaUtils->parseVpmJson(targetManifest, sessionInfo)) {
            mLogger.LogInfo() << "* package-name : " << sessionInfo.packageName.c_str();
            mLogger.LogInfo() << "* software-cluster : " << sessionInfo.softwareCluster.c_str();
            mLogger.LogInfo() << "* version : " << sessionInfo.version.c_str();
            mLogger.LogInfo() << "* action-type : " << sessionInfo.actionType.c_str();
        } else {
            return;
        }

        if (!dataTransfer->dataTransferVehiclePackage(targetManifest)) {
            return;
        }

        if (!dataTransfer->dataTransferSoftwarePackage(it, targetPackage)) {
            break;
        }

        while (vehiclePackageManagementProxyImpl->getTransferState()
                != ara::ucm::TransferStateType::kIdle) {
            mLogger.LogInfo() << "wait until idle";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        if (sessionInfo.actionType == "install") {
            eevp::ota::monitoring::type::UpdatableServiceInfo serviceInfo;
            serviceInfo.serviceName = sessionInfo.softwareCluster;
            serviceInfo.version = "1.0.1";
            serviceInfo.actionType = "install";
            otaMonitoringSkeletonImpl->sendNotifyUpdatableService(serviceInfo);
        } else if (sessionInfo.actionType == "update") {
            eevp::ota::monitoring::type::RequestServiceInfo serviceInfo;
            serviceInfo.serviceName = sessionInfo.softwareCluster;
            serviceInfo.version = sessionInfo.version;
            serviceInfo.lastUpdateTime = 1718601691;
            otaMonitoringSkeletonImpl->sendNotifyServiceEvent(serviceInfo);
        }
    }
/*
    ara::ucm::SwClusterInfoVectorType swInfo;
    if (vehiclePackageManagementProxyImpl->getSwClusterInfo(swInfo)) {
        for (auto& info : swInfo) {
            if(info.Name ==
        }
    }
*/
    mLogger.LogInfo() << __func__ << "completed";
}
#endif

#ifdef HAWKBIT
void
OtaClient::RunHawkbitProvider(
        VehiclePackageManagementApp<VehiclePackageManagementProxy>& app,
        std::string const& configFile) {
    mLogger.LogInfo() << "Running hawkbit provider";

    eevp::ucm::ota::hawkbitClient::ConfigClass hawkbitConfig;
    hawkbitConfig.LoadConfigFile(configFile.c_str());
    if (!hawkbitConfig.isInitializedCorrectly) {
        return;
    }

    eevp::ucm::ota::hawkbitClient::HawkbitClient hawkbitClient(app);
    if (!hawkbitClient.Init(hawkbitConfig)) {
        mLogger.LogError() << "Error while initialization of hawkbit provider";
    } else {
        hawkbitClient.StartServiceSync();
        mLogger.LogInfo() << "hawkbit provider running";
    }

    while (mRunning) {
        mLogger.LogInfo() << "OTA Client is alive";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    hawkbitClient.StopServiceSync();
}
#endif

} // namespace ota
} // namespace eevp
