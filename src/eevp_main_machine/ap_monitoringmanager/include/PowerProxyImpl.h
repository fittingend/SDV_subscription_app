#ifndef EEVP_POWER_PROXY_IMPL_H_
#define EEVP_POWER_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soapower_proxy.h"

#include "ara/log/logger.h"

#include "IPowerListener.h"

namespace eevp {
namespace control {
namespace power {

class PowerProxyImpl {
public:
    PowerProxyImpl();
    ~PowerProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::power::IPowerListener> _listener);
    bool init();

    void getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaPowerSwVersion(std::uint8_t& powerSwVersion);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaPowerProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribePowerSwVersion();
    void SubscribePowerDeviceNormal();

    /// @brief Unsubscribe Field
    void UnsubscribeField();



    // callback func
    void cbSoaPowerIsDeviceNormal();
    void cbSoaPowerSwVersion();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::power::IPowerListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaPowerProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace power
} // namespace control
} // namespace eevp

#endif /// EEVP_POWER_PROXY_IMPL_H_