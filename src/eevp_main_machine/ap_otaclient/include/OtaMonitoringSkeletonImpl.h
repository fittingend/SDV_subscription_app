#ifndef EEVP_OTA_MONITORING_SKELETON_IMPL_H_
#define EEVP_OTA_MONITORING_SKELETON_IMPL_H_

#include "eevp/ota/monitoring/service/otamonitoring_skeleton.h"
#include "ara/log/logger.h"

#include "IOtaMonitoringListener.h"

namespace eevp {
namespace ota {
namespace monitoring {

class OtaMonitoringSkeletonImpl : public eevp::ota::monitoring::service::skeleton::OtaMonitoringSkeleton {
public:
    OtaMonitoringSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEventSingleThread);

    ~OtaMonitoringSkeletonImpl();

    void setEventListener(std::shared_ptr<eevp::ota::IOtaMonitoringListener> _listener);

    ara::core::Future<requestServiceInstallOutput> requestServiceInstall(const eevp::type::String& appName) override;
    ara::core::Future<requestServiceUpdateOutput> requestServiceUpdate(const eevp::type::String& appName) override;
    ara::core::Future<requestVersionInfoOutput> requestVersionInfo() override;
    ara::core::Future<resetUcmTestOutput> resetUcmTest() override;

    void sendNotifyServiceEvent(eevp::ota::monitoring::type::RequestServiceInfo& info);
    void sendNotifyUpdatableService(eevp::ota::monitoring::type::UpdatableServiceInfo& serviceInfo);

private:
    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::ota::IOtaMonitoringListener> listener;
};

} /// namespace monitoring
} /// namespace ota
} /// namespace eevp

#endif /// EEVP_OTA_MONITORING_SKELETON_IMPL_H_
