#ifndef __INTELLIGENT_WIPER_H__
#define __INTELLIGENT_WIPER_H__

#include <csignal>
#include <thread>
#include <atomic>
#include <ara/log/logger.h>

#include "proxy/WiperProxyImpl.h"
#include "proxy/AccrPedalProxyImpl.h"
#include "proxy/BrakePedalProxyImpl.h"
#include "proxy/GearProxyImpl.h"
#include "proxy/VehSpdProxyImpl.h"

namespace eevp
{
    namespace simulation
    {

        class IntelligentWiper
        {
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
            // void notify_wipingLevel(eevp::simulation::BCM_WipingLevel &wipinglevel);
            void get_wipingLevel(eevp::simulation::BCM_WipingLevel &wipinglevel);
            void execServiceLogic();

        private:
            /// @brief Signal Handler
            static void SignalHandler(std::int32_t signal);

            /// @brief Set Running State
            bool setRunningState();

            /// Start Proxy
            bool startWiperProxy();

            bool startAccrPedalProxy();

            bool startBrakePedalProxy();

            bool startGearProxy();

            bool startVehSpdProxy();

            /// @brief Check Driving Intention
            bool checkDrivingIntention();

            /// @brief Check Stop Status
            void checkStopStatus(bool &isParked, bool &isStopped);

            /// @brief Check if velocity is zero for a duration
            bool isVelocityZeroForDuration();

            /// @brief Check Parking Intention
            void checkParkingIntention();

            /// @brief Dynamic Wiper Adjustment based on velocity
            void DynamicWiperAdjustment(double new_wiperSpeed, double new_wiperInterval);

            /// @brief Retrieve gear value
            void getGearValue(std::uint8_t &gearValue);

            /// @brief Retrieve sonar value
            void getSonarValue(double &sonarValue);

            /// @brief Retrieve vehicle velocity
            void getVehVelocity(double &vehVelocity);

            /// @brief Retrieve brake pedal value
            void getBrakePedalValue(double &brakeValue);

            /// @brief Set wiper speed
            void setWiperSpeed(double wiperSpeed);

            /// @brief Set wiper interval
            void setWiperInterval(double wiperInterval);

            void notifyMFSWiperSpeedInterval(const double &wiperSpeed, const double &wiperInterval);

            /// @brief Flag of Running
            static std::atomic_bool mRunning;

            /// @brief Logger
            ara::log::Logger &mLogger;

            /// WiperVar
            eevp::simulation::BCM_WipingLevel wipingLevel;
            std::uint16_t wipingInterval;

            /// AccrPedalVar
            eevp::simulation::VCS_AccrPedal vcs_AccrPedal;

            /// @brief Proxy Implementation
            std::shared_ptr<eevp::simulation::WiperProxyImpl> wiperProxyImpl;
            std::shared_ptr<eevp::simulation::BrakePedalProxyImpl> brakePedalProxyImpl;
            std::shared_ptr<eevp::simulation::GearProxyImpl> gearProxyImpl;
            std::shared_ptr<eevp::simulation::VehSpdProxyImpl> vehSpdProxyImpl;
            std::shared_ptr<eevp::simulation::AccrPedalProxyImpl> accrPedalProxyImpl;
        };

    } // namespace simulation
} // namespace eevp

#endif // __INTELLIGENT_WIPER_H__
