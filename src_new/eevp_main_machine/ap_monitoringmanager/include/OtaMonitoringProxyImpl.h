#ifndef EEVP_OTA_MONITORING_PROXY_IMPL_H_
#define EEVP_OTA_MONITORING_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/ota/monitoring/service/otamonitoring_proxy.h"
#include "ara/log/logger.h"

#include "IOtaMonitoringListener.h"

namespace eevp {
namespace monitoring {

class OtaMonitoringProxyImpl {
public:
    OtaMonitoringProxyImpl();
    ~OtaMonitoringProxyImpl();

    void setEventListener(std::shared_ptr<eevp::monitoring::IOtaMonitoringListener> _listener);
    bool init();

    // method
    bool requestServiceInstall(const eevp::type::String& serviceName);
    bool requestServiceUpdate(const eevp::type::String& serviceName);
    bool requestVersionInfo(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap);
    void resetUcmTest();

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::ota::monitoring::service::proxy::OtaMonitoringProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Event
    void SubscribeEvent();
    /// @brief Subscribe Field
    void SubscribeField();

    /// @brief Unsubscribe Event
    void UnsubscribeEvent();
    /// @brief Unsubscribe Field
    void UnsubscribeField();

    // callback func
    void cbServiceInfoEvent();
    void cbServiceUpdateEvent();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::monitoring::IOtaMonitoringListener> listener;
    std::shared_ptr<eevp::ota::monitoring::service::proxy::OtaMonitoringProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;
    eevp::ota::monitoring::type::RequestServiceInfo requestServiceInfo;
    eevp::ota::monitoring::type::UpdatableServiceInfo updatableServiceInfo;


    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace monitoring
} // namespace eevp

#endif /// EEVP_OTA_MONITORING_PROXY_IMPL_H_