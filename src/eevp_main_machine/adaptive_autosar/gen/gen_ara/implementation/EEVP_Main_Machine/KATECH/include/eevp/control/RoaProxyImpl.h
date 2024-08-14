#ifndef EEVP_CONTROL_ROA_PROXY_IMPL_H_
#define EEVP_CONTROL_ROA_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soaroa_proxy.h"
#include "ara/log/logger.h"

#include "IRoaListener.h"

namespace eevp {
namespace control {
namespace roa {

class RoaProxyImpl {
public:
    RoaProxyImpl();
    ~RoaProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::roa::IRoaListener> _listener);
    bool init();

    // field getter
    bool getterSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> container,
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
    //void cbSoaRctnStatus();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::roa::IRoaListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaRoaProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace rearcurtain
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_REARCURTAIN_PROXY_IMPL_H_