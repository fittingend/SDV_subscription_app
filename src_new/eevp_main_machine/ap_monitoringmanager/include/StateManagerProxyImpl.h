#ifndef IVI_STATEMANAGER_PROXY_IMPL_H_
#define IVI_STATEMANAGER_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "ivi/info/statemanager/service/statemanager_proxy.h"

#include "ara/log/logger.h"

#include "IStateManagerListener.h"

namespace ivi {
namespace info {
namespace statemanager {

class StateManagerProxyImpl {
public:
    StateManagerProxyImpl();
    ~StateManagerProxyImpl();

    void setEventListener(std::shared_ptr<ivi::info::statemanager::IStateManagerListener> _listener);
    bool init();

    // field getter
    bool getterNotifyTime(std::uint8_t& notifyTime);
    bool getterSystemState(ivi::info::statemanager::type::State& state);

    // field setter
    bool setterNotifyTime(const std::uint8_t& notifyTime);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<ivi::info::statemanager::service::proxy::StateManagerProxy::HandleType> container,
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
    void cbNotifySystemState();
    void cbNotifyTime();
    void cbSystemState();

    ara::log::Logger& mLogger;
    std::shared_ptr<ivi::info::statemanager::IStateManagerListener> listener;
    std::shared_ptr<ivi::info::statemanager::service::proxy::StateManagerProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace statemanager
} // namespace info
} // namespace ivi

#endif /// IVI_STATEMANAGER_PROXY_IMPL_H_