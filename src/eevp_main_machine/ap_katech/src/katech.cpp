#include "katech.h"
#include "ara/exec/execution_client.h"
#include <ctime>

// #define demo

namespace eevp {
namespace control {

std::atomic_bool KATECH::mRunning(false);

// class KatechListener : public IKatechListener {
// public:
//     KatechListener(KATECH* katech_app) : katech(katech_app) {}

// private:
//     KATECH* katech;
// };

class RoaListener : public eevp::control::roa::KatechRoaListener {
public:
    RoaListener(KATECH* katech_app) : katech(katech_app) {}

    // void notifyRoaDetectState(const eevp::control::SoaRoaDetectState & value) {
    //     return katech->notifyRoaDetectState(value);
    // }

    void notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return katech->notifySoaRoaDeviceNormal(deviceIsNormal);
    }

    void notifySoaRoaSwVersion(const std::uint8_t& powerSwVersion) {
        return katech->notifySoaRoaSwVersion(powerSwVersion);
    }

    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
        return katech->getSoaRoaDeviceNormal(deviceIsNormal);
    }

    void getSoaRoaSwVersion(std::uint8_t& powerSwVersion) {
        return katech->getSoaRoaSwVersion(powerSwVersion);
    }

private:
    KATECH* katech;
};

KATECH::KATECH() :
        mLogger(ara::log::CreateLogger("KATC", "KATC", ara::log::LogLevel::kInfo)),
        //katechSkeletonImpl{nullptr},
        roaProxyImpl{nullptr}{
    mLogger.LogInfo() << __func__;
    // std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);
}

KATECH::~KATECH() {
}

void
KATECH::SignalHandler(std::int32_t /*signal*/) {
    mRunning = false;
}

bool
KATECH::Start() {
    mLogger.LogInfo() << __func__;

    mRunning = true;

    if (!setRunningState()) {
        return false;
    }

    if (!startRoaProxy()) {
        return false;
    }

    // if (!startKatechSkeleton()) {
    //     return false;
    // }

    //eventProcessingThreadHandle = std::thread(&MonitoringManager::eventProcessingThread, this);
    mLogger.LogInfo() << "KATECH app end of Start";

    //startRoutineTask();

    return true;
}

void
KATECH::Run() {
    mLogger.LogInfo() << __func__;

    while (mRunning) {
        mLogger.LogInfo() << "KATECH app is Running";

    eevp::control::SoaRoaDetectState soaRoaDetectState;
    std::uint8_t soaRoaDetectCount;
    getSoaRoaDetectState(soaRoaDetectState);
    getSoaRoaDetectCount(soaRoaDetectCount);

	std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void
KATECH::Terminate() {
    mLogger.LogInfo() << "KATECH app terminating";
    mRunning = false;

    //stopThirtySecondTask();
    if (eventProcessingThreadHandle.joinable()) {
        eventProcessingThreadHandle.join();
    }
}

void
KATECH::startRoutineTask() {
    routineTaskRunning = true;
    mLogger.LogInfo() << "KATECH routineTask starting";
    routineThread = std::thread(&KATECH::routineTask, this);
}

void
KATECH::stopRoutineTask() {
    routineTaskRunning = false;
    if (routineThread.joinable()) {
        routineThread.join();
    }
}

void
KATECH::routineTask() {
    while (routineTaskRunning) {
        //requestVersionInfo();
        mLogger.LogInfo() << "KATECH routineTask running";
        // getSoaRoaDetectCount();
        // getSoaRoaDetectState();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void
KATECH::getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState){
    mLogger.LogInfo() << __func__;

    //eevp::control::SoaRoaDetectState soaRoaDetectState;
    roaProxyImpl->getSoaRoaDetectState(soaRoaDetectState);

    if (soaRoaDetectState == eevp::control::SoaRoaDetectState::kDETECTED_SEVERAL) {
        mLogger.LogInfo() << "detected state is kDETECTED_SEVERAL";

    }
    if (soaRoaDetectState == eevp::control::SoaRoaDetectState::kEMPTY) {
        mLogger.LogInfo() << "detected state is empty";
    }
    mLogger.LogInfo() << "[getSoaRoaDetectState]" << ":"
                      << static_cast<int>(soaRoaDetectState);
}

void
KATECH::getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount) {
    mLogger.LogInfo() << __func__;

    //uint8_t soaRoaDetectCount;
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
bool
KATECH::setRunningState() {
    mLogger.LogInfo() << __func__;
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "KATECH app in Running State";
    } else {
        mLogger.LogError() << exec.Error().Message();
        return false;
    }
    return true;
}

// bool
// KATECH::startKatechSkeleton() {
//     mLogger.LogInfo() << __func__;
//     ara::core::InstanceSpecifier specifier("KATECH/AA/PPortRearCurtain");
//     //추후 PPortKatech 으로 바꿔야..
//     katechSkeletonImpl = std::make_shared<eevp::control::KatechSkeletonImpl>(specifier);
//     auto katechListener = std::make_shared<KatechListener>(this);
//     katechSkeletonImpl->setEventListener(katechListener);
//     katechSkeletonImpl->OfferService();
//     return true;
// }

void
KATECH::notifyRoaDetectState(const eevp::control::SoaRoaDetectState& fieldValue) {
    mLogger.LogInfo() << __func__;

     if (fieldValue == eevp::control::SoaRoaDetectState::kEMPTY) {
        mLogger.LogInfo() << "test";

    } else if (fieldValue == eevp::control::SoaRoaDetectState::kDETECTED_SEVERAL) {
    }

    // if (fieldValue.curMotorDirection == eevp::control::SoaRctnMotorDir::kUP) {
    //     info.serviceControl = "UP";
    // } else if (fieldValue.curMotorDirection == eevp::control::SoaRctnMotorDir::kDOWN) {
    //     info.serviceControl = "DOWN";
    // }

    // eevp::monitoring::type::ControllerServiceStatusSpare sendinfo = {
    //                 info.serviceName,
    //                 info.serviceStatus,
    //                 info.serviceEnable,
    //                 info.serviceControl};

    // enqueueEvent(Event(sendinfo));
}
void
KATECH::notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;
    //TODO
    //monitoringManagementSkeletonImpl->updateRoaDeviceNormal(deviceIsNormal);
}
void
KATECH::notifySoaRoaSwVersion(const std::uint8_t& fieldValue) {
    mLogger.LogInfo() << __func__;
    //TODO
    //monitoringManagementSkeletonImpl->updateRoaDeviceNormal(deviceIsNormal);
}
void
KATECH::getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    roaProxyImpl->getSoaRoaDeviceNormal(deviceIsNormal);
    notifySoaRoaDeviceNormal(deviceIsNormal);
}

void
KATECH::getSoaRoaSwVersion(std::uint8_t& powerSwVersion) {
}

bool
KATECH::startRoaProxy() {
    mLogger.LogInfo() << __func__;
    roaProxyImpl = std::make_shared<eevp::control::roa::RoaProxyImpl>();
    auto roaListener = std::make_shared<RoaListener>(this);
    roaProxyImpl->setEventListener(roaListener);
    roaProxyImpl->init();
    return true;
}

// bool 
// KATECH::startRearCurtainSkeleton(){
//     mLogger.LogInfo() << __func__;
//     ara::core::InstanceSpecifier specifier("KATECH/AA/PPortRearCurtain");
//     // initialize service skeleton
//     mPPortImpl = std::make_unique<eevp::control::KatechSkeletonImpl>(specifier);
//     mPPortImpl = std::make_shared<eevp::control::SoaRcurtainSkeletonImpl>(specifier);
//     auto monitoringManagementListener = std::make_shared<MonitoringManagementListener>(this);
//     monitoringManagementSkeletonImpl->setEventListener(monitoringManagementListener);
//     monitoringManagementSkeletonImpl->OfferService();
//     auto offered = mPPortImpl->OfferService();
//     if (offered.HasValue()) {
//         mLogger.LogInfo() << " Rearcurtain Offer Service";
//         mRunning = true;
//         return true;
//     } else {
//         mLogger.LogInfo() << "Rearcurtain Offer Service Failed";
//         return false;
//     }
//     return true;
// }
} // namespace control
} // namespace eevp
