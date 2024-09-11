#ifndef EEVP_CONTROL_WIPER_PROXY_IMPL_H_
#define EEVP_CONTROL_WIPER_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soawiper_proxy.h"
#include "ara/log/logger.h"

#include "IWiperListener.h"

namespace eevp {
namespace control {
namespace wiper {

class WiperProxyImpl {
public:
    WiperProxyImpl();
    ~WiperProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::wiper::IWiperListener> _listener);
    bool init();

    /// method
    void requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode);
    void setWiperAutoSpeed(const bool& isAutoSpeed);

    /// field getter
    void getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue);
    void getSoaWiperSwVersion(std::uint8_t& wiperSwVersion);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaWiperProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribesoaWiperDeviceNormal();
    void SubscribeSoaWiperStatus();
    void SubscribeSoaWiperSwVersion();

    /// @brief Unsubscribe Field
    void UnsubscribeField();

    // callback func
    void cbSoaWiperIsDeviceNormal();
    void cbSoaWiperStatus();
    void cbSoaWiperSwVersion();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::wiper::IWiperListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaWiperProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace wiper
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_WIPER_PROXY_IMPL_H_