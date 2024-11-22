#ifndef __INTELLIGENT_WIPER_H__
#define __INTELLIGENT_WIPER_H__

#include <csignal>
#include <thread>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <ara/log/logger.h>

#include "proxy/WiperProxyImpl.h"
#include "proxy/AccrPedalProxyImpl.h"
#include "proxy/BrakePedalProxyImpl.h"
#include "proxy/GearProxyImpl.h"
#include "proxy/VehSpdProxyImpl.h"
#include "proxy/SnsrUssProxyImpl.h"

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

            bool startSnsrUSSProxy();

            // Wiper
            void get_wipingLevel();
            void get_wipingInterval();
            void set_wipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel);
            void set_wipingInterval(const std::uint16_t &wipingInterval);
            void startWiping();
            void stopWiping();

            // WiperVar
            eevp::simulation::BCM_WipingLevel wipinglevel;
            std::uint16_t wipinginterval;

            // AccrPedal
            void get_accrPedal();

            // AccrPedalVar
            eevp::simulation::type::VCS_AccrPedal accrpedal;

            // BrakePedal
            void get_BrakePosn();
            void get_BrakeSwitch();

            // BrakePedalVar
            eevp::simulation::type::VCS_BrakePosn brakeposn;
            eevp::simulation::type::VCS_BrakeSwitch brakeswitch;

            // Gear
            void get_Gear();
            void set_Gear(const eevp::simulation::type::VCS_Gear &vcs_gear);

            // GearVar
            eevp::simulation::type::VCS_Gear gear;

            // VehSpd
            void get_VehSpd();

            // VehSpdVar
            eevp::simulation::type::VCS_VehSpd vehspd;

            // Sonar
            void get_Sonar();
            void isDetect();

            // SonarVar
            eevp::simulation::type::USSSonarInfo sonarinfo;
            bool sonarDetect = false;

            // Logic
            bool startLogicThread();
            static pthread_t thread_checkdriving;
            static pthread_t thread_checkstop;
            static pthread_t thread_checkparking;
            static pthread_t thread_getvalue;
            static void *checkDrivingIntention(void *inst);
            static void *checkStopStatus(void *inst);
            static void *checkParkingIntention(void *inst);
            static void *startGetValue(void *inst);

            // LogicVar
            bool isIntentToDrive = false;
            bool isStopped = true;
            bool isParking = true;
            bool isgearP = false;

            /// @brief Check if velocity is zero for a duration
            bool isVelocityZeroForDuration();

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

            // mutex and condition_variable
            std::mutex mtx;
            std::condition_variable cvdriving;
            std::condition_variable cvstop;
            std::condition_variable cvparking;

            /// @brief Proxy Implementation
            std::shared_ptr<eevp::simulation::WiperProxyImpl> wiperProxyImpl;
            std::shared_ptr<eevp::simulation::BrakePedalProxyImpl> brakePedalProxyImpl;
            std::shared_ptr<eevp::simulation::GearProxyImpl> gearProxyImpl;
            std::shared_ptr<eevp::simulation::VehSpdProxyImpl> vehSpdProxyImpl;
            std::shared_ptr<eevp::simulation::AccrPedalProxyImpl> accrPedalProxyImpl;
            std::shared_ptr<eevp::simulation::SnsrUssProxyImpl> snsrUssProxyImpl;
        };

    } // namespace simulation
} // namespace eevp

#endif // __INTELLIGENT_WIPER_H__
