#include "consumer.h"
#include "ara/exec/execution_client.h"
#include <random>

namespace swc 
{

std::atomic_bool Consumer::mRunning(false);
Consumer::Consumer()
    : mLogger(ara::log::CreateLogger("TCON", "SWC", ara::log::LogLevel::kInfo))
{
    std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);
}

Consumer::~Consumer()
{
}

void Consumer::SignalHandler(std::int32_t /*signal*/)
{
    mRunning = false;
}

bool Consumer::Start()
{
    mLogger.LogInfo() << "Consumer Start";
    ara::core::InstanceSpecifier specifier("DummyTest_Consumer/AA/DummyTest_RPort");
    auto callback = [&](auto services, auto handler) {
        StartFindCallback(services, handler);
    };
    auto ret = DummyTestProxy::StartFindService(callback, specifier);
    if (ret.HasValue()) {
        mLogger.LogInfo() << "DummyTestProxy Start Find Service Success";
        mRunning = true;
        return true;
    } else {
        mLogger.LogInfo() << "DummyTestProxy Start Find Service Failed";
        return false;
    }
}

void Consumer::Run()
{
    mLogger.LogInfo() << "Consumer Run";
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "Consumer Running State";
    } else {
        mLogger.LogInfo() << exec.Error().Message();
    }
    while (mRunning) {
        if (mRPort == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }
        FieldGetter();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        MethodRequest();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        FieldSetter();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Consumer::Terminate()
{
    mLogger.LogInfo() << "Consumer Terminate";
    mRunning = false;
    if (mRPort) {
        mRPort->StopFindService(*mFindHandle);
        delete mFindHandle;
        mRPort->DeviceEvent.Unsubscribe();
        mRPort->DeviceField.Unsubscribe();
        mRPort = nullptr;
    }
}

void Consumer::StartFindCallback(ara::com::ServiceHandleContainer<DummyTestProxy::HandleType> services, ara::com::FindServiceHandle handle)
{
    DummyTestProxy::HandleType proxyHandle;
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
        if (service.GetServiceHandle().serviceId != 5152) {
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
        mRPort = std::make_unique<DummyTestProxy>(proxyHandle);
        mFindHandle = new ara::com::FindServiceHandle(handle);
        mProxyHandle = proxyHandle;
        SubscribeEvent();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SubscribeField();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (findFlag == false) {
        mLogger.LogInfo() << "Not available ServiceProvider";
        mRPort = nullptr;
    }
}

void Consumer::StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state) 
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

void Consumer::MethodRequest()
{
    if (mRunning == false) {
        return;
    }
    if (mRPort) {
        std::random_device randomDevice;
        std::default_random_engine randomEngine{randomDevice()};
        std::uniform_int_distribution<std::int64_t> valueGenerator{-1000, 1000};

        std::int16_t devicenumber = valueGenerator(randomEngine);
        auto requestdevice = mRPort->DeviceMethod(devicenumber);

        std::chrono::time_point<std::chrono::system_clock> deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        auto request_statusdevice = requestdevice.wait_until(deadline);

        if (request_statusdevice == ara::core::future_status::ready) {
            auto response = requestdevice.GetResult();

            if (response.HasValue()){
                mLogger.LogInfo() << "[DEVICE METHOD RESPONSE] (" << response.Value().DeviceState << ")";
            }
        } else {
            mLogger.LogError() << "[DEVICE METHOD RESPONSE]  timeout";
            return;
        }
        if (mRunning == false) {
            return;
        }
    }
}

void Consumer::FieldGetter()
{
    if (mRunning == false) {
        return;
    }
    if (mRPort) {

        mLogger.LogInfo() << "[DEVICE FIELD GET REQUEST] ()";
        auto request = mRPort->DeviceField.Get();
        std::chrono::time_point<std::chrono::system_clock> deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        auto request_status = request.wait_until(deadline);
        if (request_status == ara::core::future_status::ready) {
            auto response = request.GetResult();
            if (response.HasValue()){
                mLogger.LogInfo() << "[DEVICE FIELD GET RESPONSE] (" << response.Value().DeviceNum << ":" << response.Value().DeviceState << ")";
            }
        } else {
            mLogger.LogError() << "[FIELD GET RESPONSE] timeout";
            return;
        }
    }
}

void Consumer::FieldSetter()
{
    if (mRunning == false) {
        return;
    }
    if (mRPort) {
        fields::DeviceField::FieldType value;
        std::random_device randomDevice;
        std::default_random_engine randomEngine{randomDevice()};

        std::uniform_int_distribution<std::int16_t> shortGen{-1000, 1000};
        value.DeviceNum = shortGen(randomEngine);
        value.DeviceState = true;

        mLogger.LogInfo() << "[FIELD SET REQUEST] (" << value.DeviceNum << ":"
                <<value.DeviceState << ")";

        auto request = mRPort->DeviceField.Set(value);
        std::chrono::time_point<std::chrono::system_clock> deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        auto request_status = request.wait_until(deadline);
        if (request_status == ara::core::future_status::ready) {
            auto response = request.GetResult();
            if (response.HasValue()) {
                mLogger.LogInfo() << "[FIELD SET RESPONSE] ("<<response.Value().DeviceNum<<":"
                <<response.Value().DeviceState<<")";
            } 
        } else {
            mLogger.LogError() << "[FIELD SET RESPONSE] timeout";
            return;
        }
    }
}

void Consumer::SubscribeEvent()
{
    if (mRPort->DeviceEvent.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }
    auto eventCallback = [&](auto state) {
        StateChangeCallback("DeviceEvent", state);
    };
    mRPort->DeviceEvent.SetSubscriptionStateChangeHandler(eventCallback);
    auto receiveEvent = [&] () {
        GetEventData();
    };
    mRPort->DeviceEvent.SetReceiveHandler(receiveEvent);
    mRPort->DeviceEvent.Subscribe(10);
}

void Consumer::SubscribeField()
{

    if (mRPort->DeviceField.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }
    auto fieldCallback = [&](auto state) {
        StateChangeCallback("DeviceField", state);
    };
    mRPort->DeviceField.SetSubscriptionStateChangeHandler(fieldCallback);
    auto receiveEvent = [&] () {
        GetFieldValue();
    };
    mRPort->DeviceField.SetReceiveHandler(receiveEvent);
    mRPort->DeviceField.Subscribe(10);
}

/// @brief Process received event data 
void Consumer::GetEventData()
{
    if (mRPort->DeviceEvent.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }
    mRPort->DeviceEvent.GetNewSamples([&](auto noti){
        mLogger.LogInfo() << "[EVENT NOTIFICATION] ("<<noti->DeviceNum<<":"
            <<noti->DeviceState<<")";
    });
}

void Consumer::GetFieldValue()
{
    if (mRPort->DeviceField.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }
    mRPort->DeviceField.GetNewSamples([&](auto noti){
        mLogger.LogInfo() << "[FIELD NOTIFICATION] ("<<noti->DeviceNum<<":"
            <<noti->DeviceState<<")";
    });
}
}
