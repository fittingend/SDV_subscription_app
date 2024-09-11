#include <Zone2RoaProxyImpl.hpp>
#include <Api_SoaRoa.hpp>
#include <Api_Zone2Roa.hpp>
#include <VehicleContext.hpp>
#include <Log.hpp>

using namespace zone2::roa::control;

#define ROA_CONTROL_INIT        1
#define ROA_CONTROL_START       2
#define ROA_CONTROL_STOP        3
#define ROA_CONTROL_START_DELAY 4

static void checkRoaSnSrStatusAndUpdateContext(EcmRoaSnsrStatus status)
{
    VehicleContext *context = VehicleContext::GetInstance();
    DeviceNormal_e isNormal = context->mIsNormal;
    int detectCount = context->mDetectCount;
    RoaSensorError_e sensorError = context->mSensorError;

    isNormal = (status.isNormal == 0) ? eDeviceNormal_Ok : eDeviceNormal_Abnormal;
    if (context->mIsNormal != isNormal)
    {
        context->mIsNormal = isNormal;
        SOA_ROA_UpdateDeviceNormal();
    }

    switch (status.snsrErrState)
    {
    case 0:
        sensorError = eRoaSensorError_Ok;
        break;
    case 1:
        sensorError = eRoaSensorError_Snsr;
        break;
    case 2:
        sensorError = eRoaSensorError_Blckge;
        break;
    default:
        sensorError = eRoaSensorError_Snsr;
        break;
    }

    if (context->mSensorError != sensorError)
    {
        context->mSensorError = sensorError;
        SOA_ROA_UpdateSensorError();
    }

    if (status.detInfo == 1)    // DETECT
    {
        detectCount = 1;
    }
    else if (status.detInfo == 3)   // EMPTY
    {
        detectCount = 0;
    }

    if (context->mDetectCount != detectCount)
    {
        context->mDetectCount = detectCount;
        SOA_ROA_UpdateDetectCount();
    }
}

class RoaListener : public IZone2RoaListener
{
public:
    void notifySnsrStatus(const EcmRoaSnsrStatus &fieldValue) override
    {
        checkRoaSnSrStatusAndUpdateContext(fieldValue);
    }

    void getSnsrStatus() override
    {
    }
};

void Zone2_SOA_Init()
{
    auto *inst = Zone2RoaProxyImpl::GetInstance();
    if (inst->init())
    {
        inst->setEventListener(std::make_shared<RoaListener>());
        EcmRoaSnsrStatus status;
        if (inst->getterSnsrStatus(status))
        {
            checkRoaSnSrStatusAndUpdateContext(status);
        }
    }
}

void Zone2_SOA_Term()
{
    Zone2RoaProxyImpl::DeleteInstance();
}

void Zone2_SOA_ResetSensor()
{
    LOG_DEBUG() << "(+)\n";
    Zone2RoaProxyImpl::GetInstance()->controlRoa(ROA_CONTROL_INIT);
    LOG_DEBUG() << "(-)\n";
}

void Zone2_SOA_StartSensor()
{
    LOG_DEBUG() << "(+)\n";
    Zone2RoaProxyImpl::GetInstance()->controlRoa(ROA_CONTROL_START);
    LOG_DEBUG() << "(-)\n";
}

void Zone2_SOA_StopSensor()
{
    LOG_DEBUG() << "(+)\n";
    Zone2RoaProxyImpl::GetInstance()->controlRoa(ROA_CONTROL_STOP);
    LOG_DEBUG() << "(-)\n";
}

