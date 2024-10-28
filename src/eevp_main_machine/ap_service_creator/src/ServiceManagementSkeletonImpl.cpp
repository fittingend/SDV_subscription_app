#include "ServiceManagementSkeletonImpl.h"
#include "ServiceCreator.h"

using namespace ara::core;
using namespace eevp::service;
using namespace eevp::service::type;
using namespace eevp::simulation;

namespace eevp
{
    namespace service
    {

        ServiceManagementSkeletonImpl::ServiceManagementSkeletonImpl(
            InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode) : listener{nullptr},
                                                       ServiceManagementSkeleton(instanceSpec, mode),
                                                       mLogger(ara::log::CreateLogger("SMGR", "SMGR", ara::log::LogLevel::kInfo))
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

            wiperLevel.RegisterGetHandler(wiperLevel_get_handler);
            wiperInterval.RegisterGetHandler(wiperInterval_get_handler);
        }

        ServiceManagementSkeletonImpl::~ServiceManagementSkeletonImpl()
        {
            StopOfferService();
        }

        void
        ServiceManagementSkeletonImpl::setEventListener(std::shared_ptr<IServiceManagementListener> _listener)
        {
            listener = _listener;
        }

        Future<skeleton::ServiceManagementSkeleton::isWipingOutput> ServiceManagementSkeletonImpl::isWiping()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::ServiceManagementSkeleton::isWipingOutput> promise;
            updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return promise.get_future();
        }

        Future<skeleton::ServiceManagementSkeleton::getWipingLevelOutput> ServiceManagementSkeletonImpl::getWipingLevel()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::ServiceManagementSkeleton::getWipingLevelOutput> promise;
            updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return promise.get_future();
        }

        Future<skeleton::ServiceManagementSkeleton::getWipingIntervalOutput> ServiceManagementSkeletonImpl::getWipingInterval()
        {
            mLogger.LogInfo() << __func__;
            ara::core::Promise<skeleton::ServiceManagementSkeleton::getWipingIntervalOutput> promise;
            updateWipingInterval(ServiceCreator::wiperRecv.wipingInterval);
            return promise.get_future();
        }

        // proxy 에서만 사용
        Future<skeleton::ServiceManagementSkeleton::stopWipingOutput> ServiceManagementSkeletonImpl::stopWiping()
        {
            mLogger.LogInfo() << __func__;
        }

        Future<skeleton::ServiceManagementSkeleton::startWipingOutput> ServiceManagementSkeletonImpl::startWiping()
        {
            mLogger.LogInfo() << __func__;
        }
        Future<skeleton::ServiceManagementSkeleton::setWipingLevelOutput> ServiceManagementSkeletonImpl::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
        }

        Future<skeleton::ServiceManagementSkeleton::setWipingLevelImmeOutput> ServiceManagementSkeletonImpl::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
        }

        Future<skeleton::ServiceManagementSkeleton::setWipingIntervalOutput> ServiceManagementSkeletonImpl::setWipingInterval(const std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
        }

        Future<service::skeleton::fields::wiperInterval::FieldType>
        ServiceManagementSkeletonImpl::wiperIntervalGetter()
        {
            ara::core::Promise<service::skeleton::fields::wiperInterval::FieldType> promise;
            promise.set_value(this->wiperIntervalField);
            return promise.get_future();
        }

        void
        ServiceManagementSkeletonImpl::updateWipingInterval(const std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            wiperInterval.Update(wipingInterval);
            mLogger.LogInfo() << __func__ << "(" << static_cast<uint16_t>(wipingInterval) << ")";
        }

        Future<service::skeleton::fields::wiperLevel::FieldType>
        ServiceManagementSkeletonImpl::wiperLevelGetter()
        {
            ara::core::Promise<service::skeleton::fields::wiperLevel::FieldType> promise;
            promise.set_value(this->wiperLevelField);
            return promise.get_future();
        }
        void
        ServiceManagementSkeletonImpl::updateWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            wiperLevel.Update(wipingLevel);
            mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingLevel) << ")";
        }
    }
}
