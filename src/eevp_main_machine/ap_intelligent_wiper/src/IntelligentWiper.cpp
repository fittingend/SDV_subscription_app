#include "IntelligentWiper.h"
#include "ara/exec/execution_client.h"
#include <ctime>
#include <ara/log/logger.h>
#include <cmath>
namespace eevp
{
    namespace simulation
    {

        std::atomic_bool IntelligentWiper::mRunning(false);

        class WiperListener : public eevp::simulation::IWiperListener
        {
        public:
            WiperListener(IntelligentWiper *app) : intelligentWiper(app) {}

            // void notify_wipingLevel(eevp::simulation::BCM_WipingLevel& value) {
            //     return intelligentWiper->notify_wipingLevel(value);
            // }
        private:
            IntelligentWiper *intelligentWiper;
        };

        class AccrPedalListener : public eevp::simulation::IAccrPedalListener
        {
        public:
            AccrPedalListener(IntelligentWiper *app) : intelligentWiper(app) {}

        private:
            IntelligentWiper *intelligentWiper;
        };

        class BrakePedalListener : public eevp::simulation::IBrakePedalListener
        {
        public:
            BrakePedalListener(IntelligentWiper *app) : intelligentWiper(app) {}

            // void notify_wipingLevel(eevp::simulation::BCM_WipingLevel& value) {
            //     return intelligentWiper->notify_wipingLevel(value);
            // }
        private:
            IntelligentWiper *intelligentWiper;
        };

        class GearListener : public eevp::simulation::IGearListener
        {
        public:
            GearListener(IntelligentWiper *app) : intelligentWiper(app) {}

        private:
            IntelligentWiper *intelligentWiper;
        };

        class VehSpdListener : public eevp::simulation::IVehSpdListener
        {
        public:
            VehSpdListener(IntelligentWiper *app) : intelligentWiper(app) {}

        private:
            IntelligentWiper *intelligentWiper;
        };

        IntelligentWiper::IntelligentWiper()
            : mLogger(ara::log::CreateLogger("INTW", "INTW", ara::log::LogLevel::kInfo)),
              wiperProxyImpl{nullptr},
              accrPedalProxyImpl{nullptr},
              brakePedalProxyImpl{nullptr},
              gearProxyImpl{nullptr},
              vehSpdProxyImpl{nullptr}
        {
            // Log the constructor function name for initialization tracking
            mLogger.LogInfo() << __func__;

            // Set up signal handling for graceful termination
            // std::signal(SIGINT, SignalHandler); // Uncomment if SIGINT handling is needed
            std::signal(SIGTERM, SignalHandler);
        }

        IntelligentWiper::~IntelligentWiper()
        {
            // Destructor implementation (empty for now)
        }

        void
        IntelligentWiper::SignalHandler(std::int32_t /*signal*/)
        {
            mRunning = false;
        }

        bool
        IntelligentWiper::Start()
        {
            mLogger.LogInfo() << __func__;

            mRunning = true;

            if (!setRunningState())
            {
                return false;
            }

            if (!startWiperProxy())
            {
                return false;
            }

            if (!startAccrPedalProxy())
            {
                return false;
            }

            if (!startBrakePedalProxy())
            {
                return false;
            }

            if (!startGearProxy())
            {
                return false;
            }

            if (!startVehSpdProxy())
            {
                return false;
            }

            return true;
        }

        void
        IntelligentWiper::Run()
        {
            mLogger.LogInfo() << __func__;
            while (mRunning)
            {
                // execServiceLogic();
                // get_wipingLevel(wipingLevel);
                // accrPedalProxyImpl->get_accrPedal();
                // brakePedalProxyImpl->get_BrakePosn();
                // brakePedalProxyImpl->get_BrakeSwitch();
                // gearProxyImpl->get_Gear();
                // vehSpdProxyImpl->get_VehSpd();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }

        void
        IntelligentWiper::Terminate()
        {
            mLogger.LogInfo() << __func__;
            mRunning = false;
        }

        bool
        IntelligentWiper::setRunningState()
        {
            ara::exec::ExecutionClient executionClient;
            auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
            if (exec.HasValue())
            {
                mLogger.LogInfo() << "Intelligent wiper app in Running State";
            }
            else
            {
                mLogger.LogError() << exec.Error().Message();
                return false;
            }
            return true;
        }

        void
        IntelligentWiper::get_wipingLevel(eevp::simulation::BCM_WipingLevel &wipinglevel)
        {
            wiperProxyImpl->get_wipingLevel(wipinglevel);
            mLogger.LogInfo() << "[get_wipingLevel]:" << static_cast<std::uint8_t>(wipinglevel);
        }

        // void
        // IntelligentWiper::getGearValue(std::uint8_t& gearValue)
        // {
        //     // gearProxyImpl->getGearValue(gearValue);
        //     mLogger.LogInfo() << "[getGearValue]:" << static_cast<std::uint8_t>(gearValue);
        // }

        // void IntelligentWiper::notify_wipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel)
        // {
        //     mLogger.LogInfo() << __func__;
        //     mLogger.LogInfo() << "wiping level: " << static_cast<std::uint8_t>(wipinglevel);
        // }

        bool IntelligentWiper::startWiperProxy()
        {
            mLogger.LogInfo() << __func__;

            wiperProxyImpl = std::make_shared<eevp::simulation::WiperProxyImpl>();
            auto wiperListener = std::make_shared<WiperListener>(this);
            wiperProxyImpl->setEventListener(wiperListener);
            wiperProxyImpl->init();
            return true;
        }

        bool IntelligentWiper::startAccrPedalProxy()
        {
            mLogger.LogInfo() << __func__;

            accrPedalProxyImpl = std::make_shared<eevp::simulation::AccrPedalProxyImpl>();
            auto accrListener = std::make_shared<AccrPedalListener>(this);
            accrPedalProxyImpl->setEventListener(accrListener);
            accrPedalProxyImpl->init();
            return true;
        }

        bool IntelligentWiper::startBrakePedalProxy()
        {
            mLogger.LogInfo() << __func__;

            brakePedalProxyImpl = std::make_shared<eevp::simulation::BrakePedalProxyImpl>();
            auto brakeListener = std::make_shared<BrakePedalListener>(this);
            brakePedalProxyImpl->setEventListener(brakeListener);
            brakePedalProxyImpl->init();
            return true;
        }

        bool IntelligentWiper::startGearProxy()
        {
            mLogger.LogInfo() << __func__;

            gearProxyImpl = std::make_shared<eevp::simulation::GearProxyImpl>();
            auto gearListener = std::make_shared<GearListener>(this);
            gearProxyImpl->setEventListener(gearListener);
            gearProxyImpl->init();
            return true;
        }

        bool IntelligentWiper::startVehSpdProxy()
        {
            mLogger.LogInfo() << __func__;

            vehSpdProxyImpl = std::make_shared<eevp::simulation::VehSpdProxyImpl>();
            auto vehSpdListener = std::make_shared<VehSpdListener>(this);
            vehSpdProxyImpl->setEventListener(vehSpdListener);
            vehSpdProxyImpl->init();
            return true;
        }

        void IntelligentWiper::execServiceLogic()
        {
            bool isIntentToDrive, isStopped;

            // 주행 의도 판단 알고리즘
            isIntentToDrive = checkDrivingIntention();

            // 주정차 상태 판단 알고리즘
            checkStopStatus(isStopped);

            if (isIntentToDrive == false && isStopped == true)
            {
                wiperProxyImpl->startWiping();
            }
            else
                wiperProxyImpl->stopWiping();

            // 주차 상황 판단 알고리즘
            checkParkingIntention();
        }

        void IntelligentWiper::checkParkingIntention()
        {
            double gearValue;
            double sonarValue;
            // getGearValue(gearValue);
            // getSonarValue(sonarValue);

            // if (sonarValue!= DETECTED && gearValue == PARK)
            // {
            //     wiperProxyImpl->stopWiping();
            // }
            // else
            // {
            //     wiperProxyImpl->startWiping();
            // }
        }

        void IntelligentWiper::notifyMFSWiperSpeedInterval(const double &wiperSpeed, const double &wiperInterval)
        {
            DynamicWiperAdjustment(wiperSpeed, wiperInterval);
        }

        // 차속 연동 와이퍼 제어 알고리즘
        // 운전자의 multifunction 스위치로 와이퍼가 수동 조작되었을때 호출되는 알고리즘
        void IntelligentWiper::DynamicWiperAdjustment(double new_wiperSpeed, double new_wiperInterval)
        {
            double vehVelocity;
            // getVehVelocity(vehVelocity);
            double refVehVelocity = vehVelocity;
            double refWiperSpeed = new_wiperSpeed;
            double refWiperInterval = new_wiperInterval;
            const int divider = 5;

            while (1)
            {
                // getVehVelocity(vehVelocity);

                double diff = vehVelocity - refVehVelocity;
                double diffDivided = diff / divider;
                int output_1;
                if (diffDivided < 0)
                {
                    output_1 = -1;
                }
                else if (diffDivided == 0)
                {
                    output_1 = 0;
                }
                else if (diffDivided > 0)
                {
                    output_1 = 1;
                }
                double output_2 = std::floor(fabs(diffDivided)) * 0.1;
                double output_3 = output_1 * output_2 + 1;
                // setWiperSpeed(std::round(output_3 * refWiperSpeed));
                // setWiperInterval(std::round(output_3 *refWiperInterval));

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(100)));
            }
        }

        bool IntelligentWiper::checkDrivingIntention()
        {
            // getGearValue(gearValue);
            // getBrakePedalValue(brakeValue);

            // if((gearValue == DRIVE || gearValue == MANUAL) && (brakeValue == 0 || brakeValue == 1))
            // {
            //     return true;
            // }
            // else
            // {
            //     return false;
            // }
            return true;
        }

        void IntelligentWiper::checkStopStatus(bool &isStopped)
        {
            // getGearValue(gearValue);
            // getVehVelocity(vehVelocity);

            // if (gearValue == P)// == P
            // {
            //     isStopped = true;
            //     //주차상태 TRUE
            // }
            // else if (vehVelocity < 1) // 속도가 1km/h 이내면 0 으로 가정
            // {
            //     isStopped = isVelocityZeroForDuration();
            // }
        }
        bool IntelligentWiper::isVelocityZeroForDuration()
        {

            const double duration = 3.0;      // seconds
            const double checkInterval = 0.5; // seconds between checks
            double timeZero = 0.0;

            while (timeZero < duration)
            {
                double vehVelocity;
                // getVehVelocity(vehVelocity);

                if (vehVelocity != 0)
                {
                    // If velocity is not zero, exit immediately
                    return false;
                }
                else
                {
                    // Accumulate time with velocity at zero
                    timeZero += checkInterval;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(checkInterval * 1000)));
            }

            return true; // `vehVelocity` was 0 for the full 3 seconds
        }

    } // namespace simulation
} // namespace eevp
