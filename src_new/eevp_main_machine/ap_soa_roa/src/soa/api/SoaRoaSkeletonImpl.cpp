#include "SoaRoaSkeletonImpl.hpp"
#include <Common.h>
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

    this->mDeviceNormal	= fields::soaRoaDeviceNormal::FieldType::kABNORMAL;
    this->mRunningState	= fields::soaRoaRunningState::FieldType::kOFF;
    this->mMode			= fields::soaRoaMode::FieldType::kNORMAL;
    this->mDetectState	= fields::soaRoaDetectState::FieldType::kEMPTY;
    this->mDetectCount	= 0;
    this->mSensorError	= fields::soaRoaSensorError::FieldType::kOK;	

    soaRoaDeviceNormal.RegisterGetHandler(deviceNormal_getHandler);
    soaRoaRunningState.RegisterGetHandler(runningState_getHandler);
    soaRoaMode.RegisterGetHandler(mode_getHandler);
    soaRoaDetectState.RegisterGetHandler(detectState_getHandler);
    soaRoaDetectCount.RegisterGetHandler(detectCount_getHandler);
    soaRoaSensorError.RegisterGetHandler(sensorError_getHandler);
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

SoaRoaSkeletonImpl::~SoaRoaSkeletonImpl() {
    StopOfferService();
}

void SoaRoaSkeletonImpl::StartRoa()
{
}

void SoaRoaSkeletonImpl::StopRoa()
{
}

void SoaRoaSkeletonImpl::ResetRoaDetectInfo()
{
}

void SoaRoaSkeletonImpl::SetRoaMode(const eevp::control::SoaRoaMode& mode)
{
}



} // namespace control
} // namespace eevp
