#include <Common.h>
#include <MessageItem.hpp>
#include <VehicleContext.hpp>
#include <Api_Zone3Rcurtain.hpp>
#include <Api_SoaRcurtain.hpp>
#include <RearCurtainManager.hpp>
#include <Log.hpp>

RearCurtainManager *RearCurtainManager::mInst = nullptr;

RearCurtainManager *RearCurtainManager::GetInstance()
{
    if (RearCurtainManager::mInst == nullptr)
    {
        RearCurtainManager::mInst = new RearCurtainManager();
        Api_Rcurtain_Field_SoaRctnStatus();
    }

    return RearCurtainManager::mInst;
}

RearCurtainManager::RearCurtainManager()
{

}

RearCurtainManager::~RearCurtainManager()
{

}

void RearCurtainManager::OnEventPower(PowerState_e power_curr, PowerState_e power_prev)
{

}

void RearCurtainManager::OnEventVehiclSpeed(int speed_curr, int speed_prev)
{

}


void RearCurtainManager::OnEventRcButton(RCtnSwitch_e btn_curr, RCtnSwitch_e btn_prev)
{
    funcMsgItem msgItem;

    switch (btn_curr)
    {
    case eRCtnSwitch_OpenOn:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "eRCtnSwitch_OpenOn\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnState != eRCtnState_FullyOpened)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_OpenOn);
                // context->Save();
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    case eRCtnSwitch_CloseOn:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "eRCtnSwitch_CloseOn\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnState != eRCtnState_FullyClosed && context->mGearState != eGearState_R)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_CloseOn);
            }

             Api_Rcurtain_Field_SoaRctnStatus();
             return 0;
        };
        break;

    case eRCtnSwitch_Off:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventRcButton] eRCtnSwitch_Off\n";
            VehicleContext *context = VehicleContext::GetInstance();

            Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_Off);
            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    default:
        return;
    }

    this->sendMessage(msgItem);
}

void RearCurtainManager::OnEventGearState(GearState_e gear_curr, GearState_e gear_prev)
{
#if 0
    funcMsgItem msgItem;

    if (gear_curr == eGearState_R)
    {
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventGearState] eGearState_R\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnState != eRCtnState_FullyOpened)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_OpenOn);
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
    }
    else
    {
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventGearState] !eGearState_R\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRCLastUserSwitch == eRCtnSwitch_OpenOn && context->mRctnState != eRCtnState_FullyOpened)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_OpenOn);
                //context->mRctnState = eRCtnState_Opening;
                context->mRCLastState = eRCtnState_PartlyOpened;

                context->Save();
            }
            else if (context->mRCLastUserSwitch == eRCtnSwitch_CloseOn && context->mRctnState != eRCtnState_FullyClosed)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_CloseOn);
                //context->mRctnState = eRCtnState_Closing;
                context->mRCLastState = eRCtnState_PartlyOpened;
                context->Save();
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
    }

    this->sendMessage(msgItem);
#endif
}

void RearCurtainManager::OnEventRcState(RCtnState_e state_curr, RCtnState_e state_prev)
{
#if 0
    funcMsgItem msgItem;

    switch (state_curr)
    {
    case eRCtnState_FullyOpened:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventRcState] eRCtnState_FullyOpened\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRCLastState != eRCtnState_FullyOpened)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_Off);
                // context->mRctnState = eRCtnState_FullyOpened;
                context->mRCLastState = eRCtnState_FullyOpened;
                context->Save();
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    case eRCtnState_FullyClosed:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventRcState] eRCtnState_FullyClosed\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRCLastState != eRCtnState_FullyClosed)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_Off);
                // context->mRctnState = eRCtnState_FullyClosed;
                context->mRCLastState = eRCtnState_FullyClosed;
                context->Save();
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    default:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnEventRcState] Others....\n";
            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;
    }

    this->sendMessage(msgItem);
#endif
}

int RearCurtainManager::OnCmdRequestRearCurtainOperation(RCtnSwitch_e btn, bool api_modal)
{
    funcMsgItem msgItem;

    switch (btn)
    {
    case eRCtnSwitch_OpenOn:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnCmdRequestRearCurtainOperation] eRCtnSwitch_OpenOn\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnState != eRCtnState_FullyOpened)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_OpenOn);
                context->mRctnState = eRCtnState_Opening;
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    case eRCtnSwitch_CloseOn:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnCmdRequestRearCurtainOperation] eRCtnSwitch_CloseOn\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnState != eRCtnState_FullyClosed && context->mGearState != eGearState_R)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_CloseOn);
                context->mRctnState = eRCtnState_Closing;
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    case eRCtnSwitch_Off:
        msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
            LOG_DEBUG() << "[RearCurtainManager::OnCmdRequestRearCurtainOperation] eRCtnSwitch_Off\n";
            VehicleContext *context = VehicleContext::GetInstance();

            if (context->mRctnSwitch != eRCtnSwitch_Off)
            {
                Zone3_RCtn_MoveCurtainMotor(eRCtnSwitch_Off);
                if (context->mRctnState != eRCtnState_FullyClosed && context->mRctnState != eRCtnState_FullyOpened)
                {
                    context->mRctnState = eRCtnState_PartlyOpened;
                }
            }

            Api_Rcurtain_Field_SoaRctnStatus();
            return 0;
        };
        break;

    default:
        return 1;
    }

    return this->sendMessage(msgItem, api_modal);
}

int RearCurtainManager::OnCmdRequestRearCurtainPosition(int position_per, bool api_modal)
{
    funcMsgItem msgItem;

    msgItem.mFunc = [](int arg1, int arg2, int arg3, void *argPtr) {
        LOG_DEBUG() << "[RearCurtainManager::OnCmdRequestRearCurtainOperation] eRCtnSwitch_OpenOn\n";
        Zone3_RCtn_MoveCurtainMotorToPosition(arg1);
        return 0;
    };
    msgItem.mArg1 = position_per;

    return this->sendMessage(msgItem, api_modal);
}
