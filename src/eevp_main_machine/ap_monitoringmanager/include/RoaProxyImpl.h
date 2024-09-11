#ifndef EEVP_ROA_PROXY_IMPL_H_
#define EEVP_ROA_PROXY_IMPL_H_

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

    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaRoaSwVersion(std::uint8_t& roaSwVersion);
    bool getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);
    bool getSoaRoaDetectCount(uint8_t& soaRoaDetectCount);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribeRoaSwVersion();
    void SubscribeRoaDeviceNormal();

    /// @brief Unsubscribe Field
    void UnsubscribeField();

    // callback func
    void cbSoaRoaIsDeviceNormal();
    void cbSoaRoaSwVersion();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::roa::IRoaListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaRoaProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::unique_ptr<eevp::control::proxy::SoaRoaProxy> mRPort{nullptr};
    eevp::control::proxy::SoaRoaProxy::HandleType mProxyHandle;
    void StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state);
    void SubscribeField();    
    //void GetFieldValue();

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace roa
} // namespace control
} // namespace eevp

#endif /// EEVP_ROA_PROXY_IMPL_H_