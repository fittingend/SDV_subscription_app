#include "provider.h"

#include "ara/exec/execution_client.h"
namespace swc
{
std::atomic_bool Provider::mRunning(false);

Provider::Provider()
    : mLogger(ara::log::CreateLogger("TPRV", "SWC", ara::log::LogLevel::kInfo)),
    i (0), tf(false)
{
    std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);
}

void Provider::SignalHandler(std::int32_t /*signal*/)
{
    mRunning = false;
}

bool Provider::Start()
{
    ara::core::InstanceSpecifier specifier("DummyTest_Provider/AA/DummyTest_PPort");
    // initialize service skeleton
    //mPPortImpl = std::make_unique<TestSrvSkeletonImpl>(specifier, ara::com::MethodCallProcessingMode::kPoll);
    mPPortImpl = std::make_unique<DummyTestSkeletonImpl>(specifier, ara::com::MethodCallProcessingMode::kEventSingleThread);
    // offer service
    auto offered = mPPortImpl->OfferService();
    if (offered.HasValue()) {
        mLogger.LogInfo() << "DummyTest Provider Offer Service";
        mRunning = true;
        return true;
    } else {
        mLogger.LogInfo() << "DummyTest Provider Offer Service Failed";
        return false;
    }
}

void Provider::Run()
{
    // loop start
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "Provider Running State";
    } else {
        mLogger.LogInfo() << exec.Error().Message();
    }
    while (mRunning) {
        SendEvent();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        SendNotification();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

// terminate service instance
void Provider::Terminate()
{
    if (mPPortImpl) {
        mPPortImpl->StopOfferService();
        mLogger.LogInfo() << "Provider Stop Offer Service";
    }
}

void Provider::SendEvent()
{
    if (mRunning == false) {
        return;
    }
    if (mPPortImpl == nullptr) {
        return;
    }
    events::DeviceEvent::SampleType ddata;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> NumGen(1, 10);
    ddata.DeviceNum = i++;//NumGen(gen);

    std::bernoulli_distribution boolGen(0.5);
    tf = !tf;
    ddata.DeviceState = tf;//boolGen(gen);

    mLogger.LogInfo() << "[DEVICE EVENT NOTIFICATION] (" << ddata.DeviceNum << ":"
            << ddata.DeviceState << ")";

    mPPortImpl->DeviceEvent.Send(ddata);

}

void Provider::SendNotification()
{
    if (mRunning == false) {
        return;
    }
    if (mPPortImpl == nullptr) {
        return;
    }
    fields::DeviceField::FieldType dvalue;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> NumGen(1, 10);
    dvalue.DeviceNum = i;//NumGen(gen);

    std::bernoulli_distribution boolGen(0.5);
    dvalue.DeviceState = tf;//boolGen(gen);

    mLogger.LogInfo() << "[DEVICE FIELD NOTIFICATION] (" << dvalue.DeviceNum << ":"
            << dvalue.DeviceState << ")";

    mPPortImpl->DeviceField.Update(dvalue);
}
}
