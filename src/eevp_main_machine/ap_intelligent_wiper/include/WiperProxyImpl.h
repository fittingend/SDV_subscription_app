#ifndef __EEVP_SIMULATION_WIPER_PROXY_IMPL_H_
#define __EEVP_SIMULATION_WIPER_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>  

#include "eevp/simulation/bcm_wiperwash_proxy.h"
#include "ara/log/logger.h"

#include "IWiperListener.h"

namespace eevp {
namespace simulation {

class WiperProxyImpl {
public:
    //static WiperProxyImpl *GetInstance();
    WiperProxyImpl();
    ~WiperProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::simulation::IWiperListener> _listener);
    bool init();
    //bool isWiping();

    // field getter
    bool getBCM_WipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel);

    eevp::simulation::BCM_ReturnCode stopWiping();
    eevp::simulation::BCM_ReturnCode startWiping();

    // eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);
    // eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel);

    // eevp::simulation::BCM_ReturnCode setWipingIneterval(std::uint16_t &wipingInterval);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::simulation::proxy::BCM_WiperWashProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Unsubscribe Field
    void UnsubscribeField();

    /// @brief Subscribe Field
    void SubscribeWiperLevel();
    void SubscribeWiperInterval();

    // callback func
    void cbWiperLevel();
    void cbWiperInterval();

    ara::log::Logger &mLogger;
    std::shared_ptr<eevp::simulation::IWiperListener> listener;
    std::shared_ptr<eevp::simulation::proxy::BCM_WiperWashProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;
    //void getWiperRecv();
    //void getWiperSend();

    std::mutex mHandle;
    std::condition_variable cvHandle;
}; // namespace wiper
} // namespace simulation
} // namespace eevp

#endif