#include <SoaRoaSkeletonImpl.hpp>
#include <Common.h>
#include <VehicleContext.hpp>
#include <Api_SoaRoa.hpp>
#include <SoaDataType.h>
#include <Log.hpp>

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {

SoaRoaSkeletonImpl::SoaRoaSkeletonImpl(
        ara::core::InstanceSpecifier instanceSpec,
        ara::com::MethodCallProcessingMode mode) :
    SoaRoaSkeleton(instanceSpec, mode) ,
    mLogger(ara::log::CreateLogger("SOA", "ROA", ara::log::LogLevel::kInfo))
{
    auto deviceNormal_getHandler = [this]() {
        return this->getter_DeviceNormal();
    };

    auto runningState_getHandler = [this]() {
        return this->getter_RunningState();
    };

    auto mode_getHandler = [this]() {
        return this->getter_Mode();
    };

    auto detectState_getHandler = [this]() {
        return this->getter_DetectState();
    };

    auto detectCount_getHandler = [this]() {
        return this->getter_DetectCount();
    };

    auto sensorError_getHandler = [this]() {
        return this->getter_SensorError();
    };

    auto sw_getHandler = [this]() {
        return this->getter_SwVersion();
    };

    this->mDeviceNormal	= fields::soaRoaDeviceNormal::FieldType::kABNORMAL;
    this->mRunningState	= fields::soaRoaRunningState::FieldType::kOFF;
    this->mMode			= fields::soaRoaMode::FieldType::kNORMAL;
    //this->mDetectState	= fields::soaRoaDetectState::FieldType::kEMPTY;
    this->mDetectState	= fields::soaRoaDetectState::FieldType::kDETECTED_ONCE;
    this->mDetectCount	= 2;
    this->mSensorError	= fields::soaRoaSensorError::FieldType::kOK;
    this->mSwVersion = 12;

    soaRoaDeviceNormal.RegisterGetHandler(deviceNormal_getHandler);
    soaRoaRunningState.RegisterGetHandler(runningState_getHandler);
    soaRoaMode.RegisterGetHandler(mode_getHandler);
    soaRoaDetectState.RegisterGetHandler(detectState_getHandler);
    soaRoaDetectCount.RegisterGetHandler(detectCount_getHandler);
    soaRoaSensorError.RegisterGetHandler(sensorError_getHandler);
    soaRoaSwVersion.RegisterGetHandler(sw_getHandler);
}

ara::core::Future<fields::soaRoaDeviceNormal::FieldType> SoaRoaSkeletonImpl::getter_DeviceNormal()
{
    ara::core::Promise<fields::soaRoaDeviceNormal::FieldType> promise;
    promise.set_value(this->mDeviceNormal);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaRunningState::FieldType> SoaRoaSkeletonImpl::getter_RunningState()
{
    ara::core::Promise<fields::soaRoaRunningState::FieldType> promise;
    promise.set_value(this->mRunningState);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaMode::FieldType> SoaRoaSkeletonImpl::getter_Mode()
{
    ara::core::Promise<fields::soaRoaMode::FieldType> promise;
    promise.set_value(this->mMode);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaDetectState::FieldType> SoaRoaSkeletonImpl::getter_DetectState()
{
    ara::core::Promise<fields::soaRoaDetectState::FieldType> promise;
    mLogger.LogInfo() << __func__;
    promise.set_value(this->mDetectState);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaDetectCount::FieldType> SoaRoaSkeletonImpl::getter_DetectCount()
{
    ara::core::Promise<fields::soaRoaDetectCount::FieldType> promise;
    promise.set_value(this->mDetectCount);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaSensorError::FieldType> SoaRoaSkeletonImpl::getter_SensorError()
{
    ara::core::Promise<fields::soaRoaSensorError::FieldType> promise;
    promise.set_value(this->mSensorError);
    return promise.get_future();
}

ara::core::Future<fields::soaRoaSwVersion::FieldType> SoaRoaSkeletonImpl::getter_SwVersion()
{
    ara::core::Promise<fields::soaRoaSwVersion::FieldType> promise;
    promise.set_value(this->mSwVersion);
    return promise.get_future();
}

SoaRoaSkeletonImpl::~SoaRoaSkeletonImpl() {
    StopOfferService();
}

void SoaRoaSkeletonImpl::StartRoa()
{
    LOG_DEBUG() << "[eevp.control.SoaRoa.StartRoa] (+)\n";
    SOA_ROA_StartSensor();
    LOG_DEBUG() << "[eevp.control.SoaRoa.StartRoa] (-)\n";
}

void SoaRoaSkeletonImpl::StopRoa()
{
    LOG_DEBUG() << "[eevp.control.SoaRoa.StopRoa] (+)\n";
    SOA_ROA_StopSensor();
    LOG_DEBUG() << "[eevp.control.SoaRoa.StopRoa] (-)\n";
}

void SoaRoaSkeletonImpl::ResetRoaDetectInfo()
{
    LOG_DEBUG() << "[eevp.control.SoaRoa.ResetRoaDetectInfo] (+)\n";
    SOA_ROA_ResetSensor();
    LOG_DEBUG() << "[eevp.control.SoaRoa.ResetRoaDetectInfo] (-)\n";
}

void SoaRoaSkeletonImpl::SetRoaMode(const eevp::control::SoaRoaMode& mode)
{
    LOG_DEBUG() << "[eevp.control.SoaRoa.SetRoaMode] (+)\n";
    RoaMode_e roa_mode;
    switch (mode)
    {
    case eevp::control::SoaRoaMode::kOFF:
        roa_mode = eRoaMode_Off;
        break;
    case eevp::control::SoaRoaMode::kNORMAL:
        roa_mode = eRoaMode_Normal;
        break;
    case eevp::control::SoaRoaMode::kADVANCED:
        roa_mode = eRoaMode_Advanced;
        break;
    default:
        roa_mode = eRoaMode_Off;
        break;
    }
    SOA_ROA_SetMode(roa_mode);
    LOG_DEBUG() << "[eevp.control.SoaRoa.SetRoaMode] (-)\n";
}

void SoaRoaSkeletonImpl::UpdateDeviceNormal()
{
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaDeviceNormal::FieldType value;

    value = (context->mIsNormal == eDeviceNormal_Ok) ? eevp::control::SoaDeviceIsNormal::kNORMAL : eevp::control::SoaDeviceIsNormal::kABNORMAL;
    if (this->mDeviceNormal != value)
    {
        this->mDeviceNormal = value;
        soaRoaDeviceNormal.Update(this->mDeviceNormal);
    }
}

void SoaRoaSkeletonImpl::UpdateRunningState()
{
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaRunningState::FieldType value;

    switch (context->mRunningState)
    {
    case eRoaRunningState_Off:
        value = eevp::control::SoaRoaRunningState::kOFF;
        break;
    case eRoaRunningState_On:
        value = eevp::control::SoaRoaRunningState::kON;
        break;
    case eRoaRunningState_Error:
    default:
        value = eevp::control::SoaRoaRunningState::kUNKNOWN;
        break;
    }

    if (this->mRunningState != value)
    {
        this->mRunningState = value;
        soaRoaRunningState.Update(this->mRunningState);
    }
}

void SoaRoaSkeletonImpl::UpdateRoaMode()
{
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaMode::FieldType value;

    switch (context->mRoaMode)
    {
    case eRoaMode_Off:
        value = fields::soaRoaMode::FieldType::kOFF;
        break;
    case eRoaMode_Normal:
        value = fields::soaRoaMode::FieldType::kNORMAL;
        break;
    case eRoaMode_Advanced:
        value = fields::soaRoaMode::FieldType::kADVANCED;
        break;
    default:
        value = fields::soaRoaMode::FieldType::kOFF;
        break;
    }

    if (this->mMode != value)
    {
        this->mMode = value;
        soaRoaMode.Update(this->mMode);
    }
}
void SoaRoaSkeletonImpl::UpdateDetectState()
{
    mLogger.LogInfo() << __func__;

    fields::soaRoaDetectState::FieldType value;
    value = fields::soaRoaDetectState::FieldType::kDETECTED_SEVERAL;
    this->mDetectState = value;
    soaRoaDetectState.Update(this->mDetectState);
}
/*
void SoaRoaSkeletonImpl::UpdateDetectState()
{
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaDetectState::FieldType value;

    if (context->mDetectCount <= 0)
    {
        value = fields::soaRoaDetectState::FieldType::kEMPTY;
    }
    else if (context->mDetectCount == 1)
    {
        value = fields::soaRoaDetectState::FieldType::kDETECTED_ONCE;
    }
    else
    {
        value = fields::soaRoaDetectState::FieldType::kDETECTED_SEVERAL;
    }

    if (this->mDetectState != value)
    {
        this->mDetectState = value;
        soaRoaDetectState.Update(this->mDetectState);
    }
}
*/
void SoaRoaSkeletonImpl::UpdateDetectCount()
{
    LOG_INFO() << __func__;
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaDetectCount::FieldType value;
    LOG_INFO() << "sss value is" << value;

    value = (fields::soaRoaDetectCount::FieldType)context->mDetectCount;
    if (this->mDetectCount != value)
    {
        this->mDetectCount = value;
        LOG_INFO() << "jjj value is" << value;
        soaRoaDetectCount.Update(this->mDetectCount);
    }
}

void SoaRoaSkeletonImpl::UpdateSensorError()
{
    VehicleContext *context = VehicleContext::GetInstance();
    fields::soaRoaSensorError::FieldType value;
    switch (context->mSensorError)
    {
    case eRoaSensorError_Ok:
        value = fields::soaRoaSensorError::FieldType::kOK;
        break;
    case eRoaSensorError_Snsr:
        value = fields::soaRoaSensorError::FieldType::kERR_SNSR;
        break;
    case eRoaSensorError_Blckge:
        value = fields::soaRoaSensorError::FieldType::kERR_BLCKGE;
        break;
    default:
        value = fields::soaRoaSensorError::FieldType::kOK;
        break;
    }

    if (this->mSensorError != value)
    {
        this->mSensorError = value;
        soaRoaSensorError.Update(this->mSensorError);
    }
}


} // namespace control
} // namespace eevp
