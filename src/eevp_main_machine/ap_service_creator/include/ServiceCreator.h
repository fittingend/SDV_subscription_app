#ifndef __SERVICE_CREATOR_H__
#define __SERVICE_CREATOR_H__

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

#include "IWiperListener.h"
#include "IServiceManagementListener.h"

#include "WiperProxyImpl.h"

#include "ServiceManagementSkeletonImpl.h"
#include "WiperSkeletonImpl.h"

#define BUF_SIZE 1024
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {
        class ServiceCreator
        {
        public:
            /// @brief Constructor
            ServiceCreator();
            /// @brief Destructor
            ~ServiceCreator();

            /// @brief Start S/W Component
            bool Start();
            /// @brief Run S/W Component
            void Run();
            /// @brief Terminate S/W Component
            void Terminate();

            // IWiperListener
            bool isWiping();
            std::uint16_t getWipingInterval();
            eevp::simulation::BCM_WipingLevel getWipingLevel();
            eevp::simulation::BCM_ReturnCode stopWiping();
            eevp::simulation::BCM_ReturnCode startWiping();
            eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval);
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            // void isWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void stopWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void startWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void getWipingInterval_C(std::uint16_t &wipingInterval);
            // void getWipingLevel_C(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void setWipingLevelImme_C(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void setWipingInterval_C(std::uint16_t &wipingInterval);
            // void setWipingLevel_C(const eevp::simulation::BCM_WipingLevel &wipingLevel);


            // void getWipingLevel_Subs(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void setWipingLevel_Subs(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            // void getWipinginterval(std::uint16_t &wipingInterval);
            // void getWipinglevel(eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void setWipingLevelimme(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            // void setWipinginterval(std::uint16_t &wipingInterval);
            // void setWipinglevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);

            // WiperVar
            static eevp::service::type::wiperRecv wiperRecv;
            static eevp::service::type::wiperSend wiperSend;

            // Thread
            void poolingFieldUpdate();

            static pthread_t thread_socket_recv;
            static pthread_t thread_socket_send;
            std::thread *updateThread;
            std::atomic<bool> uThreadRunning;
            static void *socket_recv(void *inst);
            static void *socket_send(void *inst);

        private:
            static void SignalHandler(std::int32_t signal);

            /// @brief set Running State
            bool setRunningState();

            bool startWiperProxy();

            bool startSocketClient();

            bool startServiceCreatorStub();

            static std::atomic_bool mRunning;
            ara::log::Logger &mLogger;

            std::shared_ptr<eevp::service::ServiceManagementSkeletonImpl> serviceManagementSkeletonImpl;
            std::shared_ptr<eevp::simulation::WiperSkeletonImpl> wiperSkeletonImpl;
            std::shared_ptr<eevp::simulation::WiperProxyImpl> wiperProxyImpl;
            void getWiperRecv();
            void getWiperSend();
            void setWiperSend(std::uint16_t &wipingInterval);
            void setWiperSend(const eevp::simulation::BCM_WipingLevel &wipingLevel);
        };

    } // namespace monitoring
} // namespace eevp

#endif // __SERVICE_CREATOR_H__