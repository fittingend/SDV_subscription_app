#ifndef EEVP_DRVSEAT_PROXY_IMPL_H_
#define EEVP_DRVSEAT_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soadriverseat_proxy.h"

#include "ara/log/logger.h"

#include "IDrvseatListener.h"

namespace eevp {
namespace control {
namespace drvseat {

class DrvseatProxyImpl {
public:
    DrvseatProxyImpl();
    ~DrvseatProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::drvseat::IDrvseatListener> _listener);
    bool init();

    void getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaDrvseatSwVersion(std::uint8_t& drvseatSwVersion);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaDriverSeatProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Field
    void SubscribeDrvSeatSwVersion();
    void SubscribeDrvSeatDeviceNormal();

    /// @brief Unsubscribe Field
    void UnsubscribeField();



    // callback func
    void cbSoaDrvseatIsDeviceNormal();
    void cbSoaDrvseatSwVersion();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::drvseat::IDrvseatListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaDriverSeatProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace drvseat
} // namespace control
} // namespace eevp

#endif /// EEVP_DRVSEAT_PROXY_IMPL_H_