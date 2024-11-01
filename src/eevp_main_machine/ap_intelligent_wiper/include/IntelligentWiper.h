#ifndef __INTELLIGENT_WIPER_H__
#define __INTELLIGENT_WIPER_H__

#include <csignal>
#include <thread>
#include <ara/log/logger.h>

#include "WiperProxyImpl.h"

namespace eevp {
namespace simulation {

class IntelligentWiper {
public:
    /// @brief Constructor
    IntelligentWiper();
    /// @brief Destructor
    ~IntelligentWiper();

    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run();
    /// @brief Terminate S/W Component
    void Terminate();
    
    /// @brief notify when user changes wiper values 
    void notifyBCM_WipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel);
    void getBCM_WipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel);
    void IntelligentWiper::execServiceLogic();


private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief Find handler
    void StartFindCallback(ara::com::ServiceHandleContainer<eevp::simulation::proxy::BCM_WiperWashProxy::HandleType> services, ara::com::FindServiceHandle handle);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Find Control Proxy
    bool startWiperProxy();

    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    std::shared_ptr<eevp::simulation::WiperProxyImpl> wiperProxyImpl;
};

}   // namespace simulation
}   // namespace eevp

#endif // __INTELLIGENT_WIPER_H__
