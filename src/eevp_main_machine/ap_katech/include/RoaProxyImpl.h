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

    // method
    //eevp::control::SoaErrorState requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir);

    // field getter
    bool getterSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribeField();

    /// @brief Unsubscribe Field
    void UnsubscribeField();

    // callback func
    void cbSoaRoaDetectState();
    void StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state);
    /// @brief Process received field value 
    void GetFieldValue();
    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::roa::IRoaListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaRoaProxy> mProxy;
    //std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::unique_ptr<eevp::control::proxy::SoaRoaProxy> mRPort{nullptr};
    /// @brief FindServiceHandle
    ara::com::FindServiceHandle* mFindHandle{nullptr};
    /// @brief Current ProxyHandle
    eevp::control::proxy::SoaRoaProxy::HandleType mProxyHandle;
    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace ROA
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_ROA_PROXY_IMPL_H_