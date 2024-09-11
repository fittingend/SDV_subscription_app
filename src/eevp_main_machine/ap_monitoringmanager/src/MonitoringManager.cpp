#include "MonitoringManager.h"

#include "ara/exec/execution_client.h"
#include <ctime>

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

    /// MoodLamp
    void RequestMlmSetRgbColor(const std::uint8_t& colorTableIndex) {
        return monitoringManager->RequestMlmSetRgbColor(colorTableIndex);
    }

    /// RearCurtain
    void RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
        return monitoringManager->RequestRearCurtainOperation(motorDir);
    }
    void RequestRearCurtainPosition(const std::uint8_t& posPercentage) {
        return monitoringManager->RequestRearCurtainPosition(posPercentage);
    }

    /// Wiper
    void requestWiperOperation(const eevp::control::SoaWiperMode& mode) {
        return monitoringManager->requestWiperOperation(mode);
    }

    void setWiperAutoSpeed(const bool& isAutoSpeed) {
        return monitoringManager->setWiperAutoSpeed(isAutoSpeed);
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

    void notifySoaMlmSwVersion(const std::uint8_t& fieldValue) {
        return monitoringManager->notifySoaMlmSwVersion(fieldValue);
    }

    void getSoaMlmStatus(eevp::control::SoaMlmStatus& fieldValue) {
        return monitoringManager->getSoaMlmStatus(fieldValue);
    }

    void getSoaMlmSwVersion(std::uint8_t& fieldValue) {
        return monitoringManager->getSoaMlmSwVersion(fieldValue);
    }

private:
    MonitoringManager* monitoringManager;
};

class PdwListener : public eevp::pdw::IPdwListener {
public :
    PdwListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel){
        return monitoringManager->notifyDistanceLevel(dLevel);
    }

private:
    MonitoringManager* monitoringManager;
};

class WiperListener : public eevp::control::wiper::IWiperListener {
public:
    WiperListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->notifySoaWiperDeviceNormal(deviceIsNormal);
    }

    void notifySoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue) {
        return monitoringManager->notifySoaWiperStatus(wiperStatusValue);
    }

    void notifySoaWiperSwVersion(const std::uint8_t& wiperSwVersion) {
        return monitoringManager->notifySoaWiperSwVersion(wiperSwVersion);
    }

    void getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->getSoaWiperDeviceNormal(deviceIsNormal);
    }

    void getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue) {
        return monitoringManager->getSoaWiperStatus(wiperStatusValue);
    }

    void getSoaWiperSwVersion(std::uint8_t& wiperSwVersion) {
        return monitoringManager->getSoaWiperSwVersion(wiperSwVersion);
    }

    void requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode) {
        return monitoringManager->requestWiperOperation(wiperOperationMode);
    }

    void setWiperAutoSpeed(const bool& isAutoSpeed) {
        return monitoringManager->setWiperAutoSpeed(isAutoSpeed);
    }

private:
    MonitoringManager* monitoringManager;
};

class RoaListener : public eevp::control::roa::IRoaListener {
public:
    RoaListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->notifySoaRoaDeviceNormal(deviceIsNormal);
    }

    void notifySoaRoaSwVersion(const std::uint8_t& powerSwVersion) {
        return monitoringManager->notifySoaRoaSwVersion(powerSwVersion);
    }

    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->getSoaRoaDeviceNormal(deviceIsNormal);
    }

    void getSoaRoaSwVersion(std::uint8_t& powerSwVersion) {
        return monitoringManager->getSoaRoaSwVersion(powerSwVersion);
    }

private:
    MonitoringManager* monitoringManager;
};

class DrvseatListener : public eevp::control::drvseat::IDrvseatListener {
public:
    DrvseatListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->notifySoaDrvseatDeviceNormal(deviceIsNormal);
    }

    void notifySoaDrvseatSwVersion(const std::uint8_t& powerSwVersion) {
        return monitoringManager->notifySoaDrvseatSwVersion(powerSwVersion);
    }

    void getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->getSoaDrvseatDeviceNormal(deviceIsNormal);
    }

    void getSoaDrvseatSwVersion(std::uint8_t& powerSwVersion) {
        return monitoringManager->getSoaDrvseatSwVersion(powerSwVersion);
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

    void notifySoaRctnSwVersion(const std::uint8_t& fieldValue) {
        return monitoringManager->notifySoaRctnSwVersion(fieldValue);
    }

    void getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) {
        return monitoringManager->getSoaRctnStatus(fieldValue);
    }

    void getSoaRctnSwVersion(std::uint8_t& fieldValue) {
        return monitoringManager->getSoaRctnSwVersion(fieldValue);
    }

private:
    MonitoringManager* monitoringManager;
};

class PowerListener : public eevp::control::power::IPowerListener {
public:
    PowerListener(MonitoringManager* mgr) : monitoringManager(mgr) {}

    void notifySoaPowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->notifySoaPowerDeviceNormal(deviceIsNormal);
    }

    void notifySoaPowerSwVersion(const std::uint8_t& powerSwVersion) {
        return monitoringManager->notifySoaPowerSwVersion(powerSwVersion);
    }

    void getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return monitoringManager->getSoaPowerDeviceNormal(deviceIsNormal);
    }

    void getSoaPowerSwVersion(std::uint8_t& powerSwVersion) {
        return monitoringManager->getSoaPowerSwVersion(powerSwVersion);
    }

private:
    MonitoringManager* monitoringManager;
};


MonitoringManager::MonitoringManager() :
        mLogger(ara::log::CreateLogger("MONM", "MONM", ara::log::LogLevel::kInfo)),
        stateManagerProxyImpl{nullptr},
        otaMonitoringProxyImpl{nullptr},
        monitoringManagementSkeletonImpl{nullptr},
        moodLampProxyImpl{nullptr},
        pdwProxyImpl{nullptr},
        wiperProxyImpl{nullptr},
        roaProxyImpl{nullptr},
        drvseatProxyImpl{nullptr},
        rearCurtainProxyImpl{nullptr},
        powerProxyImpl{nullptr} {
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

    if (!startPdwProxy()) {
        return false;
    }

    if (!startWiperProxy()) {
        return false;
    }

    if (!startRoaProxy()) {
        return false;
    }

    if (!startDrvseatProxy()) {
        return false;
    }

    if (!startRearCurtainProxy()) {
        return false;
    }

    if (!startPowerProxy()) {
        return false;
    }

   // startThirtySecondTask();

    return true;
}

void
MonitoringManager::Run(int ac, char** av) {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "MonitoringManager Run";

    while (mRunning) {
        mLogger.LogInfo() << "MonitoringManager is Running";
        //test
        getSoaRoaDetectState();
        getSoaRoaDetectCount();

        eevp::control::SoaMlmStatus mlmValue;
        eevp::control::SoaRctnStatus rctnValue;
        eevp::control::SoaWiperStatus wiperValue;

        eevp::control::SoaDeviceIsNormal dNormal;

        std::uint8_t swVersion;
        getSoaRctnSwVersion(swVersion);
        mLogger.LogInfo() << "swVersion is "<<swVersion;
        eevp::control::SoaRctnMotorDir motorDir;

        if (i % 2 == 0) {
            mlmValue.colorTableIndex = 0;
            mlmValue.moodMode = eevp::control::SoaMlmMoodMode::kCARE_MOOD;
            mlmValue.brightness = 0;
            mlmValue.isNormal = eevp::control::SoaDeviceIsNormal::kNORMAL;

            rctnValue.errorState = eevp::control::SoaErrorState::kOK;
            rctnValue.curMotorDirection = eevp::control::SoaRctnMotorDir::kSTOP;
            rctnValue.curtainState = eevp::control::SoaRctnState::kFULLY_UP;
            rctnValue.isNormal = eevp::control::SoaDeviceIsNormal::kNORMAL;

            wiperValue.isAutoMode = true;
            wiperValue.mode = eevp::control::SoaWiperMode::kMIST;
            dNormal = eevp::control::SoaDeviceIsNormal::kNORMAL;

            motorDir = eevp::control::SoaRctnMotorDir::kSTOP;

            swVersion = 0;
        } else {
            mlmValue.colorTableIndex = 1;
            mlmValue.moodMode = eevp::control::SoaMlmMoodMode::kCOMPORT_MOOD;
            mlmValue.brightness = 1;
            mlmValue.isNormal = eevp::control::SoaDeviceIsNormal::kABNORMAL;

            rctnValue.errorState = eevp::control::SoaErrorState::kERROR;
            rctnValue.curMotorDirection = eevp::control::SoaRctnMotorDir::kUP;
            rctnValue.curtainState = eevp::control::SoaRctnState::kFULLY_DOWN;
            rctnValue.isNormal = eevp::control::SoaDeviceIsNormal::kABNORMAL;

            wiperValue.isAutoMode = false;
            wiperValue.mode = eevp::control::SoaWiperMode::kOFF;
            dNormal = eevp::control::SoaDeviceIsNormal::kABNORMAL;

            motorDir = eevp::control::SoaRctnMotorDir::kUP;

            swVersion = 1;
        }
/*
        notifySoaRctnStatus(rctnValue);
        notifySoaWiperStatus(wiperValue);
        notifySoaMlmStatus(mlmValue);

        notifySoaWiperDeviceNormal(dNormal);

        notifySoaRctnSwVersion(swVersion);
        notifySoaWiperSwVersion(swVersion);
        notifySoaMlmSwVersion(swVersion);
*/
        i++;

        RequestRearCurtainOperation(motorDir);
        getSoaRctnStatus(rctnValue);

        getSoaMlmStatus(mlmValue);

	    std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void
MonitoringManager::Terminate() {
    mLogger.LogInfo() << "MonitoringManager Terminate";
    mRunning = false;

    stopThirtySecondTask();
}
void
MonitoringManager::getSoaRoaDetectState() {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaRoaDetectState soaRoaDetectState;
    roaProxyImpl->getSoaRoaDetectState(soaRoaDetectState);

    if (soaRoaDetectState == eevp::control::SoaRoaDetectState::kEMPTY) {
    mLogger.LogInfo() << "kEMPTY";  
    }
    if (soaRoaDetectState == eevp::control::SoaRoaDetectState::kDETECTED_ONCE) {
    mLogger.LogInfo() << "kDETECTED_ONCE";           
    }

    mLogger.LogInfo() << "[getSoaRoaDetectState]" << ":"
                      << static_cast<int>(soaRoaDetectState);
}
void
MonitoringManager::getSoaRoaDetectCount() {
    mLogger.LogInfo() << __func__;

    uint8_t soaRoaDetectCount;
    roaProxyImpl->getSoaRoaDetectCount(soaRoaDetectCount);
    if (soaRoaDetectCount == 0) {
         mLogger.LogInfo() << "No detection";
    }
    if (soaRoaDetectCount !=0) {
        mLogger.LogInfo() << "Multiple detection";
    }
    mLogger.LogInfo() << "[getSoaRoaDetectCount]" << ":"
                      << soaRoaDetectCount;
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

        std::this_thread::sleep_for(std::chrono::seconds(30));
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

            monitoringManagementSkeletonImpl->sendeventServiceInfoSpare(sendinfo);
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

    monitoringManagementSkeletonImpl->sendupdatableserviceEvent(sendinfo);
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

    monitoringManagementSkeletonImpl->sendeventServiceStatusSpare(sendinfo);
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
        const auto& serviceInfo = pair.second;

        serviceName[index] = serviceInfo.serviceName;
        serviceStatus[index] = serviceInfo.serviceStatus;
        serviceEnable[index] = serviceInfo.serviceEnable;
        serviceControl[index] = serviceInfo.serviceControl;
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
            monitoringManagementSkeletonImpl->sendeventServiceStatusSpare(sendinfo);
            return true;
        } else {
            mLogger.LogInfo() << "MoodLamp Color Change failed!";
        }
    }

    return false;
}

void
MonitoringManager::requestVersionInfo() {
    mLogger.LogInfo() << __func__;

    eevp::ota::monitoring::type::RequestServiceInfoMap requestServiceInfoMap;
    otaMonitoringProxyImpl->requestVersionInfo(requestServiceInfoMap);

    controllerInfoMap.clear();

    for (auto& info : requestServiceInfoMap) {
        //controllerInfoMap[info.first] = info.second;
    }

    for (auto& info : controllerInfoMap) {
        //eevp::monitoring::type::ControllerServiceInfoSpare sendinfo = info.second;
        //monitoringManagementSkeletonImpl->sendeventServiceInfoSpare(sendinfo);

    }
}

bool
MonitoringManager::requestControllerServiceInfoAll(eevp::monitoring::type::ControllerServiceInfoMap& infoMap) {
    mLogger.LogInfo() << __func__;
    return true;
}

bool
MonitoringManager::requestControllerServiceStatusAll(eevp::monitoring::type::ControllerServiceStatusMap& statusMap) {
    mLogger.LogInfo() << __func__;

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

void
MonitoringManager::resetUcmTest() {
    mLogger.LogInfo() << __func__;
    otaMonitoringProxyImpl->resetUcmTest();
    return;
}


/// MoodLamp Start
void
MonitoringManager::notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateMlmStatus(fieldValue);
}

void
MonitoringManager::notifySoaMlmSwVersion(const std::uint8_t& fieldValue) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateMlmSwVersion(fieldValue);
}

void
MonitoringManager::getSoaMlmStatus(eevp::control::SoaMlmStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    moodLampProxyImpl->getSoaMlmStatus(fieldValue);
    notifySoaMlmStatus(fieldValue);
}

void
MonitoringManager::getSoaMlmSwVersion(std::uint8_t& fieldValue) {
    mLogger.LogInfo() << __func__;

    moodLampProxyImpl->getSoaMlmSwVersion(fieldValue);
    notifySoaMlmSwVersion(fieldValue);
}

void
MonitoringManager::RequestMlmSetRgbColor(const std::uint8_t& colorTableIndex) {
    mLogger.LogInfo() << __func__;

    moodLampProxyImpl->requestMlmSetRGBColor(colorTableIndex);
}

/// MoodLamp End

/// PDW start

void
MonitoringManager::notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel) {
    mLogger.LogInfo() << "__func__";

    monitoringManagementSkeletonImpl->notifyDistanceLevel(dLevel);
}

/// PDW end

/// Wiper Start

void
MonitoringManager::notifySoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateSoaWiperDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::notifySoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateSoaWiperStatus(wiperStatusValue);
}

void
MonitoringManager::notifySoaWiperSwVersion(const std::uint8_t& wiperSwVersion) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateSoaWiperSwVersion(wiperSwVersion);
}

void
MonitoringManager::getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    wiperProxyImpl->getSoaWiperDeviceNormal(deviceIsNormal);
    notifySoaWiperDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue) {
    mLogger.LogInfo() << __func__;

    wiperProxyImpl->getSoaWiperStatus(wiperStatusValue);
    notifySoaWiperStatus(wiperStatusValue);
}

void
MonitoringManager::getSoaWiperSwVersion(std::uint8_t& wiperSwVersion) {
    mLogger.LogInfo() << __func__;

    wiperProxyImpl->getSoaWiperSwVersion(wiperSwVersion);
    notifySoaWiperSwVersion(wiperSwVersion);
}

void
MonitoringManager::requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode) {
    mLogger.LogInfo() << __func__;

    wiperProxyImpl->requestWiperOperation(wiperOperationMode);
}

void
MonitoringManager::setWiperAutoSpeed(const bool& isAutoSpeed) {
    mLogger.LogInfo() << __func__;

    wiperProxyImpl->setWiperAutoSpeed(isAutoSpeed);
}

/// Wiper End

/// Roa Start

void
MonitoringManager::notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateRoaDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::notifySoaRoaSwVersion(const std::uint8_t& powerSwVersion) {
}

void
MonitoringManager::getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    roaProxyImpl->getSoaRoaDeviceNormal(deviceIsNormal);
    notifySoaRoaDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::getSoaRoaSwVersion(std::uint8_t& powerSwVersion) {
}

/// Roa End

/// DriverSeat Start

void
MonitoringManager::notifySoaDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateDrvseatDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::notifySoaDrvseatSwVersion(const std::uint8_t& powerSwVersion) {
}

void
MonitoringManager::getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    drvseatProxyImpl->getSoaDrvseatDeviceNormal(deviceIsNormal);
    notifySoaDrvseatDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::getSoaDrvseatSwVersion(std::uint8_t& powerSwVersion) {
}

/// DriverSeat End

/// RearCurtain Start

void
MonitoringManager::notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateRctnStatus(fieldValue);
}

void
MonitoringManager::notifySoaRctnSwVersion(const std::uint8_t& fieldValue) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateRctnVersion(fieldValue);
}

void
MonitoringManager::getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    rearCurtainProxyImpl->getSoaRctnStatus(fieldValue);
    notifySoaRctnStatus(fieldValue);
}

void
MonitoringManager::getSoaRctnSwVersion(std::uint8_t& fieldValue) {
    mLogger.LogInfo() << __func__;

    rearCurtainProxyImpl->getSoaRctnSwVersion(fieldValue);
    notifySoaRctnSwVersion(fieldValue);
}

void
MonitoringManager::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaErrorState errorState = rearCurtainProxyImpl->requestRearCurtainOperation(motorDir);
}

void
MonitoringManager::RequestRearCurtainPosition(const std::uint8_t& posPercentage) {
    mLogger.LogInfo() << __func__;

    rearCurtainProxyImpl->requestRearCurtainPosition(posPercentage);
}

/// RearCurtain End

/// Power Start

void
MonitoringManager::notifySoaPowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    monitoringManagementSkeletonImpl->updateRoaDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::notifySoaPowerSwVersion(const std::uint8_t& powerSwVersion) {
}

void
MonitoringManager::getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    powerProxyImpl->getSoaPowerDeviceNormal(deviceIsNormal);
    notifySoaPowerDeviceNormal(deviceIsNormal);
}

void
MonitoringManager::getSoaPowerSwVersion(std::uint8_t& powerSwVersion) {
}

/// Power End

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
MonitoringManager::startPdwProxy() {
    mLogger.LogInfo() << __func__;
    pdwProxyImpl = std::make_shared<eevp::pdw::PdwProxyImpl>();
    auto pdwListener = std::make_shared<PdwListener>(this);
    pdwProxyImpl->setEventListener(pdwListener);
    pdwProxyImpl->init();
    return true;
}

bool
MonitoringManager::startWiperProxy() {
    mLogger.LogInfo() << __func__;
    wiperProxyImpl = std::make_shared<eevp::control::wiper::WiperProxyImpl>();
    auto wiperListener = std::make_shared<WiperListener>(this);
    wiperProxyImpl->setEventListener(wiperListener);
    wiperProxyImpl->init();
    return true;
}

bool
MonitoringManager::startRoaProxy() {
    mLogger.LogInfo() << __func__;
    roaProxyImpl = std::make_shared<eevp::control::roa::RoaProxyImpl>();
    auto roaListener = std::make_shared<RoaListener>(this);
    roaProxyImpl->setEventListener(roaListener);
    roaProxyImpl->init();
    return true;
}

bool
MonitoringManager::startDrvseatProxy() {
    mLogger.LogInfo() << __func__;
    drvseatProxyImpl = std::make_shared<eevp::control::drvseat::DrvseatProxyImpl>();
    auto drvseatListener = std::make_shared<DrvseatListener>(this);
    drvseatProxyImpl->setEventListener(drvseatListener);
    drvseatProxyImpl->init();
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

bool
MonitoringManager::startPowerProxy() {
    mLogger.LogInfo() << __func__;
    powerProxyImpl = std::make_shared<eevp::control::power::PowerProxyImpl>();
    auto powerListener = std::make_shared<PowerListener>(this);
    powerProxyImpl->setEventListener(powerListener);
    powerProxyImpl->init();
    return true;
}
} // namespace monitoring
} // namespace eevp
