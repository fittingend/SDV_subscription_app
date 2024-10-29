#ifndef __SERVICE_MANAGEMENT_SKELETON_H__
#define __SERVICE_MANAGEMENT_SKELETON_H__

#include "ara/log/logger.h"
#include "eevp/service/servicemanagement_skeleton.h"

#include "IServiceManagementListener.h"

using namespace ara::core;

namespace eevp
{
    namespace service
    {
        class ServiceManagementSkeletonImpl : public eevp::service::skeleton::ServiceManagementSkeleton
        {
        public:
            ServiceManagementSkeletonImpl(
                InstanceSpecifier instanceSpec,
                ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEventSingleThread);

            ~ServiceManagementSkeletonImpl();

            void setEventListener(std::shared_ptr<eevp::service::IServiceManagementListener> _listener);


            Future<stopWipingOutput> stopWiping();

            Future<startWipingOutput> startWiping();

            Future<isWipingOutput> isWiping();

            Future<getWipingLevelOutput> getWipingLevel();

            Future<getWipingIntervalOutput> getWipingInterval();

            Future<setWipingLevelOutput> setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            Future<setWipingLevelImmeOutput> setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            Future<setWipingIntervalOutput> setWipingInterval(const std::uint16_t &wipingInterval);

            Future<service::skeleton::fields::wiperLevel::FieldType> wiperLevelGetter();
            void updateWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            Future<service::skeleton::fields::wiperInterval::FieldType> wiperIntervalGetter();
            void updateWipingInterval(const std::uint16_t &wipingInterval);

        private:
            ara::log::Logger &mLogger;
            std::shared_ptr<IServiceManagementListener> listener;

            service::skeleton::fields::wiperLevel::FieldType wiperLevelField;
            service::skeleton::fields::wiperInterval::FieldType wiperIntervalField;
        };
    } // namespace service
} // namespace eevp

#endif // __SERVICE_MANAGEMENT_SKELETON_H__