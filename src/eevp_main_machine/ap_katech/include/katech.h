#include "eevp/control/soaroa_proxy.h"

#include <csignal>
#include <thread>

#include <ara/log/logger.h>

#include <queue>
#include <mutex>
#include <condition_variable>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "IRoaListener.h"
#include "IWiperListener.h"

#include "RoaProxyImpl.h"
#include "RearCurtainProxyImpl.h"
#include "WiperProxyImpl.h"

#define RCTN_OP_TIME 3
using namespace ara::core;
using namespace eevp::simulation;

namespace eevp
{
    namespace control
    {

        class KATECH
        {
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
            void notifySoaRoaDetectCount(const std::uint8_t &detectCount);
            void getSoaRoaDetectState(eevp::control::SoaRoaDetectState &soaRoaDetectState);
            void getSoaRoaDetectCount(std::uint8_t &soaRoaDetectCount);

            /// Rear Curtain
            void getSoaRctnStatus(eevp::control::SoaRctnStatus &fieldValue);
            bool requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir &motorDir);
            void requestRearCurtainPosition(const std::uint8_t &posPercentage);

            /// Wiper
            bool isWiping();
            std::uint16_t getWipingInterval();
            eevp::simulation::BCM_WipingLevel getWipingLevel();
            eevp::simulation::BCM_ReturnCode stopWiping();
            eevp::simulation::BCM_ReturnCode startWiping();
            eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval);
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            bool checkRctnReady();

        private:
            /// @brief Signal Handler
            static void SignalHandler(std::int32_t signal);

            /// @brief Find handler
            void StartFindCallback(ara::com::ServiceHandleContainer<eevp::simulation::proxy::BCM_WiperWashProxy::HandleType> services, ara::com::FindServiceHandle handle);

            /// @brief set Running State
            bool setRunningState();

            /// @brief Find Control Proxy
            bool startRoaProxy();
            /// @brief Find RearCurtain Proxy
            bool startRearCurtainProxy();
            /// @brief Find RearCurtain Proxy
            bool startWiperProxy();
            /// @brief Flag of Running
            static std::atomic_bool mRunning;
            /// @brief Logger
            ara::log::Logger &mLogger;

            std::shared_ptr<eevp::control::roa::RoaProxyImpl> roaProxyImpl;
            std::shared_ptr<eevp::control::rearcurtain::RearCurtainProxyImpl> rearCurtainProxyImpl;
            std::shared_ptr<eevp::simulation::WiperProxyImpl> wiperProxyImpl;
        };

    } // namespace monitoring
} // namespace eevp
