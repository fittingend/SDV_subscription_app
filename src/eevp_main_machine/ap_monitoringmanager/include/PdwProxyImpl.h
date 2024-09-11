#ifndef EEVP_PDW_PROXY_IMPL_H_
#define EEVP_PDW_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/pdw/service/main_pdw_service_proxy.h"
#include "ara/log/logger.h"

#include "IPdwListener.h"

namespace eevp {
namespace pdw {

class PdwProxyImpl {
public:
    PdwProxyImpl();
    ~PdwProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::pdw::IPdwListener> _listener);
    bool init();


private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::pdw::service::proxy::Main_PDW_ServiceProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Event
    void SubscribeEvent();

    /// @brief Unsubscribe Event
    void UnsubscribeEvent();

    // callback func
    void cbDistanceLevel();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::pdw::IPdwListener> listener;
    std::shared_ptr<eevp::pdw::service::proxy::Main_PDW_ServiceProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace pdw
} // namespace eevp

#endif /// EEVP_PDW_PROXY_IMPL_H_