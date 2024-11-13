#include "skeleton/GearSkeletonImpl.h"

namespace eevp
{
    namespace simulation
    {
        GearSkeletonImpl::GearSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       VCS_GearSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("GEAR", "GEAR", ara::log::LogLevel::kInfo))

        {
            mLogger.LogInfo() << __func__;
        }

        GearSkeletonImpl::~GearSkeletonImpl()
        {
            StopOfferService();
        }

        void
        GearSkeletonImpl::setEventListener(std::shared_ptr<IGearListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::VCS_GearSkeleton::notifyStatusOutput>
        GearSkeletonImpl::notifyStatus()
        {
            mLogger.LogInfo() << __func__;

            skeleton::VCS_GearSkeleton::notifyStatusOutput response;
            Promise<notifyStatusOutput> promise;

            if (listener != nullptr)
            {
                listener->notifyGear(response.VCS_Gear);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::VCS_GearSkeleton::setTargetOutput>
        GearSkeletonImpl::setTarget(const eevp::simulation::type::VCS_Gear &targetGear)
        {
            mLogger.LogInfo() << __func__;
        }
    }
}
