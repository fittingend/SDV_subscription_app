#include <Common.h>
#include <SoaDataType.h>
#include <string.h>
#include <string>
#include <Api_SoaRcurtain.hpp>
#include <Api_Zone3Rcurtain.hpp>
#include <Zone3RcurtainProxyImpl.hpp>
#include <VehicleContext.hpp>
#include <iostream>
#include <Log.hpp>

#define ZONE3_MOTOR_POS_STOP        0
#define ZONE3_MOTOR_POS_FULL_CLOSE  1
#define ZONE3_MOTOR_POS_CLOSS_66    2
#define ZONE3_MOTOR_POS_CLOSS_33    3
#define ZONE3_MOTOR_POS_FULL_OPEN   4

using namespace zone3::rcurtain::control;

static int convert_motor_btn_to_zone3_command(RCtnSwitch_e btn)
{
    switch (btn)
    {
    case eRCtnSwitch_Off:
        return ZONE3_MOTOR_POS_STOP;

    case eRCtnSwitch_OpenOn:
        return ZONE3_MOTOR_POS_FULL_OPEN;

    case eRCtnSwitch_CloseOn:
        return ZONE3_MOTOR_POS_FULL_CLOSE;

    default:
        break;
    }

    return ZONE3_MOTOR_POS_STOP;
}

static int convert_motor_move_percentage_to_zone3_command(int percentage)
{
    if (percentage >= 83)
    {
        return ZONE3_MOTOR_POS_FULL_CLOSE;
    }
    else if (percentage >= 49)
    {
        return ZONE3_MOTOR_POS_CLOSS_66;
    }
    else if (percentage >= 17)
    {
        return ZONE3_MOTOR_POS_CLOSS_33;
    }

    return ZONE3_MOTOR_POS_FULL_OPEN;
}

static bool update_vehicle_context_by_EcuRcurtainStatus(EcuRcurtainStatus status)
{
    VehicleContext *context = VehicleContext::GetInstance();
    RCtnSwitch_e rctnSwitch = context->mRctnSwitch;
    RCtnState_e rctnState = context->mRctnState;
    DeviceNormal_e isNormal = context->mIsNormal;

    if (context->mMotorMoving == true)
    {
        if (status.curMotorDir == context->mRctnZoneInputPosition)
        {
            if (status.curMotorDir == ZONE3_MOTOR_POS_FULL_CLOSE)
            {
                rctnState = eRCtnState_FullyClosed;
            }
            else if (status.curMotorDir == ZONE3_MOTOR_POS_FULL_OPEN)
            {
                rctnState = eRCtnState_FullyOpened;
            }
            else
            {
                rctnState = eRCtnState_PartlyOpened;
            }

            rctnSwitch = eRCtnSwitch_Off;
            context->mMotorMoving = false;
        }
    }
    else
    {
        switch (status.curMotorDir)
        {
        case ZONE3_MOTOR_POS_FULL_CLOSE:
            rctnState = eRCtnState_FullyClosed;
            break;
        case ZONE3_MOTOR_POS_CLOSS_66:
        case ZONE3_MOTOR_POS_CLOSS_33:
            rctnState = eRCtnState_PartlyOpened;
            break;
        case ZONE3_MOTOR_POS_FULL_OPEN:
            rctnState = eRCtnState_FullyOpened;
            break;
        }
    }

    isNormal = (status.isNormal == 0) ? eDeviceNormal_Ok : eDeviceNormal_Abnormal;
    if ((context->mRctnSwitch != rctnSwitch) || (context->mRctnState != rctnState) || (context->mIsNormal != isNormal))
    {
        LOG_DEBUG() << "context changed\n";

        context->mRctnSwitch = rctnSwitch;
        context->mRctnState = rctnState;
        context->mIsNormal = isNormal;
        Api_Rcurtain_Field_SoaRctnStatus();
        return true;
    }

    return false;
}

class RearCurtainListener : public zone3::rcurtain::control::IZone3RearCurtainListener
{
    void notifyRcurtainStatus(const zone3::rcurtain::control::EcuRcurtainStatus &fieldValue)
    {
        LOG_DEBUG() << "EcuRcurtainStatus.curMotorDir = " << (int)fieldValue.curMotorDir << "\n";
        LOG_DEBUG() << "EcuRcurtainStatus.curMotorLimit = " << (int)fieldValue.curMotorLimit << "\n";
        LOG_DEBUG() << "EcuRcurtainStatus.motorCurrent = " << (int)fieldValue.motorCurrent << "\n";
        LOG_DEBUG() << "EcuRcurtainStatus.isNormal = " << (int)fieldValue.isNormal << "\n";

        update_vehicle_context_by_EcuRcurtainStatus(fieldValue);
    }

    void getRcurtainStatus()
    {
    }
};

void Zone3_RCtn_Init(void)
{
    auto *inst = Zone3RearCurtainProxyImpl::GetInstance();
    if (inst->init())
    {
        inst->setEventListener(std::make_shared<RearCurtainListener>());

        EcuRcurtainStatus status;
        if (inst->getterRcurtainStatus(status))
        {
            update_vehicle_context_by_EcuRcurtainStatus(status);
        }
    }
}

void Zone3_RCtn_Term(void)
{
    Zone3RearCurtainProxyImpl::DeleteInstance();
}

void Zone3_RCtn_PowerOn(PowerState_e power)
{

}

void Zone3_RCtn_MoveCurtainMotor(RCtnSwitch_e btn)
{
    LOG_DEBUG() << "(+)\n";
    VehicleContext *context = VehicleContext::GetInstance();
    int zone_val = convert_motor_btn_to_zone3_command(btn);
    RCtnSwitch_e rctnSwitch = context->mRctnSwitch;
    RCtnState_e rctnState = context->mRctnState;

    LOG_DEBUG() << "controlMotor(" << (int)context->mRctnZoneInputPosition << " -> " << zone_val << ")\n";

    if (zone_val != ZONE3_MOTOR_POS_STOP)
    {
        if ((context->mRctnZoneInputPosition != zone_val) && (context->mMotorMoving != true))
        {
            if (context->mRctnZoneInputPosition > zone_val)
            {
                rctnSwitch = eRCtnSwitch_CloseOn;
                rctnState = eRCtnState_Closing;
            }
            else
            {
                rctnSwitch = eRCtnSwitch_OpenOn;
                rctnState = eRCtnState_Opening;
            }

            context->mRctnZoneInputPosition = zone_val;
            context->mMotorMoving = true;
            Zone3RearCurtainProxyImpl::GetInstance()->controlMotor((uint8_t)zone_val);
        }

        if ((rctnSwitch != context->mRctnSwitch) || (rctnState != context->mRctnState))
        {
            context->mRctnSwitch = rctnSwitch;
            context->mRctnState = rctnState;
            Api_Rcurtain_Field_SoaRctnStatus();
        }
    }
    LOG_DEBUG() << "(-)\n";
}

void Zone3_RCtn_MoveCurtainMotorToPosition(int pos)
{
    LOG_DEBUG() << "(+) pos=" << pos << "\n";
    VehicleContext *context = VehicleContext::GetInstance();
    int zone_val = convert_motor_move_percentage_to_zone3_command(pos);
    RCtnSwitch_e rctnSwitch = context->mRctnSwitch;
    RCtnState_e rctnState = context->mRctnState;

    LOG_DEBUG() << "controlMotor(" << (int)context->mRctnZoneInputPosition << " -> " << zone_val << ")\n";

    if ((context->mRctnZoneInputPosition != zone_val) && (context->mMotorMoving != true))
    {
        if (context->mRctnZoneInputPosition > zone_val)
        {
            rctnSwitch = eRCtnSwitch_CloseOn;
            rctnState = eRCtnState_Closing;
        }
        else
        {
            rctnSwitch = eRCtnSwitch_OpenOn;
            rctnState = eRCtnState_Opening;
        }

        context->mRctnZoneInputPosition = zone_val;
        context->mMotorMoving = true;
        Zone3RearCurtainProxyImpl::GetInstance()->controlMotor((uint8_t)zone_val);
    }

    if ((rctnSwitch != context->mRctnSwitch) || (rctnState != context->mRctnState))
    {
        context->mRctnSwitch = rctnSwitch;
        context->mRctnState = rctnState;
        Api_Rcurtain_Field_SoaRctnStatus();
    }
    LOG_DEBUG() << "(-)\n";
}

void Zone3_RCtn_UpdateContext(void)
{
    auto *inst = Zone3RearCurtainProxyImpl::GetInstance();

    EcuRcurtainStatus status;
    if (inst->getterRcurtainStatus(status))
    {
        update_vehicle_context_by_EcuRcurtainStatus(status);
    }

}