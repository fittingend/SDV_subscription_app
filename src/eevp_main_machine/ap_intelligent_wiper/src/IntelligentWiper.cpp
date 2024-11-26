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
        pthread_t IntelligentWiper::thread_commandwiping;

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
                std::this_thread::sleep_for(std::chrono::seconds(100));
                mLogger.LogInfo() << __func__;
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

            if (pthread_create(&thread_checkstop, nullptr, IntelligentWiper::commandWiping, this) != 0)
            {
                mLogger.LogInfo() << "commandwiping 스레드 생성 실패";
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
            if (!isWiping)
            {
                wipinglevel = BCM_WipingLevel::LOW;
                wiperProxyImpl->startWiping();
                isWiping = true;
            }
            return;
        }

        void IntelligentWiper::stopWiping()
        {

            std::unique_lock<std::mutex> lock(mtx);
            if (isWiping)
            {
                wipinglevel = BCM_WipingLevel::STOP;
                wipinginterval = 0U;
                wiperProxyImpl->stopWiping();
                isWiping = false;
            }
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
            instance->mLogger.LogInfo() << __func__;

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
            instance->mLogger.LogInfo() << __func__;

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
            instance->mLogger.LogInfo() << __func__;

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
            instance->mLogger.LogInfo() << __func__;

            while (mRunning)
            {
                std::unique_lock<std::mutex> lock(instance->mtx);
                instance->isParking = (instance->sonarDetect && (instance->gear.GearStatus == type::GearStatus::R));

                instance->cvparking.wait(lock, [instance]
                                         { return instance->isParking != (instance->sonarDetect && (instance->gear.GearStatus == type::GearStatus::R)); });
            }
            return nullptr;
        }

        void *IntelligentWiper::commandWiping(void *inst)
        {
            IntelligentWiper *instance = static_cast<IntelligentWiper *>(inst);
            instance->mLogger.LogInfo() << __func__;

            while (mRunning)
            {
                std::unique_lock<std::mutex> lock(instance->mtx);
                instance->shouldStartWiping = (!instance->isIntentToDrive && instance->isStopped) || !instance->isParking;

                if (instance->shouldStartWiping)
                    instance->startWiping();
                else
                    instance->stopWiping();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            return nullptr;
        }

        // 사용자가 수동 조작 시 호출
        void IntelligentWiper::DynamicWiperAdjustment()
        {
            BCM_WipingLevel ref_wipingLevel = wipinglevel;
            std::uint16_t ref_wipingInterval = wipinginterval;
            type::VCS_VehSpd ref_vehspd = vehspd;
            std::uint16_t threshold;
            while (mRunning)
            {
                std::unique_lock<std::mutex> lock(mtx);
                std::double_t diff = vehspd.absoluteValue - ref_vehspd.absoluteValue; // 기준 속도가 80이하 일때는 20km/h마다, 80이상 일때는 25km/h마다 와이퍼 속도변경
                std::double_t diffDivided = diff / 5;

                if (ref_vehspd.absoluteValue < 80)
                    threshold = 20;
                else
                    threshold = 25;

                // set_wipingLevel threshold에 따라 diff에 맞춰 wipinglevel 조절
                if (std::fabs(diff) >= threshold) // threshold 이상 변화 시
                {
                    if (diff > 0 && wipinglevel < BCM_WipingLevel::HIGH)
                    {
                        wipinglevel = static_cast<BCM_WipingLevel>(static_cast<int>(wipinglevel) + 1); // 단계 증가
                    }
                    else if (diff < 0 && wipinglevel > BCM_WipingLevel::LOW)
                    {
                        wipinglevel = static_cast<BCM_WipingLevel>(static_cast<int>(wipinglevel) - 1); // 단계 감소
                    }

                    // 기준 속도 업데이트
                    ref_vehspd = vehspd;
                }
                set_wipingLevel(wipinglevel);

                std::int8_t output_1;
                output_1 = (diffDivided > 0) ? 1 : ((diffDivided == 0) ? 0 : -1);
                std::double_t output_2 = std::floor(std::fabs(diffDivided)) * 0.1;
                std::double_t output_3 = output_1 * output_2 + 1;
                set_wipingInterval(std::round(ref_wipingInterval / output_3));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    } // namespace simulation
} // namespace eevp
