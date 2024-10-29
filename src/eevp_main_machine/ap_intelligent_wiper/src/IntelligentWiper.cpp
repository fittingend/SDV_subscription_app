#include "intelligent_wiper.h"
#include "ara/exec/execution_client.h"
#include <ctime>

namespace eevp {
namespace simulation {

//eevp::simulation::wi soaRearCurtainStatus;

std::atomic_bool IntelligentWiper::mRunning(false);

class WiperListener : public eevp::simulation::roa::IWiperListener {
public:
    WiperListener(IntelligentWiper* app) : intelligentWiper(app) {}
    
    void notifyUserControl(std::uint8_t& value) {
        return intelligentWiper->notifyUserControl(value);
    }
private:
    IntelligentWiper* intelligentWiper;
};

IntelligentWiper::IntelligentWiper()
    : mLogger(ara::log::CreateLogger("INTW", "INTW", ara::log::LogLevel::kInfo)),
      wiperProxyImpl{nullptr},
      accrPedalProxyImpl{nullptr},
      brakePedalProxyImpl{nullptr},
      gearProxyImpl{nullptr},
      vehSpdProxyImpl{nullptr} 
{
    // Log the constructor function name for initialization tracking
    mLogger.LogInfo() << __func__;
    
    // Set up signal handling for graceful termination
    // std::signal(SIGINT, SignalHandler); // Uncomment if SIGINT handling is needed
    std::signal(SIGTERM, SignalHandler);
}

IntelligentWiper::~IntelligentWiper() {
    // Destructor implementation (empty for now)
}

void
IntelligentWiper::SignalHandler(std::int32_t /*signal*/) {
    mRunning = false;
}

bool
IntelligentWiper::Start() {
    mLogger.LogInfo() << __func__;

    mRunning = true;

    if (!setRunningState()) {
        return false;
    }

    if (!startWiperProxy()) {
        return false;
    }

    return true;
}

void
IntelligentWiper::Run() {
    mLogger.LogInfo() << __func__;
    while (mRunning) 
    {
        mLogger.LogInfo() << "Service Creator running";
    }
}

void
IntelligentWiper::Terminate() 
{
    mLogger.LogInfo() << __func__;
    mRunning = false;
}

bool
KATECH::setRunningState() {
    ara::exec::ExecutionClient executionClient;
    auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (exec.HasValue()) {
        mLogger.LogInfo() << "Intelligent wiper app in Running State";
    } else {
        mLogger.LogError() << exec.Error().Message();
        return false;
    }
    return true;
}

// /// ROA Start

// void
// KATECH::getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState)
// {
//     roaProxyImpl->getSoaRoaDetectState(soaRoaDetectState);
//     mLogger.LogInfo() << "[getSoaRoaDetectState]:" << static_cast<std::uint8_t>(soaRoaDetectState);
// }

// void
// KATECH::getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount) 
// {
//     roaProxyImpl->getSoaRoaDetectCount(soaRoaDetectCount);
//     mLogger.LogInfo() << "[getSoaRoaDetectCount]" << ":"
//                       << soaRoaDetectCount;
// }

// /// ROA End


/// RearCurtain Start
void IntelligentWiper::notifyUserControl()
{
    mLogger.LogInfo() << __func__;

    

}

eevp::simulation::BCM_ReturnCode ServiceCreator::stopWiping()
{
    mLogger.LogInfo() << __func__;
    return BCM_ReturnCode::SUCCESS;
}

eevp::simulation::BCM_ReturnCode ServiceCreator::startWiping()
{
    mLogger.LogInfo() << __func__;
    return BCM_ReturnCode::SUCCESS;
}

eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
{
    mLogger.LogInfo() << __func__;
    wiperSkeletonImpl->updateWipingLevel(wipingLevel);
    return BCM_ReturnCode::SUCCESS;
}

eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
{
    mLogger.LogInfo() << __func__;
    wiperSkeletonImpl->updateWipingLevel(wipingLevel);
    return BCM_ReturnCode::SUCCESS;
}

eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingInterval(std::uint16_t &wipingInterval)
{
    mLogger.LogInfo() << __func__;
    wiperSkeletonImpl->updateWipingInterval(wipingInterval);
    return BCM_ReturnCode::SUCCESS;
}

std::uint16_t ServiceCreator::getWipingInterval()
{
    mLogger.LogInfo() << __func__;
    wiperProxyImpl->getWipingInterval();
    return 0;
}

eevp::simulation::BCM_WipingLevel ServiceCreator::getWipingLevel()
{
    mLogger.LogInfo() << __func__;
    wiperProxyImpl->getWipingLevel();
    return wiperRecv.wipingLevel;
}
void
IntelligentWiper::getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    rearCurtainProxyImpl->getSoaRctnStatus(fieldValue);
    if (fieldValue.errorState == eevp::control::SoaErrorState::kOK) {
        mLogger.LogInfo() << "getSoaRctnStatus is kOK";
    }
    if (fieldValue.errorState == eevp::control::SoaErrorState::kERROR) {
    mLogger.LogInfo() << "getSoaRctnStatus is kERROR";
    }
}

bool
KATECH::requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
    mLogger.LogInfo() << __func__;

    eevp::control::SoaErrorState errorState = rearCurtainProxyImpl->requestRearCurtainOperation(motorDir);
    if (errorState == eevp::control::SoaErrorState::kERROR) {
        mLogger.LogInfo() << "rearcurtain opration is kERROR";
        return false;
    }
    if (errorState == eevp::control::SoaErrorState::kOK) {
        mLogger.LogInfo() << "rearcurtain operation is kOK";
        return true;
    }
}

void
KATECH::requestRearCurtainPosition(const std::uint8_t& posPercentage) {
    mLogger.LogInfo() << __func__;

    rearCurtainProxyImpl->requestRearCurtainPosition(posPercentage);
}


bool IntelligentWiper::startWiperProxy()
{
    mLogger.LogInfo() << __func__;

    wiperProxyImpl = std::make_shared<eevp::simulation::WiperProxyImpl>();
    auto wiperListener = std::make_shared<WiperListener>(this);
    wiperProxyImpl->setEventListener(wiperListener);
    wiperProxyImpl->init();
    return true;
}


} // namespace control
} // namespace eevp
