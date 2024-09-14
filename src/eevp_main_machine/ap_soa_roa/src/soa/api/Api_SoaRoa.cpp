#include <SoaRoaSkeletonImpl.hpp>
#include <Api_SoaRoa.hpp>
#include <Api_Zone2Roa.hpp>
#include <VehicleContext.hpp>
#include <Log.hpp>

static eevp::control::SoaRoaSkeletonImpl *s_inst = nullptr;

void SOA_ROA_Init()
{
    if (!s_inst)
    {
        ara::core::InstanceSpecifier specifier("SOA_ROA/AA/PPort_SOA_ROA");
        s_inst = new eevp::control::SoaRoaSkeletonImpl(specifier);
        s_inst->OfferService();
    }
}

void SOA_ROA_Term()
{
    if (s_inst)
    {
        delete s_inst;
        s_inst = nullptr;
    }
}

void SOA_ROA_SetMode(RoaMode_e mode)
{
    LOG_DEBUG() << "(+)\n";
    VehicleContext *context = VehicleContext::GetInstance();
    if (context->mRoaMode != mode)
    {
        context->mRoaMode = mode;
        // ToDo:

        SOA_ROA_UpdateRoaMode();
    }
    LOG_DEBUG() << "(-)\n";
}

void SOA_ROA_ResetSensor()
{
    LOG_DEBUG() << "(+)\n";
    VehicleContext *context = VehicleContext::GetInstance();
    Zone2_SOA_ResetSensor();
    if (context->mDetectCount != 0)
    {
        context->mDetectCount = 0;
        SOA_ROA_UpdateDetectCount();
    }
    LOG_DEBUG() << "(-)\n";
}

void SOA_ROA_StartSensor()
{
    LOG_DEBUG() << "(+)\n";
    VehicleContext *context = VehicleContext::GetInstance();
    if (context->mRunningState != eRoaRunningState_On)
    {
        Zone2_SOA_StartSensor();
        context->mRunningState = eRoaRunningState_On;
        SOA_ROA_UpdateRunningState();
    }
    else
    {
        context->mDetectCount = 0;
        Zone2_SOA_ResetSensor();
    }

    LOG_DEBUG() << "(-)\n";
}

void SOA_ROA_StopSensor()
{
    LOG_DEBUG() << "(+)\n";
    VehicleContext *context = VehicleContext::GetInstance();
    if (context->mRunningState == eRoaRunningState_On)
    {
        Zone2_SOA_StopSensor();
        context->mRunningState = eRoaRunningState_Off;
        SOA_ROA_UpdateRunningState();
    }

    LOG_DEBUG() << "(-)\n";
}

void SOA_ROA_UpdateDeviceNormal()
{
    if (s_inst)
    {
        s_inst->UpdateDeviceNormal();
    }
}

void SOA_ROA_UpdateRunningState()
{
    if (s_inst)
    {
        s_inst->UpdateRunningState();
    }
}

void SOA_ROA_UpdateRoaMode()
{
    if (s_inst)
    {
        s_inst->UpdateRoaMode();
    }
}

void SOA_ROA_UpdateDetectState()
{
    if (s_inst)
    {
        s_inst->UpdateDetectState();
    }
}

void SOA_ROA_UpdateDetectCount()
{
    if (s_inst)
    {
        s_inst->UpdateDetectCount();
    }
}

void SOA_ROA_UpdateSensorError()
{
    if (s_inst)
    {
        s_inst->UpdateSensorError();
    }
}