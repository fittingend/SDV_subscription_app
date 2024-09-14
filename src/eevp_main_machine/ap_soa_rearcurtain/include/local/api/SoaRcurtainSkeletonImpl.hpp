#ifndef __SOA_RCURTAIN_SKELETON_IMPL_HPP__
#define __SOA_RCURTAIN_SKELETON_IMPL_HPP__

#include "eevp/control/soarcurtain_skeleton.h"
#include "ara/log/logger.h"
#include <iostream>

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {

class SoaRcurtainSkeletonImpl : public eevp::control::skeleton::SoaRcurtainSkeleton
{
public:
    SoaRcurtainSkeletonImpl(
        ara::core::InstanceSpecifier instanceSpec,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);
    ~SoaRcurtainSkeletonImpl();

    ara::core::Future<SoaRcurtainSkeleton::RequestRearCurtainOperationOutput> RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) override;
    void RequestRearCurtainPosition(const std::uint8_t& posPercentage) override;

    void UpdateStatus(void);

    void E2EErrorHandler(const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) override
    {
        std::cout << "[SoaRcurtainSkeletonImpl::SoaRcurtainSkeletonImpl] errorCode:\n";
    }
private:
    /// @brief Field
    fields::soaRctnStatus::FieldType mStatus;
    fields::soaRctnSwVersion::FieldType mSwVersion;

    ara::log::Logger& mLogger;

    ara::core::Future<fields::soaRctnStatus::FieldType> soaRctnStatusGetter();
    ara::core::Future<fields::soaRctnSwVersion::FieldType> soaRctnSwVersionGetter();
    bool updateFieldWithContext();
};
} // namespace control
} // namespace eevp




#endif