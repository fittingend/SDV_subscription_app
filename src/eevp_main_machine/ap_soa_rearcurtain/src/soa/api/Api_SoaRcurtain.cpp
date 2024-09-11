#include <Common.h>
#include <SoaDataType.h>
#include <string.h>
#include <VehicleContext.hpp>
#include <RearCurtainManager.hpp>
#include <Api_SoaRcurtain.hpp>
#include <SoaRcurtainSkeletonImpl.hpp>
#if !defined(DISABLE_SOMEIP)
#include <PaconSetting.hpp>
#endif
#include <Log.hpp>

static eevp::control::SoaRcurtainSkeletonImpl *s_inst = nullptr;

void Api_Rcurtain_Init(void)
{
    if (!s_inst)
    {
        ara::core::InstanceSpecifier specifier("SOA_RearCurtain/AA/PPort_SOA_RearCurtain");
        s_inst = new eevp::control::SoaRcurtainSkeletonImpl(specifier);
        s_inst->OfferService();
    }
}

void Api_Rcurtain_Term(void)
{
    if (s_inst)
    {
        delete s_inst;
        s_inst = nullptr;
    }
}

int Api_Rcurtain_Method_RequestRearCurtainOperation(RCtnSwitch_e eDirection)
{
    RearCurtainManager *mgr = RearCurtainManager::GetInstance();
    return mgr->OnCmdRequestRearCurtainOperation(eDirection);
}

int Api_Rcurtain_Method_RequestRearCurtainPosition(int percentage)
{
    RearCurtainManager *mgr = RearCurtainManager::GetInstance();
    return mgr->OnCmdRequestRearCurtainPosition(percentage);
}

void Api_Rcurtain_Field_SoaRctnStatus()
{
    eevp::control::SoaRctnStatus rctnStatus;
    VehicleContext *context = VehicleContext::GetInstance();

    eevp::control::SoaErrorState errorState = eevp::control::SoaErrorState::kOK;
    eevp::control::SoaRctnMotorDir curMotorDirection;
    eevp::control::SoaRctnState curtainState;
    eevp::control::SoaDeviceIsNormal isNormal;

    errorState = eevp::control::SoaErrorState::kOK;

    switch (context->mRctnSwitch)
    {
    case eRCtnSwitch_OpenOn:
        curMotorDirection = eevp::control::SoaRctnMotorDir::kDOWN;
        break;
    case eRCtnSwitch_CloseOn:
        curMotorDirection = eevp::control::SoaRctnMotorDir::kUP;
        break;
    case eRCtnSwitch_Off:
    default:
        curMotorDirection = eevp::control::SoaRctnMotorDir::kSTOP;
        break;
    }

    switch (context->mRctnState)
    {
    case eRCtnState_FullyOpened:
        curtainState = eevp::control::SoaRctnState::kFULLY_DOWN;
        break;
    case eRCtnState_FullyClosed:
        curtainState = eevp::control::SoaRctnState::kFULLY_UP;
        break;
    case eRCtnState_PartlyOpened:
        curtainState = eevp::control::SoaRctnState::kPARTLY_OPENED;
        break;
    case eRCtnState_Opening:
        curtainState = eevp::control::SoaRctnState::kMOVING_DOWN;
        break;
    case eRCtnState_Closing:
        curtainState = eevp::control::SoaRctnState::kMOVING_UP;
        break;
    default:
        curtainState = eevp::control::SoaRctnState::kFULLY_UP;
        break;
    }

    switch (context->mIsNormal)
    {
    case eDeviceNormal_Ok:
        isNormal = eevp::control::SoaDeviceIsNormal::kNORMAL;
        break;

    case eDeviceNormal_Abnormal:
        isNormal = eevp::control::SoaDeviceIsNormal::kABNORMAL;
        break;

    default:
        isNormal = eevp::control::SoaDeviceIsNormal::kABNORMAL;
        break;
    }

    rctnStatus.errorState = errorState;
    rctnStatus.curMotorDirection = curMotorDirection;
    rctnStatus.curtainState = curtainState;
    rctnStatus.isNormal = isNormal;

    if (s_inst != nullptr)
    {
        s_inst->SetSoaRctnStatus(rctnStatus);
    }
}
