#include "SoaRcurtainSkeletonImpl.hpp"
#include <Common.h>
#include <SoaDataType.h>
#include <Api_SoaRcurtain.hpp>
#include <VehicleContext.hpp>
#include <Log.hpp>

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {

static SoaRctnMotorDir convert_RCtnSwitch_to_SoaRctnMotorDir(RCtnSwitch_e val)
{
    switch (val)
    {
    case eRCtnSwitch_Off:
        return SoaRctnMotorDir::kSTOP;
    case eRCtnSwitch_OpenOn:
        return SoaRctnMotorDir::kDOWN;
    case eRCtnSwitch_CloseOn:
        return SoaRctnMotorDir::kUP;
    default:
        break;
    }

    return SoaRctnMotorDir::kSTOP;
}

static SoaRctnState convert_RctnState_to_SoaRctnState(RCtnState_e val)
{
    switch (val)
    {
    case eRCtnState_FullyOpened:
        return SoaRctnState::kFULLY_DOWN;
    case eRCtnState_FullyClosed:
        return SoaRctnState::kFULLY_UP;
    case eRCtnState_PartlyOpened:
        return SoaRctnState::kPARTLY_OPENED;
    case eRCtnState_Opening:
        return SoaRctnState::kMOVING_DOWN;
    case eRCtnState_Closing:
        return SoaRctnState::kMOVING_UP;
    default:
        break;
    }

    return SoaRctnState::kFULLY_DOWN;
}

static SoaDeviceIsNormal convert_DeviceNormal_to_SoaDeviceIsNormal(DeviceNormal_e val)
{
    switch (val)
    {
    case eDeviceNormal_Ok:
        return SoaDeviceIsNormal::kNORMAL;
    case eDeviceNormal_Abnormal:
        return SoaDeviceIsNormal::kABNORMAL;
    default:
        break;
    }

    return SoaDeviceIsNormal::kABNORMAL;
}

bool SoaRcurtainSkeletonImpl::updateFieldWithContext(void)
{
    bool is_changed = false;
    VehicleContext *context = VehicleContext::GetInstance();
    SoaRctnMotorDir curMotorDirection = convert_RCtnSwitch_to_SoaRctnMotorDir(context->mRctnSwitch);
    SoaRctnState curtainState = convert_RctnState_to_SoaRctnState(context->mRctnState);
    SoaDeviceIsNormal isNormal = convert_DeviceNormal_to_SoaDeviceIsNormal(context->mIsNormal);

    if (this->mStatus.curMotorDirection != curMotorDirection)
    {
        this->mStatus.curMotorDirection = curMotorDirection;
        is_changed = true;
    }

    if (this->mStatus.curtainState != curtainState)
    {
        this->mStatus.curtainState = curtainState;
        is_changed = true;
    }

    if (this->mStatus.isNormal != isNormal)
    {
        this->mStatus.isNormal = isNormal;
        is_changed = true;
    }


    return is_changed;
}

SoaRcurtainSkeletonImpl::SoaRcurtainSkeletonImpl(
        ara::core::InstanceSpecifier instanceSpec,
        ara::com::MethodCallProcessingMode mode) :
    SoaRcurtainSkeleton(instanceSpec, mode),
    mLogger(ara::log::CreateLogger("SOA", "RCTN", ara::log::LogLevel::kInfo))
{
    auto soaRctnStatus_get_handler = [this]() {
        return this->soaRctnStatusGetter();
    };

    auto soaRctnSwVersion_get_handler = [this]() {
        return this->soaRctnSwVersionGetter();
    };

    VehicleContext *context = VehicleContext::GetInstance();
    this->mStatus.errorState = eevp::control::SoaErrorState::kOK;
    updateFieldWithContext();
    this->mSwVersion = (std::uint8_t)SW_VERSION;

    soaRctnStatus.RegisterGetHandler(soaRctnStatus_get_handler);
    soaRctnSwVersion.RegisterGetHandler(soaRctnSwVersion_get_handler);
}

ara::core::Future<fields::soaRctnStatus::FieldType> SoaRcurtainSkeletonImpl::soaRctnStatusGetter()
{
    LOG_DEBUG() << "(+)\n";
    ara::core::Promise<fields::soaRctnStatus::FieldType> promise;
    promise.set_value(this->mStatus);
    LOG_DEBUG() << "(-)\n";
    return promise.get_future();
}

ara::core::Future<fields::soaRctnSwVersion::FieldType> SoaRcurtainSkeletonImpl::soaRctnSwVersionGetter()
{
    LOG_DEBUG() << "(+)\n";
    ara::core::Promise<fields::soaRctnSwVersion::FieldType> promise;
    promise.set_value(this->mSwVersion);
    LOG_DEBUG() << "(-)\n";
    return promise.get_future();
}

SoaRcurtainSkeletonImpl::~SoaRcurtainSkeletonImpl() {
    StopOfferService();
}

ara::core::Future<SoaRcurtainSkeleton::RequestRearCurtainOperationOutput> SoaRcurtainSkeletonImpl::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir)
{
    RequestRearCurtainOperationOutput response;
    ara::core::Promise<RequestRearCurtainOperationOutput> promise;

    LOG_DEBUG() << "(+)\n";

    RCtnSwitch_e eBtnValue;
    switch (motorDir)
    {
    case eevp::control::SoaRctnMotorDir::kDOWN:
        eBtnValue = eRCtnSwitch_OpenOn;
        break;

    case eevp::control::SoaRctnMotorDir::kUP:
        eBtnValue = eRCtnSwitch_CloseOn;
        break;

    case eevp::control::SoaRctnMotorDir::kSTOP:
    default:
        eBtnValue = eRCtnSwitch_Off;
        break;
    }

    int ret = Api_Rcurtain_Method_RequestRearCurtainOperation(eBtnValue);
    response.err = (ret == 0) ? eevp::control::SoaErrorState::kOK : eevp::control::SoaErrorState::kERROR;
    promise.set_value(response);

    LOG_DEBUG() << "(-)\n";
    return promise.get_future();
}

void SoaRcurtainSkeletonImpl::RequestRearCurtainPosition(const std::uint8_t& posPercentage)
{
    LOG_DEBUG() << "(+)\n";
    if (this->mSwVersion > 0)
    {
        Api_Rcurtain_Method_RequestRearCurtainPosition((int)posPercentage);
    }
    LOG_DEBUG() << "(-)\n";
}

void SoaRcurtainSkeletonImpl::UpdateStatus(void)
{
    LOG_DEBUG() << "(+)\n";
    if (updateFieldWithContext())
    {
        LOG_DEBUG() << "Data updated: Notify\n";
        soaRctnStatus.Update(this->mStatus);
    }
    LOG_DEBUG() << "(-)\n";

}

} // namespace control
} // namespace eevp
