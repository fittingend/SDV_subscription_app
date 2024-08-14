#ifndef EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_
#define EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_

#include "ara/log/logger.h"
#include "eevp/monitoring/service/monitoringmanagement_skeleton.h"

#include "IMonitoringManagementListener.h"

using namespace ara::core;

namespace eevp {
namespace monitoring {

class MonitoringManagementSkeletonImpl : public eevp::monitoring::service::skeleton::MonitoringManagementSkeleton {
public:
    MonitoringManagementSkeletonImpl(
            InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEventSingleThread);

    ~MonitoringManagementSkeletonImpl();

    void setEventListener(std::shared_ptr<eevp::monitoring::IMonitoringManagementListener> _listener);

    Future<requestAppInstallOutput> requestAppInstall(const eevp::type::String& serviceName) override;
    Future<requestAppUpdateOutput> requestAppUpdate(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceInfoOutput> requestControllerServiceInfo(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceInfoAllOutput> requestControllerServiceInfoAll() override;
    Future<requestControllerServiceStatusOutput> requestControllerServiceStatus(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceStatusAllOutput> requestControllerServiceStatusAll() override;
    Future<setEnableControllerServiceOutput> setEnableControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& enable) override;
    Future<requestControllerServiceInfoAllSpareOutput> requestControllerServiceInfoAllSpare() override;
    Future<requestControllerServiceStatusAllSpareOutput> requestControllerServiceStatusAllSpare() override;
    Future<setControlControllerServiceOutput> setControlControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& serviceControl) override;

    Future<resetUcmTestOutput> resetUcmTest() override;

//    void sendNotifyServiceEvent(eevp::monitoring::type::ControllerServiceInfoSpare& info);

    void sendeventServiceInfo();
    void sendeventServiceStatus();

    void sendeventServiceError(eevp::monitoring::type::ControllerServiceErrorEvent& info);
    void sendeventServiceInfoSpare(eevp::monitoring::type::ControllerServiceInfoSpare& info);
    void sendeventServiceStatusSpare(eevp::monitoring::type::ControllerServiceStatusSpare& info);
    void sendupdatableserviceEvent(eevp::monitoring::type::UpdatableServiceList& info);

private:
    ara::log::Logger& mLogger;
    std::shared_ptr<IMonitoringManagementListener> listener;
};

} /// namespace monitoring
} /// namespace eevp

#endif /// EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_
