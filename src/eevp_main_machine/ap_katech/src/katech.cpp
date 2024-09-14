#include "katech.h"
#include "ara/exec/execution_client.h"
#include <ctime>

namespace eevp {
namespace control {

eevp::control::SoaRctnStatus soaRearCurtainStatus;

std::atomic_bool KATECH::mRunning(false);

class RoaListener : public eevp::control::roa::IRoaListener {
public:
    RoaListener(KATECH* katech_app) : katech(katech_app) {}
    
    void notifySoaRoaDetectCount(std::uint8_t& value) {
        return katech->notifySoaRoaDetectCount(value);
    }
private:
    KATECH* katech;
};

/*
class RearCurtainListener : public eevp::control::rearcurtain::IRearCurtainListener {
public:
    RearCurtainListener(KATECH* katech_app) : katech(katech_app) {}

    void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) {
        return katech->notifySoaRctnStatus(fieldValue);
    }
    void getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) {
        return katech->getSoaRctnStatus(fieldValue);
    }

private:
    KATECH* katech;
};
*/

KATECH::KATECH() :
        mLogger(ara::log::CreateLogger("KATC", "KATC", ara::log::LogLevel::kInfo)),
        rearCurtainProxyImpl{nullptr},
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

    if (!startRearCurtainProxy()) {
        return false;
    }
   
    return true;
}

void
KATECH::Run() {
    mLogger.LogInfo() << __func__;

    while (mRunning) 
    {
        eevp::control::SoaRoaDetectState soaRoaDetectState;
        std::uint8_t soaRoaDetectCount;
        getSoaRoaDetectState(soaRoaDetectState);
        getSoaRoaDetectCount(soaRoaDetectCount);
	    std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void
KATECH::Terminate() 
{
    mRunning = false;
}

bool
KATECH::setRunningState() {
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

/// ROA Start

void
KATECH::getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState)
{
    roaProxyImpl->getSoaRoaDetectState(soaRoaDetectState);
    mLogger.LogInfo() << "[getSoaRoaDetectState]:" << static_cast<std::uint8_t>(soaRoaDetectState);
}

void
KATECH::getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount) 
{
    roaProxyImpl->getSoaRoaDetectCount(soaRoaDetectCount);
    mLogger.LogInfo() << "[getSoaRoaDetectCount]" << ":"
                      << soaRoaDetectCount;
}

/// ROA End


/// RearCurtain Start

void
KATECH::notifySoaRoaDetectCount(const std::uint8_t& detectCount) {
    mLogger.LogInfo() << __func__;
    mLogger.LogInfo() << "notified count:" << detectCount;
    
   if (checkRctnReady())
    {
        switch (detectCount)
        {
            case 0:
                if (soaRearCurtainStatus.curtainState == eevp::control::SoaRctnState::kFULLY_DOWN)
                {
                    // do nothing; rear curtain is already open
                    break;
                }
                else
                {
                    // when rear curtain is partially open or fully up 
                    bool result = requestRearCurtainOperation(eevp::control::SoaRctnMotorDir::kDOWN);
                    while (result)
                    {
                        mLogger.LogInfo() << "waiting for rear curtain operation to finish";
                        std::this_thread::sleep_for(std::chrono::seconds(RCTN_OP_TIME));
                        getSoaRctnStatus(soaRearCurtainStatus);
                        if (soaRearCurtainStatus.curtainState == eevp::control::SoaRctnState::kFULLY_DOWN)
                        {
                            mLogger.LogInfo() << "rear curtain operation finished";
                            break;
                        }
                    }
                    if (!result) 
                    {
                        mLogger.LogInfo() << "rear curtain operation unsuccessful";
                    }
                }
                break;
            
            case 1:
                if (soaRearCurtainStatus.curtainState == eevp::control::SoaRctnState::kFULLY_UP)
                {
                    // do nothing; rear curtain is already closed 
                    break;
                }
                else
                {
                    // when rear curtain is partially open or fully down 
                    bool result = requestRearCurtainOperation(eevp::control::SoaRctnMotorDir::kUP);
                    while (result)
                    {
                        mLogger.LogInfo() << "waiting for rear curtain operation to finish";
                        std::this_thread::sleep_for(std::chrono::seconds(RCTN_OP_TIME));
                        getSoaRctnStatus(soaRearCurtainStatus);
                        mLogger.LogInfo() << "waith" << static_cast<std::uint8_t>(soaRearCurtainStatus.curtainState);
                        if (soaRearCurtainStatus.curtainState == eevp::control::SoaRctnState::kFULLY_UP)
                        {
                            mLogger.LogInfo() << "rear curtain operation finished";
                            break;
                        }
                    }
                    if (!result) 
                    {
                        mLogger.LogInfo() << "rear curtain operation unsuccessful";
                    }
                }
                break;
            
            default:
                mLogger.LogInfo() << "Unknown detectCount value";
                break;
        }
    }
}

bool
KATECH::checkRctnReady(){
    mLogger.LogInfo() << __func__;
    getSoaRctnStatus(soaRearCurtainStatus);
    if ((soaRearCurtainStatus.errorState == eevp::control::SoaErrorState::kOK) &&\
    (soaRearCurtainStatus.curtainState != eevp::control::SoaRctnState::kMOVING_UP)&&\
    (soaRearCurtainStatus.curtainState != eevp::control::SoaRctnState::kMOVING_DOWN)&&\
    (soaRearCurtainStatus.isNormal == eevp::control::SoaDeviceIsNormal::kNORMAL))
    {
        mLogger.LogInfo() << "Rctn ready!";
        return true;
    }
    else 
    {
        mLogger.LogInfo() << "Rctn NOT ready!";
        mLogger.LogInfo() << "errorState is " << static_cast<std::uint8_t>(soaRearCurtainStatus.errorState); 
        mLogger.LogInfo() << "curtainState is " << static_cast<std::uint8_t>(soaRearCurtainStatus.curtainState); 
        mLogger.LogInfo() << "isNormal is " << static_cast<std::uint8_t>(soaRearCurtainStatus.isNormal); 

        return false;
    }
}

void
KATECH::getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) {
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

/// RearCurtain End


bool
KATECH::startRoaProxy() {
    mLogger.LogInfo() << __func__;
    roaProxyImpl = std::make_shared<eevp::control::roa::RoaProxyImpl>();
    auto roaListener = std::make_shared<RoaListener>(this);
    roaProxyImpl->setEventListener(roaListener);
    roaProxyImpl->init();
    return true;
}

bool
KATECH::startRearCurtainProxy() {
    mLogger.LogInfo() << __func__;
    rearCurtainProxyImpl = std::make_shared<eevp::control::rearcurtain::RearCurtainProxyImpl>();
    //auto rearCurtainListener = std::make_shared<RearCurtainListener>(this);
    //rearCurtainProxyImpl->setEventListener(rearCurtainListener);
    rearCurtainProxyImpl->init();
    return true;
}

} // namespace control
} // namespace eevp
