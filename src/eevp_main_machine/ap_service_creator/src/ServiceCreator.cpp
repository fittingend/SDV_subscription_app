#include "ara/exec/execution_client.h"
#include <ctime>
#include "ServiceCreator.h"
#include "ara/log/logger.h"

namespace eevp {
namespace simulation {

std::atomic_bool ServiceCreator::mRunning(false);

ServiceCreator::ServiceCreator() :
        mLogger(ara::log::CreateLogger("SVCC", "SVCC", ara::log::LogLevel::kInfo)){
    mLogger.LogInfo() << __func__;
    // std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);
}

ServiceCreator::~ServiceCreator() {
}

void
ServiceCreator::SignalHandler(std::int32_t /*signal*/) {
    mRunning = false;
}
bool
ServiceCreator::Start() {
    mLogger.LogInfo() << __func__;
    mRunning = true;

    if (!setRunningState()) {
        return false;
    }
    
    return true;
}

void
ServiceCreator::Run() {
    mLogger.LogInfo() << __func__;

    if (mRunning) 
    {
        mLogger.LogInfo() << "Service Creator running";
        //std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
}

void
ServiceCreator::Terminate() 
{
    mLogger.LogInfo() << __func__;
    mRunning = false;
}

bool
ServiceCreator::setRunningState() {
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "ServiceCreator app in Running State";
    } else {
        mLogger.LogError() << exec.Error().Message();
        return false;
    }
    return true;
}

}
}