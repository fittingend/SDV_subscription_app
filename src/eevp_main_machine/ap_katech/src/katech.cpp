#include "../include/eevp/control/katech.h"

#include "ara/exec/execution_client.h"
#include <ctime>

// #define demo

namespace eevp {
namespace control {

std::atomic_bool KATECH::mRunning(false);

/*class KatechListener : public IKatechListener {
public:
    KatechListener(KATECH* katech_app) : katech(katech_app) {}

private:
    KATECH* katech;
};*/

class RoaListener : public eevp::control::roa::IRoaListener {
public:
    RoaListener(KATECH* katech_app) : katech(katech_app) {}

    // void notifyRoaDetectState(const eevp::control:: & value) {
    //     return katech->notifyRoaDetectState(value);
    // }

    void getSoaRoaDetectState() {
        return katech->getSoaRoaDetectState();
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
    mLogger.LogInfo() << "KATECH app Start";

    mRunning = true;

    if (!setRunningState()) {
        return false;
    }

    if (!startKatechStub()) {
        return false;
    }

    if (!startRoaProxy()) {
        return false;
    }

    //eventProcessingThreadHandle = std::thread(&MonitoringManager::eventProcessingThread, this);

    //startThirtySecondTask();

    return true;
}

void
KATECH::Run() {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "KATECH app Run";

    while (mRunning) {
        mLogger.LogInfo() << "KATECH app is Running";
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
KATECH::Terminate() {
    mLogger.LogInfo() << "MonitoringManager Terminate";
    mRunning = false;

    //stopThirtySecondTask();
    if (eventProcessingThreadHandle.joinable()) {
        eventProcessingThreadHandle.join();
    }
}
/*
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
*/
void
KATECH::getSoaRoaDetectState() {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaRoaDetectState soaRoaDetectState;
    roaProxyImpl->getterSoaRoaDetectState(soaRoaDetectState);
    bool take_action = 0; 

    if (soaRoaDetectState == eevp::control::SoaRoaDetectState::kDETECTED_SEVERAL) {
        take_action = 1;
    }

    mLogger.LogInfo() << "[getSoaRoaDetectState]" << ":"
                      << static_cast<int>(soaRoaDetectState);
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

bool
KATECH::startKatechStub() {
    mLogger.LogInfo() << __func__;
    ara::core::InstanceSpecifier specifier("KATECH/AA/KATEHCH_PPort");
    //pport 추후에 만들필요 있음?
    //katechSkeletonImpl = std::make_shared<eevp::control::KatechSkeletonImpl>(specifier);
    //auto katechListener = std::make_shared<KatechListener>(this);
    //katechSkeletonImpl->setEventListener(katechListener);
    //katechSkeletonImpl->OfferService();
    return true;
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
} // namespace control
} // namespace eevp
