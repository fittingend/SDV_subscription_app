#include "skeleton/LotteSkeletonImpl.h"

namespace eevp
{
    namespace simulation
    {
        LotteSkeletonImpl::LotteSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       LotteServiceSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("LTSV", "LTSV", ara::log::LogLevel::kInfo))

        {
            mLogger.LogInfo() << __func__;
        }
        
        LotteSkeletonImpl::~LotteSkeletonImpl()
        {
            StopOfferService();
        }

        void
        LotteSkeletonImpl::setEventListener(std::shared_ptr<ILotteListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::LotteServiceSkeleton::DmsCurrOutput>
        LotteSkeletonImpl::DmsCurr()
        {
            mLogger.LogInfo() << __func__;

            skeleton::LotteServiceSkeleton::DmsCurrOutput response;
            Promise<DmsCurrOutput> promise;

            if (listener != nullptr)
            {
                listener->NotifyDmsCurr(response.result);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::LotteServiceSkeleton::DmsStatusOutput> LotteSkeletonImpl::DmsStatus()
        {
            mLogger.LogInfo() << __func__;

            skeleton::LotteServiceSkeleton::DmsStatusOutput response;
            Promise<DmsStatusOutput> promise;

            if (listener != nullptr)
            {
                listener->NotifyDmsStatus(response.result);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::LotteServiceSkeleton::SmartFilmControlOutput>
        LotteSkeletonImpl::SmartFilmControl(const std::int32_t &windowLoc, const std::int32_t &transparence)
        {
            mLogger.LogInfo() << __func__;

            skeleton::LotteServiceSkeleton::SmartFilmControlOutput response;
            Promise<SmartFilmControlOutput> promise;

            if (listener != nullptr)
            {
                listener->SmartFilmControl(windowLoc, transparence);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::LotteServiceSkeleton::SmartFilmCurrOutput>
        LotteSkeletonImpl::SmartFilmCurr()
        {
            mLogger.LogInfo() << __func__;

            skeleton::LotteServiceSkeleton::SmartFilmCurrOutput response;
            Promise<SmartFilmCurrOutput> promise;

            if (listener != nullptr)
            {
                listener->NotifySmartFilmCurr(response.result);
            }

            promise.set_value(response);
            return promise.get_future();
        }

        Future<skeleton::LotteServiceSkeleton::SmartFilmStatusOutput>
        LotteSkeletonImpl::SmartFilmStatus()
        {
            mLogger.LogInfo() << __func__;

            skeleton::LotteServiceSkeleton::SmartFilmStatusOutput response;
            Promise<SmartFilmStatusOutput> promise;

            if (listener != nullptr)
            {
                listener->NotifySmartFilmStatus(response.result);
            }

            promise.set_value(response);
            return promise.get_future();
        }
    }
}
