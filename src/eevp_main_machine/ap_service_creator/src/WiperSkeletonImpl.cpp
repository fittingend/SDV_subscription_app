#include "WiperSkeletonImpl.h"
#include "ServiceCreator.h"

using namespace ara::core;
using namespace eevp::simulation;

namespace eevp
{
    namespace simulation
    {

        WiperSkeletonImpl::WiperSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : BCM_WiperWashSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("PWPR", "PWPR", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;

            auto wiperLevel_get_handler = [this]()
            {
                return this->wiperLevelGetter();
            };

            auto wiperInterval_get_handler = [this]()
            {
                return this->wiperIntervalGetter();
            };
            updateWiperLevelContext();
            wiperLevel.RegisterGetHandler(wiperLevel_get_handler);
            wiperInterval.RegisterGetHandler(wiperInterval_get_handler);
        }

        bool WiperSkeletonImpl::updateWiperLevelContext()
        {
            eevp::simulation::BCM_WipingLevel wipingLevel = eevp::simulation::BCM_WipingLevel::MEDIUM;
            this->mWiperLevel = wipingLevel;
            return true;
        }

        WiperSkeletonImpl::~WiperSkeletonImpl()
        {
            StopOfferService();
        }

        void
        WiperSkeletonImpl::setEventListener(std::shared_ptr<IWiperListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::BCM_WiperWashSkeleton::isWipingOutput> WiperSkeletonImpl::isWiping()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::BCM_WiperWashSkeleton::isWipingOutput> promise;
            updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return promise.get_future();
        }

        Future<skeleton::BCM_WiperWashSkeleton::getWipingLevelOutput> WiperSkeletonImpl::getWipingLevel()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::BCM_WiperWashSkeleton::getWipingLevelOutput> promise;
            updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return promise.get_future();
        }

        Future<skeleton::BCM_WiperWashSkeleton::getWipingIntervalOutput> WiperSkeletonImpl::getWipingInterval()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::BCM_WiperWashSkeleton::getWipingIntervalOutput> promise;
            updateWipingInterval(ServiceCreator::wiperRecv.wipingInterval);
            return promise.get_future();
        }

        // proxy 에서만 사용
        Future<skeleton::BCM_WiperWashSkeleton::stopWipingOutput> WiperSkeletonImpl::stopWiping()
        {
            mLogger.LogInfo() << __func__;
        }

        Future<skeleton::BCM_WiperWashSkeleton::startWipingOutput> WiperSkeletonImpl::startWiping()
        {
            mLogger.LogInfo() << __func__;
        }
        Future<skeleton::BCM_WiperWashSkeleton::setWipingLevelOutput> WiperSkeletonImpl::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::BCM_WiperWashSkeleton::setWipingLevelOutput> promise;
            ServiceCreator::wiperSend.wipingLevel = wipingLevel;
            promise.set_value(this->mWiperInterval);
            updateWipingLevel(wipingLevel);
            return promise.get_future();
        }

        Future<skeleton::BCM_WiperWashSkeleton::setWipingLevelImmeOutput> WiperSkeletonImpl::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
        }

        Future<skeleton::BCM_WiperWashSkeleton::setWipingIntervalOutput> WiperSkeletonImpl::setWipingInterval(const std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::BCM_WiperWashSkeleton::setWipingIntervalOutput> promise;
            ServiceCreator::wiperSend.wipingInterval = wipingInterval;
            updateWipingInterval(wipingInterval);
            return promise.get_future();
        }

        Future<simulation::skeleton::fields::wiperInterval::FieldType>
        WiperSkeletonImpl::wiperIntervalGetter()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<simulation::skeleton::fields::wiperInterval::FieldType> promise;
            promise.set_value(this->mWiperInterval);
            return promise.get_future();
        }

        void
        WiperSkeletonImpl::updateWipingInterval(const std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            if (this->mWiperInterval != wipingInterval)
            {
                this->mWiperInterval = wipingInterval;
                auto updateResult = wiperInterval.Update(this->mWiperInterval);
                if (!updateResult.HasValue())
                {
                    mLogger.LogError() << "Update failed: " << updateResult.Error().Message();
                }
                mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingInterval) << ")";
            }
        }

        Future<simulation::skeleton::fields::wiperLevel::FieldType>
        WiperSkeletonImpl::wiperLevelGetter()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<simulation::skeleton::fields::wiperLevel::FieldType> promise;
            promise.set_value(this->mWiperLevel);
            return promise.get_future();
        }

        void
        WiperSkeletonImpl::updateWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            if (this->mWiperLevel != wipingLevel)
            {
                this->mWiperLevel = wipingLevel;
                auto updateResult = wiperLevel.Update(this->mWiperLevel);
                if (!updateResult.HasValue())
                {
                    mLogger.LogError() << "Update failed: " << updateResult.Error().Message();
                }
                mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingLevel) << ")";
            }
        }
    }
}