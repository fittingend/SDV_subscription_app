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

    this->updateFieldDeviceNormalWithContext();
    this->updateFieldRunningStateWithContext();
    this->updateFieldRoaModeWithContext();
    this->updateFieldDetectStateWithContext();
    this->updateFieldDetectCountWithContext();
    this->updateFieldSensorErrorWithContext();

    this->mSwVersion = (std::uint8_t)SW_VERSION;

    soaRoaDeviceNormal.RegisterGetHandler(deviceNormal_getHandler);
    soaRoaRunningState.RegisterGetHandler(runningState_getHandler);
    soaRoaMode.RegisterGetHandler(mode_getHandler);
    soaRoaDetectState.RegisterGetHandler(detectState_getHandler);
    soaRoaDetectCount.RegisterGetHandler(detectCount_getHandler);
    soaRoaSensorError.RegisterGetHandler(sensorError_getHandler);
    soaRoaSwVersion.RegisterGetHandler(sw_getHandler);
}

static SoaDeviceIsNormal convert_eDeviceNormal_to_SoaDeviceIsNormal(DeviceNormal_e val)
{
    switch (val)
    {
    case eDeviceNormal_Ok:          return SoaDeviceIsNormal::kNORMAL;
    case eDeviceNormal_Abnormal:    return SoaDeviceIsNormal::kABNORMAL;
    default:
        break;
    }

    return SoaDeviceIsNormal::kABNORMAL;
}

static SoaRoaRunningState convert_eRoaRunningState_to_SoaRoaRunningState(RoaRunningState_e val)
{
    switch (val)
    {
    case eRoaRunningState_Off:      return SoaRoaRunningState::kOFF;
    case eRoaRunningState_On:       return SoaRoaRunningState::kON;
    default:
        break;
    }

    return SoaRoaRunningState::kOFF;
}

static SoaRoaMode convert_eRoaMode_to_SoaRoaMode(RoaMode_e val)
{
    switch (val)
    {
    case eRoaMode_Off:              return SoaRoaMode::kOFF;
    case eRoaMode_Normal:           return SoaRoaMode::kNORMAL;
    case eRoaMode_Advanced:         return SoaRoaMode::kADVANCED;
    default:
        break;
    }

    return SoaRoaMode::kOFF;
}

static SoaRoaDetectState convert_nDetectCount_to_SoaRoaDetectState(int value)
{
    if (value == 0)
    {
        return SoaRoaDetectState::kEMPTY;
    }
    else if (value == 1)
    {
        return SoaRoaDetectState::kDETECTED_ONCE;
    }
    else if (value > 1)
    {
        return SoaRoaDetectState::kDETECTED_SEVERAL;
    }

    return SoaRoaDetectState::kUNKNOWN;
}

static SoaRoaSensorError convert_eRoaSensorError_to_SoaRoaSensorError(RoaSensorError_e val)
{
    switch (val)
    {
    case eRoaSensorError_Ok:        return SoaRoaSensorError::kOK;
    case eRoaSensorError_Snsr:      return SoaRoaSensorError::kERR_SNSR;
    case eRoaSensorError_Blckge:    return SoaRoaSensorError::kERR_BLCKGE;
    default:
        break;
    }

    return SoaRoaSensorError::kERR_SNSR;
}

bool SoaRoaSkeletonImpl::updateFieldDeviceNormalWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    SoaDeviceIsNormal deviceNormal = convert_eDeviceNormal_to_SoaDeviceIsNormal(context->mIsNormal);
    if (this->mDeviceNormal != deviceNormal)
    {
        this->mDeviceNormal = deviceNormal;
        return true;
    }

    return false;
}

bool SoaRoaSkeletonImpl::updateFieldRunningStateWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    SoaRoaRunningState runningState = convert_eRoaRunningState_to_SoaRoaRunningState(context->mRunningState);
    if (this->mRunningState != runningState)
    {
        this->mRunningState = runningState;
        return true;
    }

    return false;
}

bool SoaRoaSkeletonImpl::updateFieldRoaModeWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    SoaRoaMode roaMode = convert_eRoaMode_to_SoaRoaMode(context->mRoaMode);
    if (this->mMode != roaMode)
    {
        this->mMode = roaMode;
        return true;
    }

    return false;
}

bool SoaRoaSkeletonImpl::updateFieldDetectStateWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    SoaRoaDetectState detectState = convert_nDetectCount_to_SoaRoaDetectState(context->mDetectCount);
    if (this->mDetectState != detectState)
    {
        this->mDetectState = detectState;
        return true;
    }

    return false;
}

bool SoaRoaSkeletonImpl::updateFieldDetectCountWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    std::uint8_t detectCount = (std::uint8_t)context->mDetectCount;
    if (this->mDetectCount != detectCount)
    {
        this->mDetectCount = detectCount;
        return true;
    }

    return false;
}

bool SoaRoaSkeletonImpl::updateFieldSensorErrorWithContext(void)
{
    VehicleContext *context = VehicleContext::GetInstance();

    SoaRoaSensorError sensorError = convert_eRoaSensorError_to_SoaRoaSensorError(context->mSensorError);
    if (this->mSensorError != sensorError)
    {
        this->mSensorError = sensorError;
        return true;
    }

    return false;
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
    if (this->updateFieldDeviceNormalWithContext())
    {
        LOG_DEBUG() << "soaRoaDeviceNormal updated.\n";
        soaRoaDeviceNormal.Update(this->mDeviceNormal);
    }
}

void SoaRoaSkeletonImpl::UpdateRunningState()
{
    if (this->updateFieldRunningStateWithContext())
    {
        LOG_DEBUG() << "soaRoaRunningState updated.\n";
        soaRoaRunningState.Update(this->mRunningState);
    }
}

void SoaRoaSkeletonImpl::UpdateRoaMode()
{
    if (this->updateFieldRoaModeWithContext())
    {
        LOG_DEBUG() << "soaRoaMode updated.\n";
        soaRoaMode.Update(this->mMode);
    }
}

void SoaRoaSkeletonImpl::UpdateDetectState()
{
    if (this->updateFieldDetectStateWithContext())
    {
        LOG_DEBUG() << "soaRoaDetectState updated.\n";
        soaRoaDetectState.Update(this->mDetectState);
    }
}

void SoaRoaSkeletonImpl::UpdateDetectCount()
{
    if (this->updateFieldDetectCountWithContext())
    {
        LOG_DEBUG() << "soaRoaDetectCount updated.\n";
        soaRoaDetectCount.Update(this->mDetectCount);
    }
}

void SoaRoaSkeletonImpl::UpdateSensorError()
{
    if (this->updateFieldSensorErrorWithContext())
    {
        LOG_DEBUG() << "soaRoaSensorError updated.\n";
        soaRoaSensorError.Update(this->mSensorError);
    }
}


} // namespace control
} // namespace eevp
