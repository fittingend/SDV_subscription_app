#include "MonitoringManager.h"

#include "ara/exec/execution_client.h"
#include <ctime>

// #define demo

namespace eevp {
namespace monitoring {

std::atomic_bool MonitoringManager::mRunning(false);

class MonitoringManagementListener : public IMonitoringManagementListener {
public:
    MonitoringManagementListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    bool requestAppInstall(const eevp::type::String& serviceName) {
        return monitoringManager->requestAppInstall(serviceName);
    }

    bool requestAppUpdate(const eevp::type::String& serviceName) {
        return monitoringManager->requestAppUpdate(serviceName);
    }

    bool requestControllerServiceInfo(
                    const eevp::type::String& serviceName,
                    eevp::monitoring::type::ControllerServiceInfo& serviceInfo) {
        return monitoringManager->requestControllerServiceInfo(serviceName, serviceInfo);
    }

    bool requestControllerServiceInfoAll(eevp::monitoring::type::ControllerServiceInfoMap& infoMap) {
        return monitoringManager->requestControllerServiceInfoAll(infoMap);
    }

    bool requestControllerServiceStatus(const eevp::type::String& serviceName, eevp::type::String& status) {
        return monitoringManager->requestControllerServiceStatus(serviceName, status);
    }

    bool requestControllerServiceStatusAll(eevp::monitoring::type::ControllerServiceStatusMap& statusMap) {
        return monitoringManager->requestControllerServiceStatusAll(statusMap);
    }

    bool setEnableControllerService(const eevp::type::String& serviceName, const eevp::type::String& enable) {
        return monitoringManager->setEnableControllerService(serviceName, enable);
    }

    bool requestControllerServiceInfoAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& version,
                    eevp::monitoring::type::TimeArray& lastUpdateTime) {
        return monitoringManager->requestControllerServiceInfoAllSpare(serviceName, version, lastUpdateTime);
    }

    bool requestControllerServiceStatusAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& serviceStatus,
                    eevp::monitoring::type::StringArray& serviceEnable,
                    eevp::monitoring::type::StringArray& serviceControl) {
        return monitoringManager->requestControllerServiceStatusAllSpare(
                        serviceName,
                        serviceStatus,
                        serviceEnable,
                        serviceControl);
    }

    bool setControlControllerService(const eevp::type::String& serviceName, const eevp::type::String& serviceControl) {
        return monitoringManager->setControlControllerService(serviceName, serviceControl);
    }

    void resetUcmTest() {
        return monitoringManager->resetUcmTest();
    }

private:
    MonitoringManager* monitoringManager;
};

class OtaMonitoringListener : public IOtaMonitoringListener {
public:
    OtaMonitoringListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifyServiceEvent(const eevp::ota::monitoring::type::RequestServiceInfo& requestServiceInfo) {
        return monitoringManager->notifyServiceEvent(requestServiceInfo);
    }

    void notifyUpdatableService(const eevp::ota::monitoring::type::UpdatableServiceInfo& updatableServiceInfo) {
        return monitoringManager->notifyUpdatableService(updatableServiceInfo);
    }

private:
    MonitoringManager* monitoringManager;
};

class StateManagerListener : public ivi::info::statemanager::IStateManagerListener {
public:
    StateManagerListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifyNotifySystemState(const ivi::info::statemanager::type::State& state) {
        return monitoringManager->notifyNotifySystemState(state);
    }

    void notifyNotifyTime(const std::uint8_t& notifyTime) {
        return monitoringManager->notifyNotifyTime(notifyTime);
    }

    void notifySystemState(const ivi::info::statemanager::type::State& state) {
        return monitoringManager->notifySystemState(state);
    }

private:
    MonitoringManager* monitoringManager;
};

class MoodLampListener : public eevp::control::moodlamp::IMoodLampListener {
public:
    MoodLampListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue) {
        return monitoringManager->notifySoaMlmStatus(fieldValue);
    }

    void getSoaMlmStatus() {
        return monitoringManager->getSoaMlmStatus();
    }

private:
    MonitoringManager* monitoringManager;
};

class RearCurtainListener : public eevp::control::rearcurtain::IRearCurtainListener {
public:
    RearCurtainListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) {
        return monitoringManager->notifySoaRctnStatus(fieldValue);
    }

    void getSoaRctnStatus() {
        return monitoringManager->getSoaRctnStatus();
    }

private:
    MonitoringManager* monitoringManager;
};

MonitoringManager::MonitoringManager() :
        mLogger(ara::log::CreateLogger("MONM", "MONM", ara::log::LogLevel::kInfo)),
        stateManagerProxyImpl{nullptr},
        otaMonitoringProxyImpl{nullptr},
        monitoringManagementSkeletonImpl{nullptr},
        rearCurtainProxyImpl{nullptr},
        moodLampProxyImpl{nullptr} {
    mLogger.LogInfo() << __func__;
    // std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);

    controllerInfoMap = {
        {"RearCurtain", {"RearCurtain", "1.2.0", 1718600000}},
        {"MoodLamp",    {"MoodLamp",    "1.1.0", 1718700000}},
        {"app03",       {"app03",       "1.3.0", 1718800000}},
        {"app04",       {"app04",       "1.4.0", 1718900000}},
        {"app05",       {"app05",       "1.8.0", 1719000000}},
        {"app06",       {"app06",       "1.6.0", 1719100000}},
        {"app07",       {"app07",       "1.7.0", 1719200000}},
        {"app08",       {"app08",       "1.5.0", 1719300000}},
        {"app09",       {"app09",       "1.9.0", 1719400000}},
        {"app10",       {"app10",       "2.0.0", 1719500000}}
    };

    controllerServiceStatusMap = {
        {"RearCurtain", {"RearCurtain", "NORMAL", "ON", "UP"}},
        {"MoodLamp",    {"MoodLamp",    "NORMAL", "ON", "701"}},
        {"app03",       {"app03"}},
        {"app04",       {"app04",       "NORMAL", "ON", "UP"}},
        {"app05",       {"app05",       "NORMAL", "ON", "0"}},
        {"app06",       {"app06",       "NORMAL", "OFF", "0"}},
        {"app07",       {"app07",       "NORMAL", "OFF", "0"}},
        {"app08",       {"app08"}},
        {"app09",       {"app09"}},
        {"app10",       {"app10",       "NORMAL", "OFF", "0"}}
    };

    controllerStatusMap = {
        {"app01", eevp::monitoring::type::ControllerServiceStatus::NORMAL},
        {"app02", eevp::monitoring::type::ControllerServiceStatus::ABNORMAL},
        {"app03", eevp::monitoring::type::ControllerServiceStatus::ABNORMAL},
        {"app04", eevp::monitoring::type::ControllerServiceStatus::NORMAL},
        {"app05", eevp::monitoring::type::ControllerServiceStatus::NORMAL},
        {"app06", eevp::monitoring::type::ControllerServiceStatus::ABNORMAL},
        {"app07", eevp::monitoring::type::ControllerServiceStatus::NORMAL},
        {"app08", eevp::monitoring::type::ControllerServiceStatus::ABNORMAL},
        {"app09", eevp::monitoring::type::ControllerServiceStatus::ABNORMAL},
        {"app10", eevp::monitoring::type::ControllerServiceStatus::NORMAL}
    };
}

MonitoringManager::~MonitoringManager() {
}

void
MonitoringManager::SignalHandler(std::int32_t /*signal*/) {
    mRunning = false;
}

bool
MonitoringManager::Start() {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "MonitoringManager Start";

    mRunning = true;

    if (!setRunningState()) {
        return false;
    }

    if (!startStateManagerProxy()) {
        return false;
    }

    if (!startOtaMonitoringProxy()) {
        return false;
    }

    if (!startMonitoringManagementStub()) {
        return false;
    }

    if (!startMoodLampProxy()) {
        return false;
    }

    if (!startRearCurtainProxy()) {
        return false;
    }

    eventProcessingThreadHandle = std::thread(&MonitoringManager::eventProcessingThread, this);

    startThirtySecondTask();

    return true;
}

void
MonitoringManager::Run(int ac, char** av) {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "MonitoringManager Run";

    while (mRunning) {
        mLogger.LogInfo() << "MonitoringManager is Running";
/*
        for (auto& info : controllerInfoMap) {
            eevp::monitoring::type::ControllerServiceInfoSpare sendinfo = {info.second.serviceName,
                                                                           info.second.version,
                                                                           info.second.lastUpdateTime};

            enqueueEvent(Event(sendinfo));
        }

        for (auto& info : controllerServiceStatusMap) {
            eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {info.second.serviceName,
                                                                            info.second.serviceStatus,
                                                                            info.second.serviceEnable,
                                                                             info.second.serviceControl};

            enqueueEvent(Event(sendinfo));
        }

        for (auto& info : controllerServiceStatusMap) {
            eevp::monitoring::type::ControllerServiceErrorEvent sendinfo;

            sendinfo.serviceName = info.second.serviceName;
            sendinfo.serviceStatus = info.second.serviceStatus;
            sendinfo.serviceError = "";

            enqueueEvent(Event(sendinfo));
        }
*/
	std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void
MonitoringManager::Terminate() {
    mLogger.LogInfo() << "MonitoringManager Terminate";
    mRunning = false;

    stopThirtySecondTask();
    if (eventProcessingThreadHandle.joinable()) {
        eventProcessingThreadHandle.join();
    }
}

void
MonitoringManager::startThirtySecondTask() {
    thrityRunning = true;
    thrityThread = std::thread(&MonitoringManager::thirtySecondTask, this);
}

void
MonitoringManager::stopThirtySecondTask() {
    thrityRunning = false;
    if (thrityThread.joinable()) {
        thrityThread.join();
    }
}

void
MonitoringManager::thirtySecondTask() {
    while (thrityRunning) {
        requestVersionInfo();
        getSoaRctnStatus();
        getSoaMlmStatus();

        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
}

void
MonitoringManager::enqueueEvent(const Event& event) {
    std::lock_guard<std::mutex> lock(queueMutex);
    eventQueue.push(event);
    queueCondVar.notify_one();
}

void
MonitoringManager::eventProcessingThread() {
    while (mRunning) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondVar.wait(lock, [this] { return !eventQueue.empty() || !mRunning; });

        while (!eventQueue.empty()) {
            auto event = eventQueue.front();
            eventQueue.pop();
            lock.unlock();

            switch (event.type) {
                case EventType::SERVICE_INFO_SPARE:
                    monitoringManagementSkeletonImpl->sendeventServiceInfoSpare(event.serviceInfoSpare);
                    break;
                case EventType::SERVICE_STATUS_SPARE:
                    monitoringManagementSkeletonImpl->sendeventServiceStatusSpare(event.serviceStatusSpare);
                    break;
                case EventType::SERVICE_ERROR:
                    monitoringManagementSkeletonImpl->sendeventServiceError(event.serviceErrorEvent);
                    break;
                case EventType::SERVICE_UPDATABLE:
                    monitoringManagementSkeletonImpl->sendupdatableserviceEvent(event.serviceUpdatableEvent);
                    break;
            }

            lock.lock();
        }
    }
}

void
MonitoringManager::notifyServiceEvent(const eevp::ota::monitoring::type::RequestServiceInfo& requestServiceInfo) {
    mLogger.LogInfo() << __func__;

    eevp::type::String key = requestServiceInfo.serviceName;

    auto it = controllerInfoMap.find(key);

    if (it != controllerInfoMap.end()) {
        auto& originalInfo = it->second;

        if (originalInfo.serviceName != requestServiceInfo.serviceName ||
            originalInfo.version != requestServiceInfo.version ||
            originalInfo.lastUpdateTime != requestServiceInfo.lastUpdateTime) {

            originalInfo.serviceName = requestServiceInfo.serviceName;
            originalInfo.version = requestServiceInfo.version;
            originalInfo.lastUpdateTime = requestServiceInfo.lastUpdateTime;

            eevp::monitoring::type::ControllerServiceInfoSpare sendinfo = {
                            originalInfo.serviceName,
                            originalInfo.version,
                            originalInfo.lastUpdateTime};

            enqueueEvent(Event(sendinfo));
        }
    } else {
        mLogger.LogInfo() << "Key " << key.c_str() << " not found in controllerInfoMap.";
    }

}

void
MonitoringManager::notifyUpdatableService(const eevp::ota::monitoring::type::UpdatableServiceInfo& updatableServiceInfo) {
    mLogger.LogInfo() << __func__;

    eevp::monitoring::type::UpdatableServiceList sendinfo = {
                    updatableServiceInfo.serviceName,
                    updatableServiceInfo.version,
                    updatableServiceInfo.actionType};

    enqueueEvent(Event(sendinfo));
}

void
MonitoringManager::notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    auto it = controllerServiceStatusMap.find("MoodLamp");

    if (it == controllerServiceStatusMap.end()) {
        mLogger.LogInfo() << "APP IS NOT EXISTED";
        return;
    }

    auto& info = it->second;

    if (fieldValue.isNormal == eevp::control::SoaDeviceIsNormal::kABNORMAL) {
        info.serviceStatus = "ABNORMAL";
    } else if (fieldValue.isNormal == eevp::control::SoaDeviceIsNormal::kNORMAL) {
        info.serviceStatus = "NORMAL";
    }

    if (fieldValue.colorTableIndex == 1) {
        info.serviceControl = "701";
    } else if (fieldValue.colorTableIndex == 2) {
        info.serviceControl = "702";
    } else {
        info.serviceControl = "703";
    }

    eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                    info.serviceName,
                    info.serviceStatus,
                    info.serviceEnable,
                    info.serviceControl};

    enqueueEvent(Event(sendinfo));
}

void
MonitoringManager::getSoaMlmStatus() {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaMlmStatus soaMlmStatus;
    moodLampProxyImpl->getterSoaMlmStatus(soaMlmStatus);

    auto it = controllerServiceStatusMap.find("MoodLamp");

    if (it == controllerServiceStatusMap.end()) {
        mLogger.LogInfo() << "APP IS NOT EXISTED";
        return;
    }

    auto& info = it->second;

    if (soaMlmStatus.isNormal == eevp::control::SoaDeviceIsNormal::kABNORMAL) {
        info.serviceStatus = "ABNORMAL";
    } else if (soaMlmStatus.isNormal == eevp::control::SoaDeviceIsNormal::kNORMAL) {
        info.serviceStatus = "NORMAL";
    }

    if (soaMlmStatus.colorTableIndex == 1) {
        info.serviceControl = "701";
    } else if (soaMlmStatus.colorTableIndex == 2) {
        info.serviceControl = "702";
    } else {
        info.serviceControl = "703";
    }

    mLogger.LogInfo() << "[getSoaMlmStatus]" << "("
                      << static_cast<int>(soaMlmStatus.isNormal) << ":"
                      << static_cast<int>(soaMlmStatus.colorTableIndex) << ")";

    eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                    info.serviceName,
                    info.serviceStatus,
                    info.serviceEnable,
                    info.serviceControl};

    enqueueEvent(Event(sendinfo));
}

void
MonitoringManager::notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    auto it = controllerServiceStatusMap.find("RearCurtain");

    if (it == controllerServiceStatusMap.end()) {
        mLogger.LogInfo() << "APP IS NOT EXISTED";
        return;
    }

    auto& info = it->second;

    if (fieldValue.isNormal == eevp::control::SoaDeviceIsNormal::kABNORMAL) {
        info.serviceStatus = "ABNORMAL";
    } else if (fieldValue.isNormal == eevp::control::SoaDeviceIsNormal::kNORMAL) {
        info.serviceStatus = "NORMAL";
    }

    if (fieldValue.curMotorDirection == eevp::control::SoaRctnMotorDir::kUP) {
        info.serviceControl = "UP";
    } else if (fieldValue.curMotorDirection == eevp::control::SoaRctnMotorDir::kDOWN) {
        info.serviceControl = "DOWN";
    }

    eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                    info.serviceName,
                    info.serviceStatus,
                    info.serviceEnable,
                    info.serviceControl};

    enqueueEvent(Event(sendinfo));
}

void
MonitoringManager::getSoaRctnStatus() {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaRctnStatus soaRctnStatus;
    rearCurtainProxyImpl->getterSoaRctnStatus(soaRctnStatus);

    auto it = controllerServiceStatusMap.find("RearCurtain");

    if (it == controllerServiceStatusMap.end()) {
        mLogger.LogInfo() << "APP IS NOT EXISTED";
        return;
    }

    auto& info = it->second;

    if (soaRctnStatus.isNormal == eevp::control::SoaDeviceIsNormal::kABNORMAL) {
        info.serviceStatus = "ABNORMAL";
    } else if (soaRctnStatus.isNormal == eevp::control::SoaDeviceIsNormal::kNORMAL) {
        info.serviceStatus = "NORMAL";
    }

    if (soaRctnStatus.curMotorDirection == eevp::control::SoaRctnMotorDir::kUP) {
        info.serviceControl = "UP";
    } else if (soaRctnStatus.curMotorDirection == eevp::control::SoaRctnMotorDir::kDOWN) {
        info.serviceControl = "DOWN";
    }

    mLogger.LogInfo() << "[getSoaRctnStatus]" << "("
                      << static_cast<int>(soaRctnStatus.isNormal) << ":"
                      << static_cast<int>(soaRctnStatus.curMotorDirection) << ")";

    eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                    info.serviceName,
                    info.serviceStatus,
                    info.serviceEnable,
                    info.serviceControl};

    enqueueEvent(Event(sendinfo));
}

bool
MonitoringManager::requestAppInstall(const eevp::type::String& serviceName) {
    mLogger.LogInfo() << __func__  << serviceName << serviceName.length();

    auto it = controllerInfoMap.find(serviceName);

    if (it == controllerInfoMap.end()) {
        mLogger.LogInfo() << "NAME NOT EXISTED";
        return false;
    }

    auto& info = it->second;
    if (info.serviceName.empty()) {
        bool val = otaMonitoringProxyImpl->requestServiceInstall(serviceName);

        if (val) {
            info.serviceName = serviceName;
            mLogger.LogInfo() << "DOWNLOAD REQUEST ACCEPT";
            return true;
        } else {
            mLogger.LogInfo() << "INSTALLED FAILED";
        }
    } else {
        mLogger.LogInfo() << "ALREADY EXISTED";
    }
    return false;
}

bool
MonitoringManager::requestAppUpdate(const eevp::type::String& serviceName) {
    mLogger.LogInfo() << __func__ << serviceName << serviceName.length();

    auto it = controllerInfoMap.find(serviceName);

    if (it == controllerInfoMap.end()) {
        mLogger.LogInfo() << "APP IS NOT EXISTED";
        return false;
    }

    auto& info = it->second;
    if (info.serviceName.empty()) {
        mLogger.LogInfo() << "HAVE TO INSTALL THE APP FIRST";
    } else if (info.version == "latest") {
        mLogger.LogInfo() << "ALREADY LATEST VERSION";
    } else {
        mLogger.LogInfo() << "START UPDATE PROCESS";

        bool val = otaMonitoringProxyImpl->requestServiceUpdate(serviceName);

        if (val) {
            mLogger.LogInfo() << "UPDATE REQUEST COMPLETE";
            return true;
        } else {
            mLogger.LogInfo() << "UPDATE REQUEST FAILED";
        }
    }

    return false;
}

bool
MonitoringManager::requestControllerServiceInfo(const eevp::type::String& serviceName,
                                                eevp::monitoring::type::ControllerServiceInfo& serviceInfo) {
    mLogger.LogInfo() << __func__ << serviceName << serviceName.length();

    auto it = controllerInfoMap.find(serviceName);

    if (it == controllerInfoMap.end()) {
        return false;
    }

    auto& info = it->second;
    serviceInfo.serviceName = info.serviceName;
    serviceInfo.version = info.version;
    serviceInfo.lastUpdateTime = info.lastUpdateTime;

    return true;
}

bool
MonitoringManager::requestControllerServiceStatus(
                const eevp::type::String& serviceName,
                eevp::type::String& status) {
    mLogger.LogInfo() << __func__;

    auto it = controllerServiceStatusMap.find(serviceName);
    if (it == controllerServiceStatusMap.end()) {
        return false;
    }

    auto& info = it->second;

    if (serviceName == "RearCurtain") {
        if (info.serviceControl == "UP") {
            status = "NORMAL";
        } else if (info.serviceControl == "DOWN") {
            status = "ABNORMAL";
        }

        if (info.serviceEnable == "NORMAL") {
            return true;
        } else if (info.serviceEnable == "ABNORMAL") {
            return false;
        }
    }
    else if (serviceName == "MoodLamp") {
        if (info.serviceEnable == "ON") {
            status = "NORMAL";
        } else if (info.serviceEnable == "OFF") {
            status = "ABNORMAL";
        }

        if (info.serviceEnable == "NORMAL") {
            return true;
        } else if (info.serviceEnable == "ABNORMAL") {
            return false;
        }
    }

    return false;
}

bool
MonitoringManager::setEnableControllerService(const eevp::type::String& serviceName, const eevp::type::String& enable) {
    mLogger.LogInfo() << __func__ << serviceName << serviceName.length() << enable << enable.length();

    auto it = controllerServiceStatusMap.find(serviceName);

    if (it == controllerServiceStatusMap.end()) {
        return false;
    }

    auto& info = it->second;

    bool val = false;

    if (serviceName == "RearCurtain") {
        if (enable == "UP") {
            info.serviceEnable = "ON";
            info.serviceControl = "UP";

            eevp::control::SoaRctnMotorDir motorDir = eevp::control::SoaRctnMotorDir::kUP;

            eevp::control::SoaErrorState state = rearCurtainProxyImpl->requestRearCurtainOperation(motorDir);
            val = (state == eevp::control::SoaErrorState::kOK) ? true : false;
        } else if (enable == "DOWN") {
            info.serviceEnable = "OFF";
            info.serviceControl = "DOWN";

            eevp::control::SoaRctnMotorDir motorDir = eevp::control::SoaRctnMotorDir::kDOWN;

            eevp::control::SoaErrorState state = rearCurtainProxyImpl->requestRearCurtainOperation(motorDir);
            val = (state == eevp::control::SoaErrorState::kOK) ? true : false;
        }
    } else {
        info.serviceEnable = enable;
        val = true;
    }

    eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                    info.serviceName,
                    info.serviceStatus,
                    info.serviceEnable,
                    info.serviceControl};

    enqueueEvent(Event(sendinfo));
    return val;
}

bool
MonitoringManager::requestControllerServiceInfoAllSpare(
                eevp::monitoring::type::StringArray& serviceName,
                eevp::monitoring::type::StringArray& version,
                eevp::monitoring::type::TimeArray& lastUpdateTime) {
    mLogger.LogInfo() << __func__;

    int index = 0;
    for (const auto& pair : controllerInfoMap) {
        serviceName[index] = pair.second.serviceName;
        version[index] = pair.second.version;
        lastUpdateTime[index] = pair.second.lastUpdateTime;
        ++index;
    }

    return true;
}
bool
MonitoringManager::requestControllerServiceStatusAllSpare(
                eevp::monitoring::type::StringArray& serviceName,
                eevp::monitoring::type::StringArray& serviceStatus,
                eevp::monitoring::type::StringArray& serviceEnable,
                eevp::monitoring::type::StringArray& serviceControl) {
    mLogger.LogInfo() << __func__;

    int index = 0;
    for (const auto& pair : controllerServiceStatusMap) {
        serviceName[index] = pair.second.serviceName;
        serviceStatus[index] = pair.second.serviceStatus;
        serviceEnable[index] = pair.second.serviceEnable;
        serviceControl[index] = pair.second.serviceControl;
        ++index;
    }

    return true;
}
bool
MonitoringManager::setControlControllerService(
                const eevp::type::String& serviceName,
                const eevp::type::String& serviceControl) {
    mLogger.LogInfo() << __func__ << serviceName << serviceName.length() << serviceControl << serviceControl.length();

    auto it = controllerServiceStatusMap.find(serviceName);

    if (it == controllerServiceStatusMap.end()) {
        return false;
    }

    auto& info = it->second;
    if (serviceName == "MoodLamp" && info.serviceStatus == "NORMAL" && info.serviceEnable == "ON") {
        mLogger.LogInfo() << "CONTROL MoodLamp";

        uint8_t colorTableIndex;

        if (serviceControl == "701") {
            colorTableIndex = 1;
        } else if (serviceControl == "702") {
            colorTableIndex = 2;
        } else if (serviceControl == "703") {
            colorTableIndex = 3;
        }

        bool val = moodLampProxyImpl->requestMlmSetRGBColor(colorTableIndex);

        if (val) {
            info.serviceControl = serviceControl;
            eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
                            info.serviceName,
                            info.serviceStatus,
                            info.serviceEnable,
                            info.serviceControl};
            enqueueEvent(Event(sendinfo));
            return true;
        } else {
            mLogger.LogInfo() << "MoodLamp Color Change failed!";
        }
    }

    return false;
}

void
MonitoringManager::resetUcmTest() {
    mLogger.LogInfo() << __func__;
    otaMonitoringProxyImpl->resetUcmTest();
    return;
}

bool
MonitoringManager::setRunningState() {
    mLogger.LogInfo() << __func__;
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "MonitoringManager Running State";
    } else {
        mLogger.LogError() << exec.Error().Message();
        return false;
    }
    return true;
}

bool
MonitoringManager:: startStateManagerProxy(){
    mLogger.LogInfo() << __func__;
    stateManagerProxyImpl = std::make_shared<ivi::info::statemanager::StateManagerProxyImpl>();
    auto stateManagerListener = std::make_shared<StateManagerListener>(this);
    stateManagerProxyImpl->setEventListener(stateManagerListener);
    stateManagerProxyImpl->init();
    return true;
}

bool
MonitoringManager::startOtaMonitoringProxy() {
    mLogger.LogInfo() << __func__;
    otaMonitoringProxyImpl = std::make_shared<eevp::monitoring::OtaMonitoringProxyImpl>();
    auto otaMonitoringListener = std::make_shared<OtaMonitoringListener>(this);
    otaMonitoringProxyImpl->setEventListener(otaMonitoringListener);
    otaMonitoringProxyImpl->init();
    return true;
}

bool
MonitoringManager::startMonitoringManagementStub() {
    mLogger.LogInfo() << __func__;
    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/PPortMonitoringManagement");
    monitoringManagementSkeletonImpl = std::make_shared<eevp::monitoring::MonitoringManagementSkeletonImpl>(specifier);
    auto monitoringManagementListener = std::make_shared<MonitoringManagementListener>(this);
    monitoringManagementSkeletonImpl->setEventListener(monitoringManagementListener);
    monitoringManagementSkeletonImpl->OfferService();
    return true;
}

bool
MonitoringManager::startMoodLampProxy() {
    mLogger.LogInfo() << __func__;
    moodLampProxyImpl = std::make_shared<eevp::control::moodlamp::MoodLampProxyImpl>();
    auto moodLampListener = std::make_shared<MoodLampListener>(this);
    moodLampProxyImpl->setEventListener(moodLampListener);
    moodLampProxyImpl->init();
    return true;
}

bool
MonitoringManager::startRearCurtainProxy() {
    mLogger.LogInfo() << __func__;
    rearCurtainProxyImpl = std::make_shared<eevp::control::rearcurtain::RearCurtainProxyImpl>();
    auto rearCurtainListener = std::make_shared<RearCurtainListener>(this);
    rearCurtainProxyImpl->setEventListener(rearCurtainListener);
    rearCurtainProxyImpl->init();
    return true;
}

eevp::type::String
MonitoringManager::getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    char buffer[11]; // YYYY.MM.DD is 10 characters long + 1 for null terminator
    std::strftime(buffer, sizeof(buffer), "%Y.%m.%d", &tm);
    return eevp::type::String(buffer);
}

void
MonitoringManager::printMap() {
    for (const auto& info : controllerInfoMap) {
        mLogger.LogInfo() << "[Key] "   << info.first << " "
                          << "[Value] " << "ServiceName("       << info.second.serviceName      << ") "
                                        << "Version("           << info.second.version          << ") "
                                        << "lastUpdateTime("    << info.second.lastUpdateTime   << ")";
    }
}

void
MonitoringManager::requestVersionInfo() {
    mLogger.LogInfo() << __func__;

    eevp::ota::monitoring::type::RequestServiceInfoMap requestServiceInfoMap;
    otaMonitoringProxyImpl->requestVersionInfo(requestServiceInfoMap);

    controllerInfoMap.clear();

    for (auto& info : requestServiceInfoMap) {
        eevp::monitoring::type::ControllerServiceInfo newInfo;

        newInfo.serviceName = info.second.serviceName;
        newInfo.version = info.second.version;
        newInfo.lastUpdateTime = info.second.lastUpdateTime;

        controllerInfoMap[info.first] = newInfo;
    }

    for (auto& info : controllerInfoMap) {
        eevp::monitoring::type::ControllerServiceInfoSpare sendinfo = {
                        info.second.serviceName,
                        info.second.version,
                        info.second.lastUpdateTime};

        enqueueEvent(Event(sendinfo));
    }
}

bool
MonitoringManager::requestControllerServiceInfoAll(eevp::monitoring::type::ControllerServiceInfoMap& infoMap) {
    mLogger.LogInfo() << __func__;

    if (controllerInfoMap.size() == 0) {
        return false;
    }

    infoMap = controllerInfoMap;
    return true;
}

bool
MonitoringManager::requestControllerServiceStatusAll(eevp::monitoring::type::ControllerServiceStatusMap& statusMap) {
    mLogger.LogInfo() << __func__;

    if (controllerStatusMap.size() == 0) {
        return false;
    }

    statusMap = controllerStatusMap;
    return true;
}

void
MonitoringManager::notifyNotifySystemState(const ivi::info::statemanager::type::State& state) {
    mLogger.LogInfo() << __func__           << static_cast<std::uint8_t>(state);
}

void
MonitoringManager::notifyNotifyTime(const std::uint8_t& notifyTime) {
    mLogger.LogInfo() << __func__ << notifyTime;
}

void
MonitoringManager::notifySystemState(const ivi::info::statemanager::type::State& state) {
    mLogger.LogInfo() << __func__           << static_cast<std::uint8_t>(state);
}

} // namespace monitoring
} // namespace eevp
