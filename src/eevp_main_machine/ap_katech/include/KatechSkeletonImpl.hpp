#ifndef __SOA_RCURTAIN_SKELETON_IMPL_HPP__
#define __SOA_RCURTAIN_SKELETON_IMPL_HPP__

#include "eevp/control/soarcurtain_skeleton.h"
#include "ara/log/logger.h"
#include <iostream>

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {

class KatechSkeletonImpl : public eevp::control::skeleton::SoaRcurtainSkeleton
{
public:
    KatechSkeletonImpl(
        ara::core::InstanceSpecifier instanceSpec,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);
    ~KatechSkeletonImpl();

    ara::core::Future<SoaRcurtainSkeleton::RequestRearCurtainOperationOutput> RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) override;

    void SetSoaRctnStatus(eevp::control::SoaRctnStatus status);

    void E2EErrorHandler(const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) override
    {
        std::cout << "[KatechSkeletonImpl::KatechSkeletonImpl] errorCode:\n";
    }
private:
    /// @brief Field
    //fields::soaRctnStatus::FieldType mField;
    fields::soaRctnStatus::FieldType rctnStatusField;
    ara::log::Logger& mLogger;

    ara::core::Future<fields::soaRctnStatus::FieldType> soaRctnStatusGetter();
};
} // namespace control
} // namespace eevp




#endif