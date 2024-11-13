#include "skeleton/SnsrUssSkeletonImpl.h"

namespace eevp
{
    namespace simulation
    {
        SnsrUssSkeletonImpl::SnsrUssSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       Snsr_USSSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("SNUS", "SNUS", ara::log::LogLevel::kInfo))

        {
            mLogger.LogInfo() << __func__;
        }

        SnsrUssSkeletonImpl::~SnsrUssSkeletonImpl()
        {
            StopOfferService();
        }

        void
        SnsrUssSkeletonImpl::setEventListener(std::shared_ptr<ISnsrUssListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::Snsr_USSSkeleton::ntfSonarInfoOutput>
        SnsrUssSkeletonImpl::ntfSonarInfo()
        {
            mLogger.LogInfo() << __func__;

            skeleton::Snsr_USSSkeleton::ntfSonarInfoOutput response;
            Promise<ntfSonarInfoOutput> promise;

            if (listener != nullptr)
            {
                listener->ntfSonarInfo(response.UssSonarinfo);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::Snsr_USSSkeleton::ntfFltStOutput>
        SnsrUssSkeletonImpl::ntfFltSt()
        {
            mLogger.LogInfo() << __func__;
        }

    }
}