#include "skeleton/VehSpdSkeletonImpl.h"

namespace eevp
{
    namespace simulation
    {
        VehSpdSkeletonImpl::VehSpdSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       VCS_VehSpdSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("VHSP", "VHSP", ara::log::LogLevel::kInfo))

        {
            mLogger.LogInfo() << __func__;
        }

        VehSpdSkeletonImpl::~VehSpdSkeletonImpl()
        {
            StopOfferService();
        }

        void
        VehSpdSkeletonImpl::setEventListener(std::shared_ptr<IVehSpdListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::VCS_VehSpdSkeleton::notifyStatusOutput>
        VehSpdSkeletonImpl::notifyStatus()
        {
            mLogger.LogInfo() << __func__;

            skeleton::VCS_VehSpdSkeleton::notifyStatusOutput response;
            Promise<notifyStatusOutput> promise;

            if (listener != nullptr)
            {
                listener->notifyVehSpd(response.VCS_VehSpd);
            }

            promise.set_value(response);
            return promise.get_future();
        }
    }
}
