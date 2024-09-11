#include "SoaRcurtainSkeletonImpl.hpp"
#include <Common.h>
#include <SoaDataType.h>
#include <Api_SoaRcurtain.hpp>
#include <Log.hpp>

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {
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

    this->mStatus.errorState = eevp::control::SoaErrorState::kOK;
    this->mStatus.curMotorDirection = eevp::control::SoaRctnMotorDir::kSTOP;
    this->mStatus.curtainState = eevp::control::SoaRctnState::kFULLY_UP;
    this->mStatus.isNormal = eevp::control::SoaDeviceIsNormal::kNORMAL;
    this->mSwVersion = 0;

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
    LOG_INFO() << "mSW version is" << this->mSwVersion;
    return promise.get_future();
}

SoaRcurtainSkeletonImpl::~SoaRcurtainSkeletonImpl() {
    StopOfferService();
}

ara::core::Future<SoaRcurtainSkeleton::RequestRearCurtainOperationOutput> SoaRcurtainSkeletonImpl::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir)
{
    RequestRearCurtainOperationOutput response;
    ara::core::Promise<RequestRearCurtainOperationOutput> promise;

    LOG_DEBUG() << "[SoaRcurtainSkeletonImpl::RequestRearCurtainOperation] (+)\n";

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

    LOG_DEBUG() << "[SoaRcurtainSkeletonImpl::RequestRearCurtainOperation] (-)\n";
    return promise.get_future();
}

void SoaRcurtainSkeletonImpl::RequestRearCurtainPosition(const std::uint8_t& posPercentage)
{
    if (this->mSwVersion > 0)
    {
        Api_Rcurtain_Method_RequestRearCurtainPosition((int)posPercentage);
    }
}

void SoaRcurtainSkeletonImpl::SetSoaRctnStatus(eevp::control::SoaRctnStatus status)
{
    LOG_DEBUG() << "[SoaRcurtainSkeletonImpl::SetSoaRctnStatus] (+)\n";
    if ((this->mStatus.errorState != status.errorState) ||
        (this->mStatus.curMotorDirection != status.curMotorDirection) ||
        (this->mStatus.curtainState != status.curtainState) ||
        (this->mStatus.isNormal != status.isNormal))
    {
        this->mStatus = status;
        soaRctnStatus.Update(this->mStatus);
    }
    LOG_DEBUG() << "[SoaRcurtainSkeletonImpl::SetSoaRctnStatus] (-)\n";
}

} // namespace control
} // namespace eevp
