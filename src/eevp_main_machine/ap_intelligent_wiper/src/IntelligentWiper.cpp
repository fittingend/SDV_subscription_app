#include "IntelligentWiper.h"
#include "ara/exec/execution_client.h"
#include <ctime>
#include <ara/log/logger.h>
#include <cmath>
namespace eevp
{
    namespace simulation
    {
        pthread_t IntelligentWiper::thread_checkdriving;
        pthread_t IntelligentWiper::thread_checkstop;
        pthread_t IntelligentWiper::thread_checkparking;
        pthread_t IntelligentWiper::thread_getvalue;

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

        class SnsrUSSListener : public eevp::simulation::ISnsrUssListener
        {
        public:
            SnsrUSSListener(IntelligentWiper *app) : intelligentWiper(app) {}

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

            if (!startSnsrUSSProxy())
            {
                return false;
            }

            if (!startLogicThread())
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

        bool IntelligentWiper::startLogicThread()
        {
            mLogger.LogInfo() << __func__;

            if (pthread_create(&thread_getvalue, nullptr, IntelligentWiper::startGetValue, this) != 0)
            {
                mLogger.LogInfo() << "startGetValue 스레드 생성 실패";
                return false;
            }

            if (pthread_create(&thread_checkdriving, nullptr, IntelligentWiper::checkDrivingIntention, this) != 0)
            {
                mLogger.LogInfo() << "checkdriving 스레드 생성 실패";
                return false;
            }

            if (pthread_create(&thread_checkparking, nullptr, IntelligentWiper::checkParkingIntention, this) != 0)
            {
                mLogger.LogInfo() << "checkparking 스레드 생성 실패";
                return false;
            }

            if (pthread_create(&thread_checkstop, nullptr, IntelligentWiper::checkStopStatus, this) != 0)
            {
                mLogger.LogInfo() << "checkstop 스레드 생성 실패";
                return false;
            }
            return true;
        }

        // Wiper

        void IntelligentWiper::get_wipingLevel()
        {
            std::unique_lock<std::mutex> lock(mtx);
            wipinglevel = wiperProxyImpl->get_wipingLevel();
            return;
        }

        void IntelligentWiper::get_wipingInterval()
        {
            std::unique_lock<std::mutex> lock(mtx);
            wipinginterval = wiperProxyImpl->get_wipingInterval();
            return;
        }

        void IntelligentWiper::set_wipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            std::unique_lock<std::mutex> lock(mtx);
            wipinglevel = wipingLevel;
            wiperProxyImpl->setWipingLevel(wipingLevel);
            return;
        }

        void IntelligentWiper::set_wipingInterval(const std::uint16_t &wipingInterval)
        {
            std::unique_lock<std::mutex> lock(mtx);
            wipinginterval = wipingInterval;
            wiperProxyImpl->setWipingInterval(wipingInterval);
            return;
        }

        void IntelligentWiper::startWiping()
        {
            std::unique_lock<std::mutex> lock(mtx);
            wipinglevel = BCM_WipingLevel::LOW;
            wiperProxyImpl->startWiping();
            return;
        }

        void IntelligentWiper::stopWiping()
        {

            std::unique_lock<std::mutex> lock(mtx);
            wipinglevel = BCM_WipingLevel::STOP;
            wipinginterval = 0U;
            wiperProxyImpl->stopWiping();
            return;
        }

        // AccrPedal

        void IntelligentWiper::get_accrPedal()
        {
            std::unique_lock<std::mutex> lock(mtx);
            accrpedal = accrPedalProxyImpl->get_accrPedal();
            return;
        }

        // BrakePedal

        void IntelligentWiper::get_BrakePosn()
        {
            std::unique_lock<std::mutex> lock(mtx);
            brakeposn = brakePedalProxyImpl->get_BrakePosn();
            return;
        }

        void IntelligentWiper::get_BrakeSwitch()
        {
            std::unique_lock<std::mutex> lock(mtx);
            brakeswitch = brakePedalProxyImpl->get_BrakeSwitch();
            return;
        }

        // Gear

        void IntelligentWiper::get_Gear()
        {
            std::unique_lock<std::mutex> lock(mtx);

            gear = gearProxyImpl->get_Gear();
            cvdriving.notify_one();
            cvparking.notify_one();
            return;
        }

        void IntelligentWiper::set_Gear(const eevp::simulation::type::VCS_Gear &vcs_gear)
        {
            std::unique_lock<std::mutex> lock(mtx);
            this->gear = vcs_gear;
            return gearProxyImpl->set_Gear(vcs_gear);
        }

        // VehSpd

        void IntelligentWiper::get_VehSpd()
        {
            std::unique_lock<std::mutex> lock(mtx);
            vehspd = vehSpdProxyImpl->get_VehSpd();
            return;
        }

        // Sonar

        void IntelligentWiper::get_Sonar()
        {
            std::unique_lock<std::mutex> lock(mtx);
            sonarinfo = snsrUssProxyImpl->get_Sonar();
            return;
        }

        void IntelligentWiper::isDetect()
        {
            std::unique_lock<std::mutex> lock(mtx);
            sonarDetect = snsrUssProxyImpl->isDetect();
            cvparking.notify_one();
            return;
        }

        // Proxy

        bool IntelligentWiper::startWiperProxy()
        {
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

        bool IntelligentWiper::startSnsrUSSProxy()
        {
            mLogger.LogInfo() << __func__;

            snsrUssProxyImpl = std::make_shared<eevp::simulation::SnsrUssProxyImpl>();
            auto snsrUssListener = std::make_shared<SnsrUSSListener>(this);
            snsrUssProxyImpl->setEventListener(snsrUssListener);
            snsrUssProxyImpl->init();
            return true;
        }

        void *IntelligentWiper::startGetValue(void *inst)
        {
            IntelligentWiper *instance = static_cast<IntelligentWiper *>(inst);
            while (true)
            {
                instance->get_Gear();
                instance->get_BrakePosn();
                instance->get_accrPedal();
                instance->get_VehSpd();
                instance->isDetect();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            return nullptr;
        }

        void *IntelligentWiper::checkDrivingIntention(void *inst)
        {
            IntelligentWiper *instance = static_cast<IntelligentWiper *>(inst);
            while (mRunning)
            {
                std::unique_lock<std::mutex> lock(instance->mtx);

                instance->isIntentToDrive = (instance->gear.GearStatus == type::GearStatus::D);

                instance->cvdriving.wait(lock, [instance]
                                         { return (instance->gear.GearStatus == type::GearStatus::D) != instance->isIntentToDrive; });
            }
            return nullptr;
        }

        void *IntelligentWiper::checkStopStatus(void *inst)
        {
            IntelligentWiper *instance = static_cast<IntelligentWiper *>(inst);
            while (mRunning)
            {
                if (instance->gear.GearStatus == type::GearStatus::P)
                    instance->isStopped = true;
                else
                {
                    if (instance->vehspd.absoluteValue == 0 || instance->vehspd.actualValue == 0)
                    {
                        auto start_time = std::chrono::steady_clock::now();
                        while (instance->vehspd.absoluteValue == 0 || instance->vehspd.actualValue == 0)
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));

                            auto elapsed_time = std::chrono::steady_clock::now() - start_time;
                            if (std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count() >= 3)
                            {
                                instance->isStopped = true;
                                break;
                            }
                        }

                        if (instance->vehspd.absoluteValue != 0 || instance->vehspd.actualValue != 0)
                        {
                            instance->isStopped = false;
                            continue;
                        }
                    }
                    else
                        instance->isStopped = false;
                }
            }
            return nullptr;
        }

        void *IntelligentWiper::checkParkingIntention(void *inst)
        {
            IntelligentWiper *instance = static_cast<IntelligentWiper *>(inst);
            while (mRunning)
            {
                std::unique_lock<std::mutex> lock(instance->mtx);
                instance->isParking = (instance->sonarDetect && (instance->gear.GearStatus == type::GearStatus::P));

                instance->cvparking.wait(lock, [instance]
                                         { return instance->isParking != (instance->sonarDetect && (instance->gear.GearStatus == type::GearStatus::P)); });
            }
            return nullptr;
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
