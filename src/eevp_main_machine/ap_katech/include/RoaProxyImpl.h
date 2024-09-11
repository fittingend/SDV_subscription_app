#ifndef EEVP_ROA_PROXY_IMPL_H_
#define EEVP_ROA_PROXY_IMPL_H_
#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soaroa_proxy.h"
#include "ara/log/logger.h"

#include "KatechRoaListener.h"

namespace eevp {
namespace control {
namespace roa {

class RoaProxyImpl {
public:
    RoaProxyImpl();
    ~RoaProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::roa::KatechRoaListener> _listener);
    bool init();

    // method
    //eevp::control::SoaErrorState requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir);

    // field getter
    bool getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);
    bool getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount);

    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaRoaSwVersion(std::uint8_t& roaSwVersion);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribeRoaSwVersion();
    void SubscribeRoaDeviceNormal();

    /// @brief Subscribe Field
    void SubscribeField();

    /// @brief Unsubscribe Field
    void UnsubscribeField();


    // callback func
    void cbSoaRoaIsDeviceNormal();
    void cbSoaRoaSwVersion();
    // // callback func
    void cbSoaRoaDetectState();
    void StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state);
    /// @brief Process received field value 
    void GetFieldValue();
    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::roa::KatechRoaListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaRoaProxy> mProxy;
    //std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::unique_ptr<eevp::control::proxy::SoaRoaProxy> mRPort{nullptr};
    /// @brief FindServiceHandle
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;
    /// @brief Current ProxyHandle
    eevp::control::proxy::SoaRoaProxy::HandleType mProxyHandle;
    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace ROA
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_ROA_PROXY_IMPL_H_