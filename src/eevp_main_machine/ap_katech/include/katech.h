#include "eevp/control/soaroa_proxy.h"

#include <csignal>
#include <thread>
#include <ara/log/logger.h>

#include "IRoaListener.h"
#include "RoaProxyImpl.h"
#include "RearCurtainProxyImpl.h"

#define RCTN_OP_TIME 3

namespace eevp {
namespace control {

class KATECH {
public:
    /// @brief Constructor
    KATECH();
    /// @brief Destructor
    ~KATECH();

    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run();
    /// @brief Terminate S/W Component
    void Terminate();

    /// ROA
    void notifySoaRoaDetectCount(const std::uint8_t& detectCount);
    void getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);
    void getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount);

    /// Rear Curtain
    void getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue);
    bool requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir);
    void requestRearCurtainPosition(const std::uint8_t& posPercentage);

    bool checkRctnReady();

private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief Find handler
    void StartFindCallback(ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> services, ara::com::FindServiceHandle handle);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Find Control Proxy
    bool startRoaProxy();
    /// @brief Find RearCurtain Proxy
    bool startRearCurtainProxy();
    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    std::shared_ptr<eevp::control::roa::RoaProxyImpl> roaProxyImpl;
    std::shared_ptr<eevp::control::rearcurtain::RearCurtainProxyImpl> rearCurtainProxyImpl;
};

}   // namespace monitoring
}   // namespace eevp
