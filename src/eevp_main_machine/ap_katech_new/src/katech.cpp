#include "katech.h"
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

    void notifyRoaDetectState(const eevp::control::SoaRoaDetectState & value) {
        return katech->notifyRoaDetectState(value);
    }

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

    // if (!startKatechStub()) {
    //     return false;
    // }

    if (!startRoaProxy()) {
        return false;
    }

    //eventProcessingThreadHandle = std::thread(&MonitoringManager::eventProcessingThread, this);
    mLogger.LogInfo() << "KATECH app end of Start";

    startRoutineTask();

    return true;
}

void
KATECH::Run() {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "KATECH app Run";

    while (mRunning) {
        mLogger.LogInfo() << "KATECH app is Running";

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
        getSoaRoaDetectState();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void 
KATECH::StartFindCallback(ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> services, ara::com::FindServiceHandle handle)
{
    eevp::control::proxy::SoaRoaProxy::HandleType proxyHandle;
    bool findFlag = false;
    bool offeredFlag = false;
    mLogger.LogInfo() << "Current offered service list";
    for (auto service : services)
    {   
        mLogger.LogInfo() 
            << "ServiceID : " << service.GetServiceHandle().serviceId
            << "InstanceID : " << service.GetServiceHandle().instanceId
            << "MajorVersion : "<< service.GetServiceHandle().version.major
            << "MinorVesion : " << service.GetServiceHandle().version.minor ;
        if (service.GetServiceHandle().serviceId != 4947) {
            continue;
        }
        if (service.GetServiceHandle().version.major != 1) {
            continue;
        }
        if (mProxyHandle == service) {
            offeredFlag = true;
        }
        findFlag = true;
        proxyHandle = service;
    }

    if ((offeredFlag == false)&&(findFlag == true)) {
        mRPort = std::make_unique<eevp::control::proxy::SoaRoaProxy>(proxyHandle);
        mFindHandle = new ara::com::FindServiceHandle(handle);
        mProxyHandle = proxyHandle;
        SubscribeField();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (findFlag == false) {
        mLogger.LogInfo() << "Not available ServiceProvider";
        mRPort = nullptr;
    }
}


void KATECH::SubscribeField()
{

    if (mRPort->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }
    auto fieldCallback = [&](auto state) {
        StateChangeCallback("soaRoaDetectState", state);
    };
    mRPort->soaRoaDetectState.SetSubscriptionStateChangeHandler(fieldCallback);
    auto receiveEvent = [&] () {
        GetFieldValue();
    };
    mRPort->soaRoaDetectState.SetReceiveHandler(receiveEvent);
    mRPort->soaRoaDetectState.Subscribe(10);
}
void KATECH::StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state) 
{
    switch (state)
    {
    case ara::com::SubscriptionState::kNotSubscribed : 
        mLogger.LogInfo() << callsign<< " : state changed to kNotSubscribed";
        break;
    case ara::com::SubscriptionState::kSubscriptionPending : 
        mLogger.LogInfo() << callsign<< " : state changed to kSubscriptionPending";
        break;
    case ara::com::SubscriptionState::kSubscribed : 
        mLogger.LogInfo() << callsign<< " : state changed to kSubscribed";
        break;
    default:
        mLogger.LogError() << callsign<< " : not allowed state";
        break;
    }
}
void KATECH::GetFieldValue()
{
    if (mRPort->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }
    mRPort->soaRoaDetectState.GetNewSamples([&](auto noti){
        mLogger.LogInfo() << "TO DO: subscription state";
        // mLogger.LogInfo() << "[soaRoaDetectState FIELD NOTIFICATION] ("<<noti->DeviceNum<<":"
        //     <<noti->DeviceState<<")";
    });
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
