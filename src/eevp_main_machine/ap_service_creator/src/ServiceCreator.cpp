#include "ara/exec/execution_client.h"
#include "ServiceCreator.h"
#include "ara/log/logger.h"

namespace eevp
{
    namespace simulation
    {
        eevp::service::type::wiperRecv ServiceCreator::wiperRecv = {eevp::simulation::BCM_WipingLevel::STOP, 99};
        eevp::service::type::wiperSend ServiceCreator::wiperSend = {eevp::simulation::BCM_WipingLevel::LOW, 1};
        pthread_t ServiceCreator::thread_socket_recv;
        pthread_t ServiceCreator::thread_socket_send;
        std::string ServiceCreator::wiperLevel[] = {"LOW", "MEDIUM", "HIGH", "STOP"};

        std::atomic_bool ServiceCreator::mRunning(false);

        // Unused
        class ServiceManagementListener : public eevp::service::IServiceManagementListener
        {
        public:
            ServiceManagementListener(ServiceCreator *svc) : serviceCreator(svc) {}

            bool isWiping() { return serviceCreator->isWiping(); }
            std::uint16_t getWipingInterval() { return serviceCreator->getWipingInterval(); }
            eevp::simulation::BCM_WipingLevel getWipingLevel() { return serviceCreator->getWipingLevel(); }
            eevp::simulation::BCM_ReturnCode stopWiping() { return serviceCreator->stopWiping(); }
            eevp::simulation::BCM_ReturnCode startWiping() { return serviceCreator->startWiping(); }
            eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevelImme(wipingLevel); }
            eevp::simulation::BCM_ReturnCode setWipingInterval(const std::uint16_t &wipingInterval) { return serviceCreator->setWipingInterval(wipingInterval); }
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel(wipingLevel); }

        private:
            ServiceCreator *serviceCreator;
        };

        // WiperListener
        class WiperListener : public eevp::simulation::IWiperListener
        {
        public:
            WiperListener(ServiceCreator *svc) : serviceCreator(svc) {}

            bool isWiping() { return serviceCreator->isWiping(); }
            std::uint16_t getWipingInterval() { return serviceCreator->getWipingInterval(); }
            eevp::simulation::BCM_WipingLevel getWipingLevel() { return serviceCreator->getWipingLevel(); }
            eevp::simulation::BCM_ReturnCode stopWiping() { return serviceCreator->stopWiping(); }
            eevp::simulation::BCM_ReturnCode startWiping() { return serviceCreator->startWiping(); }
            eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevelImme(wipingLevel); }
            eevp::simulation::BCM_ReturnCode setWipingInterval(const std::uint16_t &wipingInterval) { return serviceCreator->setWipingInterval(wipingInterval); }
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel(wipingLevel); }

        private:
            ServiceCreator *serviceCreator;
        };

        // TMoodLampListener
        class TMoodLampListener : public eevp::simulation::ITMoodLampListener
        {
        public:
            TMoodLampListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void RequestMImSetBrightness(const std::uint16_t &Brightness) { return serviceCreator->RequestMImSetBrightness(Brightness); }
            void RequestMImSetMode(const lmp::mode::SoaMImMoodeMode &mood) { return serviceCreator->RequestMImSetMode(mood); }
            void RequestMImSetRGBColor(const std::uint8_t &ColorIndex) { return serviceCreator->RequestMImSetRGBColor(ColorIndex); }

        private:
            ServiceCreator *serviceCreator;
        };

        // MsgInfoListener
        class MsgInfoListener : public eevp::simulation::IMsgInfoListener
        {
        public:
            MsgInfoListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyMsgInfo(const bms::output::OutputData &output) { return serviceCreator->notifyMsgInfo(output); }

        private:
            ServiceCreator *serviceCreator;
        };

        // AccrPedalListener
        class AccrPedalListener : public eevp::simulation::IAccrPedalListener
        {
        public:
            AccrPedalListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyAccrPedal(eevp::simulation::type::VCS_AccrPedal &accrPedal) { return serviceCreator->notifyAccrPedal(accrPedal); }

        private:
            ServiceCreator *serviceCreator;
        };

        // EnvMonitorListener
        class EnvMonitorListener : public eevp::simulation::IEnvMonitorListener
        {
        public:
            EnvMonitorListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyHumidity(eevp::simulation::type::TMS_EnvZoneHumidityAry &envZoneHumidityAry) { return serviceCreator->notifyHumidity(envZoneHumidityAry); }

        private:
            ServiceCreator *serviceCreator;
        };

        // GearListener
        class GearListener : public eevp::simulation::IGearListener
        {
        public:
            GearListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyGear(eevp::simulation::type::VCS_Gear &gear) { return serviceCreator->notifyGear(gear); }

        private:
            ServiceCreator *serviceCreator;
        };

        // BrakePedalListener
        class BrakePedalListener : public eevp::simulation::IBrakePedalListener
        {
        public:
            BrakePedalListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyPosn(eevp::simulation::type::VCS_BrakePosn &brakePosn) { return serviceCreator->notifyPosn(brakePosn); }
            void notifyBrakeSwitch(eevp::simulation::type::VCS_BrakeSwitch &brakeSwitch) { return serviceCreator->notifyBrakeSwitch(brakeSwitch); }

        private:
            ServiceCreator *serviceCreator;
        };

        // VehSpdListener
        class VehSpdListener : public eevp::simulation::IVehSpdListener
        {
        public:
            VehSpdListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void notifyVehSpd(eevp::simulation::type::VCS_VehSpd &vehSpd) { return serviceCreator->notifyVehSpd(vehSpd); }

        private:
            ServiceCreator *serviceCreator;
        };

        // SnsrUssListener
        class SnsrUssListener : public eevp::simulation::ISnsrUssListener
        {
        public:
            SnsrUssListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void ntfSonarInfo(eevp::simulation::type::USSSonarInfo &ussSonarInfo) { return serviceCreator->ntfSonarInfo(ussSonarInfo); }

        private:
            ServiceCreator *serviceCreator;
        };

        // LotteListener
        class LotteListener : public eevp::simulation::ILotteListener
        {
        public:
            LotteListener(ServiceCreator *svc) : serviceCreator(svc) {}

            void NotifyDmsCurr(lotte::type::DmsGzDtctn &dmsGzDtctn) { return serviceCreator->NotifyDmsCurr(dmsGzDtctn); }
            void NotifyDmsStatus(bool &result) { return serviceCreator->NotifyDmsStatus(result); }
            void NotifySmartFilmCurr(lotte::type::SideTransparency &result) { return serviceCreator->NotifySmartFilmCurr(result); }
            void NotifySmartFilmStatus(bool &result) { return serviceCreator->NotifySmartFilmStatus(result); }
            void SmartFilmControl(const std::int32_t &windowLoc, const std::int32_t &transparence) { return serviceCreator->SmartFilmControl(windowLoc, transparence); }

        private:
            ServiceCreator *serviceCreator;
        };

        ServiceCreator::ServiceCreator() : mLogger(ara::log::CreateLogger("SVCC", "SVCC", ara::log::LogLevel::kInfo)),
                                           serviceManagementSkeletonImpl{nullptr}
        {
            mLogger.LogInfo() << __func__;
            std::signal(SIGTERM, SignalHandler);
            this->uThreadRunning = false;
        }

        ServiceCreator::~ServiceCreator()
        {
            this->uThreadRunning = false;
        }

        void

        ServiceCreator::SignalHandler(std::int32_t /*signal*/)
        {
            mRunning = false;
        }

        bool
        ServiceCreator::Start()
        {
            mLogger.LogInfo() << __func__;
            mRunning = true;
            this->uThreadRunning = true;
            this->updateThread = new std::thread(std::bind(&ServiceCreator::poolingFieldUpdate, this));

            if (!setRunningState())
            {
                return false;
            }

            if (!initialize())
            {
                return false;
            }

            if (!startServiceCreatorStub())
            {
                return false;
            }

            if (!startMsgInfoProxy())
            {
                return false;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if (!startSocketClient())
            {
                return false;
            }

            return true;
        }

        void
        ServiceCreator::Run()
        {
            mLogger.LogInfo() << __func__;
            while (mRunning)
            {
                std::this_thread::sleep_for(std::chrono::seconds(100));
                mLogger.LogInfo() << "Service Creator running";
            }
        }

        void
        ServiceCreator::Terminate()
        {
            mLogger.LogInfo() << __func__;
            mRunning = false;
        }

        void ServiceCreator::poolingFieldUpdate()
        {
            mLogger.LogInfo() << __func__;
            if (this->uThreadRunning)
            {
                int dummy_msg;
            }
            return;
        }

        // Wiper Start
        bool ServiceCreator::isWiping()
        {
            mLogger.LogInfo() << __func__;
            return true;
        }

        eevp::simulation::BCM_ReturnCode
        ServiceCreator::stopWiping()
        {
            mLogger.LogInfo() << __func__;
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode
        ServiceCreator::startWiping()
        {
            mLogger.LogInfo() << __func__;
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode
        ServiceCreator::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            // mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingLevel(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode
        ServiceCreator::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingLevel(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode
        ServiceCreator::setWipingInterval(const std::uint16_t &wipingInterval)
        {
            // mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingInterval(wipingInterval);
            return BCM_ReturnCode::SUCCESS;
        }

        std::uint16_t
        ServiceCreator::getWipingInterval()
        {
            mLogger.LogInfo() << __func__;
            return 0;
        }

        eevp::simulation::BCM_WipingLevel
        ServiceCreator::getWipingLevel()
        {
            mLogger.LogInfo() << __func__;
            return wiperRecv.wipingLevel;
        }

        void
        ServiceCreator::getWiperRecv()
        {
            switch (ServiceCreator::wiperRecv.wipingLevel)
            {
            case BCM_WipingLevel::HIGH:
                mLogger.LogInfo() << "wiperRecv: [HIGH, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                break;
            case BCM_WipingLevel::LOW:
                mLogger.LogInfo() << "wiperRecv: [LOW, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                break;
            case BCM_WipingLevel::MEDIUM:
                mLogger.LogInfo() << "wiperRecv: [MEDIUM, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                break;
            case BCM_WipingLevel::STOP:
                mLogger.LogInfo() << "wiperRecv: [STOP, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                break;
            default:
                break;
            }
        }
        void
        ServiceCreator::getWiperSend()
        {
            switch (ServiceCreator::wiperSend.wipingLevel)
            {
            case BCM_WipingLevel::HIGH:
                mLogger.LogInfo() << "wiperSend: [HIGH, " << ServiceCreator::wiperSend.wipingInterval << "]";
                break;
            case BCM_WipingLevel::LOW:
                mLogger.LogInfo() << "wiperSend: [LOW, " << ServiceCreator::wiperSend.wipingInterval << "]";
                break;
            case BCM_WipingLevel::MEDIUM:
                mLogger.LogInfo() << "wiperSend: [MEDIUM, " << ServiceCreator::wiperSend.wipingInterval << "]";
                break;
            case BCM_WipingLevel::STOP:
                mLogger.LogInfo() << "wiperSend: [STOP, " << ServiceCreator::wiperSend.wipingInterval << "]";
                break;
            default:
                break;
            }
        }

        void
        ServiceCreator::setWiperSend(std::uint16_t &wipingInterval)
        {
            ServiceCreator::wiperSend.wipingInterval = wipingInterval;
        }

        void
        ServiceCreator::setWiperSend(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            ServiceCreator::wiperSend.wipingLevel = wipingLevel;
        }

        // Wiper End

        // TMoodLamp Start

        void
        ServiceCreator::RequestMImSetBrightness(const std::uint16_t &Brightness)
        {
            mLogger.LogInfo() << __func__;
            this->BrightnessSend = Brightness;
            return;
        }
        void
        ServiceCreator::RequestMImSetMode(const lmp::mode::SoaMImMoodeMode &mood)
        {
            mLogger.LogInfo() << __func__;
            this->moodSend = mood;
            return;
        }
        void
        ServiceCreator::RequestMImSetRGBColor(const std::uint8_t &ColorIndex)
        {
            mLogger.LogInfo() << __func__;
            this->ColorIndexSend = ColorIndex;
            return;
        }

        // TMoodLamp End

        // BmsInfoSrv Start

        void
        ServiceCreator::notifyBmsInfo(bms::input::InputData &info)
        {
            mLogger.LogInfo() << __func__;
            bmsInfoSkeletonImpl->sendEventBmsInfo(info);
            return;
        }

        // BmsInfoSrv End

        // MsgInfoSrv Start

        void
        ServiceCreator::notifyMsgInfo(const bms::output::OutputData &output)
        {
            mLogger.LogInfo() << __func__;
            std::string filePath = "/home/popcornsar/src/eevp_main_machine/ap_service_creator/build/msg.bin";
            std::string ftpUrlBin = "ftp://yourftpserver.com/path/to/upload/msg.bin";
            std::string ftpUrlPre = "ftp://yourftpserver.com/path/to/upload/msg.pre";
            // FTP 전송용 파일 만들기
            // 1. "msg.bin" 파일을 생성하고 데이터 기록
            std::ofstream binFile(filePath, std::ios::binary);
            if (!binFile)
            {
                mLogger.LogError() << "Failed to create msg.bin";
                return;
            }
            // InterfaceIDforDbg(4bytes) 제외하고 나머지 데이터의 크기를 계산
            size_t outputSize = sizeof(OutputData) - sizeof(output.InterfaceIDforDbg);

            // OutputData에서 InterfaceIDforDbg를 제외한 나머지 데이터를 메모리에 복사
            binFile.write(reinterpret_cast<const char *>(&output) + sizeof(output.InterfaceIDforDbg), outputSize);
            if (binFile.fail())
            {
                mLogger.LogInfo() << "파일 쓰기 실패";
            }
            else
            {
                mLogger.LogInfo() << "파일에 데이터가 성공적으로 기록되었습니다";
            }
            binFile.close();

            // // 2. FTP 서버에서 기존 "msg.pre" 파일을 삭제
            // CURL *curl = curl_easy_init();
            // if (curl)
            // {
            //     curl_easy_setopt(curl, CURLOPT_URL, ftpUrlPre.c_str());
            //     curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELE"); // FTP DELETE 명령 설정

            //     CURLcode res = curl_easy_perform(curl);
            //     if (res != CURLE_OK)
            //     {
            //         mLogger.LogWarn() << "Failed to delete msg.pre on FTP: " << curl_easy_strerror(res);
            //     }
            //     else
            //     {
            //         mLogger.LogInfo() << "Existing msg.pre file deleted from FTP.";
            //     }
            //     curl_easy_cleanup(curl);
            // }

            // // 3. "msg.bin" 파일을 FTP 서버로 업로드
            // curl = curl_easy_init();
            // if (curl)
            // {
            //     FILE *file = fopen(filePath.c_str(), "rb");
            //     if (!file)
            //     {
            //         mLogger.LogError() << "Failed to open local file";
            //         return;
            //     }

            //     curl_easy_setopt(curl, CURLOPT_URL, ftpUrlBin.c_str());
            //     curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
            //     curl_easy_setopt(curl, CURLOPT_READDATA, file);

            //     CURLcode res = curl_easy_perform(curl);
            //     if (res != CURLE_OK)
            //     {
            //         mLogger.LogError() << "FTP upload failed: " << curl_easy_strerror(res);
            //         fclose(file);
            //         curl_easy_cleanup(curl);
            //         return;
            //     }

            //     mLogger.LogInfo() << "File uploaded successfully to FTP: msg.bin";
            //     fclose(file);
            //     curl_easy_cleanup(curl);
            // }

            // // 4. 업로드 완료 후 FTP 서버에서 "msg.bin" 파일을 "msg.pre"로 이름 변경
            // curl = curl_easy_init();
            // if (curl)
            // {
            //     std::string renameCommand = "RNFR msg.bin";
            //     std::string renameToCommand = "RNTO msg.pre";

            //     curl_easy_setopt(curl, CURLOPT_URL, ftpUrlBin.c_str());
            //     curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, renameCommand.c_str());

            //     CURLcode res = curl_easy_perform(curl);
            //     if (res != CURLE_OK)
            //     {
            //         mLogger.LogError() << "Failed to rename msg.bin to msg.pre on FTP: " << curl_easy_strerror(res);
            //     }
            //     else
            //     {
            //         curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, renameToCommand.c_str());
            //         res = curl_easy_perform(curl);
            //         if (res != CURLE_OK)
            //         {
            //             mLogger.LogError() << "Failed to complete renaming to msg.pre: " << curl_easy_strerror(res);
            //         }
            //         else
            //         {
            //             mLogger.LogInfo() << "msg.bin successfully renamed to msg.pre on FTP.";
            //         }
            //     }
            //     curl_easy_cleanup(curl);
            // }

            return;
        }

        // MsgInfoSrv End

        // AccrPedal Start

        void
        ServiceCreator::notifyAccrPedal(eevp::simulation::type::VCS_AccrPedal &accrPedal)
        {
            mLogger.LogInfo() << __func__;
            accrPedal = this->accrPedal;
            return;
        }

        // AccrPedal End

        // EnvMonitor Start

        void
        ServiceCreator::notifyHumidity(eevp::simulation::type::TMS_EnvZoneHumidityAry &envZoneHumidityAry)
        {
            mLogger.LogInfo() << __func__;
            envZoneHumidityAry = this->envZoneHumidityAry;
            return;
        }

        // EnvMonitor End

        // Gear Start

        void
        ServiceCreator::notifyGear(eevp::simulation::type::VCS_Gear &gear)
        {
            mLogger.LogInfo() << __func__;
            gear = this->gear;
            return;
        }

        // Gear End

        // BrakePedal Start

        void
        ServiceCreator::notifyPosn(eevp::simulation::type::VCS_BrakePosn &brakePosn)
        {
            mLogger.LogInfo() << __func__;
            brakePosn = this->brakePosn;
            return;
        }

        void
        ServiceCreator::notifyBrakeSwitch(eevp::simulation::type::VCS_BrakeSwitch &brakeSwitch)
        {
            mLogger.LogInfo() << __func__;
            brakeSwitch = this->brakeSwitch;
            return;
        }

        // BrakePedal End

        // VehSpd Start

        void
        ServiceCreator::notifyVehSpd(eevp::simulation::type::VCS_VehSpd &vehSpd)
        {
            mLogger.LogInfo() << __func__;
            vehSpd = this->vehSpd;
            return;
        }

        // VehSpd End

        // SnsrUss Start

        void
        ServiceCreator::ntfSonarInfo(eevp::simulation::type::USSSonarInfo &ussSonarInfo)
        {
            mLogger.LogInfo() << __func__;
            ussSonarInfo = this->ussSonarInfo;
            return;
        }

        // SnsrUss End

        // Lotte Start

        void ServiceCreator::NotifyDmsCurr(lotte::type::DmsGzDtctn &dmsGzDtctn)
        {
            mLogger.LogInfo() << __func__;
            return;
        }

        void ServiceCreator::NotifyDmsStatus(bool &result)
        {
            // mLogger.LogInfo() << __func__;
            result = this->dmsStatus;
            return;
        }

        void ServiceCreator::NotifySmartFilmCurr(lotte::type::SideTransparency &result)
        {
            // mLogger.LogInfo() << __func__;
            return;
        }

        void ServiceCreator::NotifySmartFilmStatus(bool &result)
        {
            // mLogger.LogInfo() << __func__;
            result = this->smartFilmStatus;
            return;
        }

        void ServiceCreator::SmartFilmControl(const std::int32_t &windowLoc, const std::int32_t &transparence)
        {
            // mLogger.LogInfo() << __func__;
            this->windowLocSend = windowLoc;
            this->transparenceSend = transparence;
            return;
        }

        // Lotte End
        bool
        ServiceCreator::setRunningState()
        {
            ara::exec::ExecutionClient executionClient;
            auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
            if (exec.HasValue())
            {
                mLogger.LogInfo() << "ServiceCreator app in Running State";
            }
            else
            {
                mLogger.LogError() << exec.Error().Message();
                return false;
            }
            return true;
        }

        bool ServiceCreator::initialize() // 변수 초기화
        {
            mLogger.LogInfo() << __func__;

            // TMoodLamp
            this->BrightnessSend = 0;
            this->moodSend = lmp::mode::SoaMImMoodeMode::kCARE_MOOD;
            this->ColorIndexSend = 0;

            return true;
        }

        bool ServiceCreator::startServiceCreatorStub()
        {
            mLogger.LogInfo() << __func__;

            ara::core::InstanceSpecifier specifier_WiperWash("ServiceCreator/AA/PPort_BCM_WiperWash");
            ara::core::InstanceSpecifier specifier_TMoodLamp("ServiceCreator/AA/PPort_LmpCtrl");
            ara::core::InstanceSpecifier specifier_BmsInfo("ServiceCreator/AA/PPort_BmsInfoSrv");
            ara::core::InstanceSpecifier specifier_AccrPedal("ServiceCreator/AA/PPort_VCS_AccrPedal");
            ara::core::InstanceSpecifier specifier_EnvMonitor("ServiceCreator/AA/PPort_TMS_EnvMonitor");
            ara::core::InstanceSpecifier specifier_Gear("ServiceCreator/AA/PPort_VCS_Gear");
            ara::core::InstanceSpecifier specifier_BrakePedal("ServiceCreator/AA/PPort_VCS_BrakePedal");
            ara::core::InstanceSpecifier specifier_VehSpd("ServiceCreator/AA/PPort_VCS_VehSpd");
            ara::core::InstanceSpecifier specifier_SnsrUss("ServiceCreator/AA/PPort_Snsr_USS");
            ara::core::InstanceSpecifier specifier_Lotte("ServiceCreator/AA/PPort_LotteService");

            wiperSkeletonImpl = std::make_shared<eevp::simulation::WiperSkeletonImpl>(specifier_WiperWash);
            auto wiperListener = std::make_shared<WiperListener>(this);
            wiperSkeletonImpl->setEventListener(wiperListener);
            wiperSkeletonImpl->OfferService();

            tEevpControlSoaMImSkeletonImpl = std::make_shared<eevp::simulation::TEevpControlSoaMImSkeletonImpl>(specifier_TMoodLamp);
            auto tMoodLampListener = std::make_shared<TMoodLampListener>(this);
            tEevpControlSoaMImSkeletonImpl->setEventListener(tMoodLampListener);
            tEevpControlSoaMImSkeletonImpl->OfferService();

            bmsInfoSkeletonImpl = std::make_shared<eevp::simulation::BmsInfoSkeletonImpl>(specifier_BmsInfo);
            bmsInfoSkeletonImpl->OfferService();

            accrPedalSkeletonImpl = std::make_shared<eevp::simulation::AccrPedalSkeletonImpl>(specifier_AccrPedal);
            auto accrPedalListener = std::make_shared<AccrPedalListener>(this);
            accrPedalSkeletonImpl->setEventListener(accrPedalListener);
            accrPedalSkeletonImpl->OfferService();

            envMonitorSkeletonImpl = std::make_shared<eevp::simulation::EnvMonitorSkeletonImpl>(specifier_EnvMonitor);
            auto envMonitorListener = std::make_shared<EnvMonitorListener>(this);
            envMonitorSkeletonImpl->setEventListener(envMonitorListener);
            envMonitorSkeletonImpl->OfferService();

            gearSkeletonImpl = std::make_shared<eevp::simulation::GearSkeletonImpl>(specifier_Gear);
            auto gearListener = std::make_shared<GearListener>(this);
            gearSkeletonImpl->setEventListener(gearListener);
            gearSkeletonImpl->OfferService();

            brakePedalSkeletonImpl = std::make_shared<eevp::simulation::BrakePedalSkeletonImpl>(specifier_BrakePedal);
            auto brakePedalListener = std::make_shared<BrakePedalListener>(this);
            brakePedalSkeletonImpl->setEventListener(brakePedalListener);
            brakePedalSkeletonImpl->OfferService();

            vehSpdSkeletonImpl = std::make_shared<eevp::simulation::VehSpdSkeletonImpl>(specifier_VehSpd);
            auto vehSpdListener = std::make_shared<VehSpdListener>(this);
            vehSpdSkeletonImpl->setEventListener(vehSpdListener);
            vehSpdSkeletonImpl->OfferService();

            snsrUssSkeletonImpl = std::make_shared<eevp::simulation::SnsrUssSkeletonImpl>(specifier_SnsrUss);
            auto snsrUssListener = std::make_shared<SnsrUssListener>(this);
            snsrUssSkeletonImpl->setEventListener(snsrUssListener);
            snsrUssSkeletonImpl->OfferService();

            lotteSkeletonImpl = std::make_shared<eevp::simulation::LotteSkeletonImpl>(specifier_Lotte);
            auto lotteListener = std::make_shared<LotteListener>(this);
            lotteSkeletonImpl->setEventListener(lotteListener);
            lotteSkeletonImpl->OfferService();
            mLogger.LogInfo() << __func__;

            return true;
        }

        bool ServiceCreator::startMsgInfoProxy()
        {
            mLogger.LogInfo() << __func__;
            msgInfoProxyImpl = std::make_shared<eevp::simulation::MsgInfoProxyImpl>();
            auto msgInfoListener = std::make_shared<MsgInfoListener>(this);
            msgInfoProxyImpl->setEventListener(msgInfoListener);
            msgInfoProxyImpl->init();

            return true;
        }

        bool ServiceCreator::startSocketClient()
        {
            mLogger.LogInfo() << __func__;
            if (pthread_create(&thread_socket_recv, nullptr, ServiceCreator::socket_recv, this) != 0)
            {
                mLogger.LogInfo() << "소켓 스레드 생성 실패";
                return false;
            }
            if (pthread_create(&thread_socket_send, nullptr, ServiceCreator::socket_send, this) != 0)
            {
                mLogger.LogInfo() << "소켓 스레드 생성 실패";
                return false;
            }
            return true;
        }

        void *ServiceCreator::socket_send(void *inst)
        {
            ServiceCreator *instance = static_cast<ServiceCreator *>(inst);
            instance->mLogger.LogInfo() << __func__;

            int sock;
            char sendMessage[BUF_SIZE];
            std::string sendMessage_s;
            int str_len;
            struct sockaddr_in serv_adr;

            sock = socket(AF_INET, SOCK_STREAM, 0);

            if (sock == -1)
            {
                instance->mLogger.LogInfo() << "send_socket() error";
                return nullptr;
            }

            // memset(&serv_adr, 0, sizeof(serv_adr));
            serv_adr.sin_family = AF_INET;
            serv_adr.sin_addr.s_addr = inet_addr("192.168.100.242");
            // serv_adr.sin_addr.s_addr = inet_addr("169.254.195.237");
            serv_adr.sin_port = htons(5000);
            // serv_adr.sin_port = htons(3363);

            // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
            if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
                instance->mLogger.LogInfo() << "send_connect() error!";
            else
                instance->mLogger.LogInfo() << "send_Connected...........";

            while (mRunning)
            {
                json data = instance->prepareData();
                sendMessage_s = data.dump();
                strcpy(sendMessage, sendMessage_s.c_str());
                str_len = write(sock, sendMessage, BUF_SIZE - 1);
                if (str_len == -1)
                {
                    instance->mLogger.LogInfo() << "send_Connect is broken";
                    break;
                }
                sendMessage[str_len] = 0;
                instance->mLogger.LogInfo() << "Send to Server: " << sendMessage;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }

            // 서버 소켓과 연결 후 송신해야 하는 이벤트 발생 시 데이터 송신
            return nullptr;
        }

        void *ServiceCreator::socket_recv(void *inst)
        {
            ServiceCreator *instance = static_cast<ServiceCreator *>(inst);
            instance->mLogger.LogInfo() << __func__;

            ///////////////////// 값을 소켓으로 받아서 recv데이터로 대입 /////////////////////

            int sock;
            char recvMessage[BUF_SIZE];
            std::string recvMessage_s;
            int str_len;
            struct sockaddr_in serv_adr;

            sock = socket(AF_INET, SOCK_STREAM, 0);

            if (sock == -1)
            {
                instance->mLogger.LogInfo() << "recv_socket() error";
                return nullptr;
            }

            // memset(&serv_adr, 0, sizeof(serv_adr));
            serv_adr.sin_family = AF_INET;
            serv_adr.sin_addr.s_addr = inet_addr("192.168.100.242");
            // serv_adr.sin_addr.s_addr = inet_addr("169.254.195.237");
            serv_adr.sin_port = htons(5000);
            // serv_adr.sin_port = htons(3363);

            // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
            if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
                instance->mLogger.LogInfo() << "recv_connect() error!";
            else
                instance->mLogger.LogInfo() << "Connected...........";

            // 소켓 read 루프 => read 후 다른 서비스로 스켈레톤을 통해 전송 구현 필요
            while (mRunning)
            {
                str_len = read(sock, recvMessage, BUF_SIZE);
                if (str_len == -1)
                {
                    instance->mLogger.LogInfo() << "recv_Connect is broken";
                    break;
                }
                recvMessage[str_len] = 0;
                // instance->mLogger.LogInfo() << "Message from server: " << recvMessage;

                try
                {
                    // JSON 객체로 변환
                    json recvData = json::parse(recvMessage);
                    instance->mLogger.LogInfo() << "데이터 추출";

                    // JSON 객체에서 데이터 추출
                    instance->extractWiperData(recvData["Wiper"]);
                    instance->extractBatteryData(recvData["Battery"]);
                    instance->extractAccrPedalData(recvData["AccrPedal"]);
                    instance->extractEnvMonitorData(recvData["EnvMonitor"]);
                    instance->extractGearData(recvData["Gear"]);
                    instance->extractBrakePedalData(recvData["BrakePedal"]);
                    instance->extractVehSpdData(recvData["VehSpd"]);
                    instance->extractSnsrUssData(recvData["SonarInfo"]);
                    instance->extractLotteData(recvData["Lotte"]);

                    // 받은 데이터 로그 출력 (디버깅용)
                    instance->getWiperRecv();

                    // 각 구독앱에 Update
                    // Wiper
                    instance->setWipingLevel(instance->wiperRecv.wipingLevel);
                    instance->setWipingInterval(instance->wiperRecv.wipingInterval);

                    // BmsInfo
                    instance->notifyBmsInfo(instance->bmsInfo);
                }
                catch (const json::parse_error &e)
                {
                    instance->mLogger.LogInfo() << "JSON parse error: " << e.what();
                }
            }
            return nullptr;
        }

        // Wiper 데이터 추출
        void ServiceCreator::extractWiperData(const json &wiperData)
        {
            wiperRecv.wipingLevel = static_cast<eevp::simulation::BCM_WipingLevel>(wiperData.value("wipingLevel", 0));
            wiperRecv.wipingInterval = wiperData.value("wipingInterval", 0);
        }

        // Battery 데이터 추출
        void ServiceCreator::extractBatteryData(const json &batteryData)
        {
            bmsInfo.InterfaceIDforDbg = batteryData.value("InterfaceIDforDbg", 0);
            bmsInfo.DataSerialNumber = batteryData.value("DataSerialNumber", 0);
            bmsInfo.VehicleUniqueSnr = batteryData.value("VehicleUniqueSnr", 0);
            bmsInfo.EMS_BatteryAvgTemperature = batteryData.value("EMS_BatteryAvgTemperature", 0);
            bmsInfo.EMS_ChargerOutputVolt = batteryData.value("EMS_ChargerOutputVolt", 0);
            bmsInfo.EMS_ChargerOutputCurr = batteryData.value("EMS_ChargerOutputCurr", 0);
            bmsInfo.EMS_ReturnCode = batteryData.value("EMS_ReturnCode", 0);
            bmsInfo.EMS_ConnectionStatus = batteryData.value("EMS_ConnectionStatus", 0);
            bmsInfo.EMS_TargetVolt = batteryData.value("EMS_TargetVolt", 0);
            bmsInfo.EMS_TargetCurr = batteryData.value("EMS_TargetCurr", 0);
            bmsInfo.EMS_RemainHour = batteryData.value("EMS_RemainHour", 0);
            bmsInfo.EMS_RemainMin = batteryData.value("EMS_RemainMin", 0);
            bmsInfo.EMS_HVBattSOC = batteryData.value("EMS_HVBattSOC", 0);
            bmsInfo.EMS_HVBattSOE = batteryData.value("EMS_HVBattSOE", 0);
            bmsInfo.EMS_HVBattSOH = batteryData.value("EMS_HVBattSOH", 0);
            bmsInfo.EMS_BattVolt = batteryData.value("EMS_BattVolt", 0);
            bmsInfo.EMS_BattCurr = batteryData.value("EMS_BattCurr", 0);
            bmsInfo.EMS_Obc_dcVolt = batteryData.value("EMS_Obc_dcVolt", 0);
            bmsInfo.EMS_Obc_dcCurr = batteryData.value("EMS_Obc_dcCurr", 0);
            bmsInfo.EMS_Avn_ChargeCurrSetSts = batteryData.value("EMS_Avn_ChargeCurrSetSts", 0);
            bmsInfo.EMS_HVBatt_MainRlyCloseReq = batteryData.value("EMS_HVBatt_MainRlyCloseReq", 0);
            bmsInfo.EMS_HVBatt_preChrgRlyStatus = batteryData.value("EMS_HVBatt_preChrgRlyStatus", 0);
            bmsInfo.EMS_HVBatt_posRlyStatus = batteryData.value("EMS_HVBatt_posRlyStatus", 0);
            bmsInfo.EMS_HVBatt_negRlyStatus = batteryData.value("EMS_HVBatt_negRlyStatus", 0);
            bmsInfo.EMS_Avn_DcChargingTargetSetSts = batteryData.value("EMS_Avn_DcChargingTargetSetSts", 0);
            bmsInfo.EMS_Avn_AcChargingTargetSetSts = batteryData.value("EMS_Avn_AcChargingTargetSetSts", 0);
        }

        // AccrPedal 데이터 추출
        void ServiceCreator::extractAccrPedalData(const json &accrPedalData)
        {
            accrPedal.valid = accrPedalData.value("valid", false);
            accrPedal.switchStatus = static_cast<eevp::simulation::type::SwitchStatus>(accrPedalData.value("switchStatus", 0));
            accrPedal.position = accrPedalData.value("position", static_cast<std::uint16_t>(0));
            accrPedal.kickdownStatus = static_cast<eevp::simulation::type::KickdownStatus>(accrPedalData.value("kickdownStatus", 0));
            accrPedal.faultStatus = accrPedalData.value("faultStatus", static_cast<std::uint8_t>(0));
            accrPedal.positionRate = accrPedalData.value("positionRate", 0);
        }

        // EnvMonitor 데이터 추출
        void ServiceCreator::extractEnvMonitorData(const json &envMonitorData)
        {
            envZoneHumidityAry[0].humidity = envMonitorData["EnvMonitor"].value("interiorhumidity", 0);
            envZoneHumidityAry[1].humidity = envMonitorData["EnvMonitor"].value("exteriorhumidity", 0);
        }

        // Gear 데이터 추출
        void ServiceCreator::extractGearData(const json &gearData)
        {
            gear.GearStatus = static_cast<eevp::simulation::type::GearStatus>(gearData.value("status", 0));
            gear.valid = gearData.value("valid", false);
        }

        // BrakePedal 데이터 추출
        void ServiceCreator::extractBrakePedalData(const json &brakePedalData)
        {
            brakePosn.stroke = brakePedalData.value("stroke", static_cast<std::int16_t>(0));
            brakePosn.strokeValid = brakePedalData.value("strokeValid", false);
            brakePosn.position = brakePedalData.value("position", static_cast<std::int16_t>(0));
            brakePosn.positionValid = brakePedalData.value("positionValid", false);
            brakePosn.strokeRate = brakePedalData.value("strokeRate", static_cast<std::int16_t>(0));
            brakePosn.strokeRateValid = brakePedalData.value("strokeRateValid", false);
            brakeSwitch.switchStatus = static_cast<eevp::simulation::type::SwitchStatus>(brakePedalData.value("switchStatus", 0));
            brakeSwitch.switchValid = brakePedalData.value("switchValid", false);
        }

        // VehSpd 데이터 추출
        void ServiceCreator::extractVehSpdData(const json &vehSpdData)
        {
            vehSpd.absoluteValue = vehSpdData.value("absoluteValue", 0);
            vehSpd.actualValue = vehSpdData.value("actualValue", 0);
            vehSpd.direction = static_cast<eevp::simulation::type::DirectionVeh>(vehSpdData.value("direction", 0));
            vehSpd.directionValid = vehSpdData.value("directionValid", false);
            vehSpd.valid = vehSpdData.value("valid", false);
        }

        // SnsrUss 데이터 추출
        void ServiceCreator::extractSnsrUssData(const json &sonarInfoData)
        {
            ussSonarInfo.pasSonarEchoTof1 = sonarInfoData.value("pasSonarEchoTof1", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEchoWidth1 = sonarInfoData.value("pasSonarEchoWidth1", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEchoPeak1 = sonarInfoData.value("pasSonarEchoPeak1", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEchoTof2 = sonarInfoData.value("pasSonarEchoTof2", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEchoWidth2 = sonarInfoData.value("pasSonarEchoWidth2", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEchoPeak2 = sonarInfoData.value("pasSonarEchoPeak2", static_cast<std::uint16_t>(0));
            ussSonarInfo.pasSonarEmit = sonarInfoData.value("pasSonarEmit", static_cast<std::uint8_t>(0));
            ussSonarInfo.sonarRingingTimer = sonarInfoData.value("sonarRingingTimer", static_cast<std::uint16_t>(0));
        }

        void ServiceCreator::extractLotteData(const json &lotteData)
        {
            // dmsGzDtctn.headLocX = lotteData.value("headLocX", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.headLocY = lotteData.value("headLocY", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.headLocZ = lotteData.value("headLocZ", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocRightX = lotteData.value("eyeLocRightX", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocRightY = lotteData.value("eyeLocRightY", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocRightZ = lotteData.value("eyeLocRightZ", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocLeftX = lotteData.value("eyeLocLeftX", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocLeftY = lotteData.value("eyeLocLeftY", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.eyeLocLeftZ = lotteData.value("eyeLocLeftZ", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.headDirPitch = lotteData.value("headDirPitch", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.headDirYaw = lotteData.value("headDirYaw", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.gazeDirPitch = lotteData.value("gazeDirPitch", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.gazeDirYaw = lotteData.value("gazeDirYaw", static_cast<std::uint8_t>(0));
            // dmsGzDtctn.gazeZone = static_cast<lotte::type::GazaZone>(lotteData.value("gazeZone", 0));
            // dmsGzDtctn.headZone = static_cast<lotte::type::HeadZone>(lotteData.value("headZone", 0));

            // windowLoc = lotteData.value("windowLoc", static_cast<std::int32_t>(0));
            // transparence = lotteData.value("transparence", static_cast<std::int32_t>(0));
            dmsStatus = lotteData.value("dmsStatus", false);
            smartFilmStatus = lotteData.value("smartFilmStatus", false);
        }

        // 데이터를 JSON으로 묶어서 반환
        json ServiceCreator::prepareData()
        {
            json sendData;

            // MoodLamp 데이터
            sendData["MoodLamp"] = {
                {"Brightness", this->BrightnessSend},
                {"mood", static_cast<int>(this->moodSend)},
                {"ColorIndex", this->ColorIndexSend}};

            // Wiper 데이터
            sendData["Wiper"] = {
                {"wipingLevel", this->wiperSend.wipingLevel},
                {"wipingInterval", this->wiperSend.wipingInterval}};

            // Lotte 데이터
            sendData["Lotte"] = {
                {"windowLoc", this->windowLocSend},
                {"transparence", this->transparenceSend}};

            return sendData;
        }

    }
}