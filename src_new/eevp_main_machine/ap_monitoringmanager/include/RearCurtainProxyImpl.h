#ifndef EEVP_CONTROL_REARCURTAIN_PROXY_IMPL_H_
#define EEVP_CONTROL_REARCURTAIN_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soarcurtain_proxy.h"
#include "ara/log/logger.h"

#include "IRearCurtainListener.h"

namespace eevp {
namespace control {
namespace rearcurtain {

class RearCurtainProxyImpl {
public:
    RearCurtainProxyImpl();
    ~RearCurtainProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::rearcurtain::IRearCurtainListener> _listener);
    bool init();

    // method
    eevp::control::SoaErrorState requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir);

    // field getter
    bool getterSoaRctnStatus(eevp::control::SoaRctnStatus& soaRctnStatus);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRcurtainProxy::HandleType> container,
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
    void cbSoaRctnStatus();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::rearcurtain::IRearCurtainListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaRcurtainProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace rearcurtain
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_REARCURTAIN_PROXY_IMPL_H_