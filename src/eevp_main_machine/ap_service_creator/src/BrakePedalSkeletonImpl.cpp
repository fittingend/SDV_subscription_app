#include "skeleton/BrakePedalSkeletonImpl.h"

namespace eevp
{
    namespace simulation
    {
        BrakePedalSkeletonImpl::BrakePedalSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       VCS_BrakePedalSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("BKPD", "BKPD", ara::log::LogLevel::kInfo))

        {
            mLogger.LogInfo() << __func__;
        }

        BrakePedalSkeletonImpl::~BrakePedalSkeletonImpl()
        {
            StopOfferService();
        }

        void
        BrakePedalSkeletonImpl::setEventListener(std::shared_ptr<IBrakePedalListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::VCS_BrakePedalSkeleton::notifyStatusOutput>
        BrakePedalSkeletonImpl::notifyStatus()
        {
            mLogger.LogInfo() << __func__;

            skeleton::VCS_BrakePedalSkeleton::notifyStatusOutput response;
            Promise<notifyStatusOutput> promise;

            if (listener != nullptr)
            {
                listener->notifyPosn(response.VCS_BrakePosn);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::VCS_BrakePedalSkeleton::notifySwitchOutput>
        BrakePedalSkeletonImpl::notifySwitch()
        {
            mLogger.LogInfo() << __func__;
        }
    }
}
