#include "ara/exec/execution_client.h"
#include <ctime>
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

        std::atomic_bool ServiceCreator::mRunning(false);

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
            eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval) { return serviceCreator->setWipingInterval(wipingInterval); }
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel(wipingLevel); }

        private:
            ServiceCreator *serviceCreator;
        };

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
            eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval) { return serviceCreator->setWipingInterval(wipingInterval); }
            eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel(wipingLevel); }

            // void isWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->isWiping_C(wipingLevel); }
            // void stopWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->stopWiping_C(wipingLevel); }
            // void startWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->startWiping_C(wipingLevel); }
            // void getWipingInterval_C(std::uint16_t &wipingInterval) { return serviceCreator->getWipingInterval_C(wipingInterval); }
            // void getWipingLevel_C(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->getWipingLevel_C(wipingLevel); }
            // void setWipingLevelImme_C(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevelImme_C(wipingLevel); }
            // void setWipingInterval_C(std::uint16_t &wipingInterval) { return serviceCreator->setWipingInterval_C(wipingInterval); }
            // void setWipingLevel_C(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel_C(wipingLevel); }

            // void getWipingLevel_Subs(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->getWipingLevel_Subs(wipingLevel); }
            // void setWipingLevel_Subs(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevel_Subs(wipingLevel); }

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
            if (!startServiceCreatorStub())
            {
                return false;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

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

            //     this->mQueueForThreadStopping.PopTimeout(&dummy_msg, 1500);
            //     if (!this->uThreadRunning)
            //     {
            //         return;
            //     }

            //     Zone4_Wiper_UpdateContext();

            //     while (this->uThreadRunning)
            //     {
            //         this->mQueueForThreadStopping.PopTimeout(&dummy_msg, 20000);
            //         if (this->mThreadRunning)
            //         {
            //             Zone4_Wiper_UpdateContext();
            //         }
            //     }
            // }
            mLogger.LogInfo() << __func__;
            if (this->uThreadRunning)
            {
                int dummy_msg;
            }
            return;
        }

        bool ServiceCreator::isWiping()
        {
            mLogger.LogInfo() << __func__;
            return true;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::stopWiping()
        {
            mLogger.LogInfo() << __func__;
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::startWiping()
        {
            mLogger.LogInfo() << __func__;
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingLevel(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingLevel(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingInterval(std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            wiperSkeletonImpl->updateWipingInterval(wipingInterval);
            return BCM_ReturnCode::SUCCESS;
        }

        std::uint16_t ServiceCreator::getWipingInterval()
        {
            mLogger.LogInfo() << __func__;
            return 0;
        }

        eevp::simulation::BCM_WipingLevel ServiceCreator::getWipingLevel()
        {
            mLogger.LogInfo() << __func__;
            return wiperRecv.wipingLevel;
        }

        // void ServiceCreator::isWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) {};
        // void ServiceCreator::stopWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) {};
        // void ServiceCreator::startWiping_C(eevp::simulation::BCM_WipingLevel &wipingLevel) {};
        // void ServiceCreator::getWipingInterval_C(std::uint16_t &wipingInterval)
        // {
        //     mLogger.LogInfo() << __func__;
        //     return;
        // };
        // void ServiceCreator::getWipingLevel_C(eevp::simulation::BCM_WipingLevel &wipingLevel)
        // {
        //     mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingLevel) << ")";
        //     return;
        // };
        // void ServiceCreator::setWipingLevelImme_C(const eevp::simulation::BCM_WipingLevel &wipingLevel) {};
        // void ServiceCreator::setWipingInterval_C(std::uint16_t &wipingInterval) {

        // };
        // void ServiceCreator::setWipingLevel_C(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        // {
        //     wiperSkeletonImpl->updateWipingLevel(wipingLevel);
        //     return;
        // };

        // void ServiceCreator::getWipingLevel_Subs(eevp::simulation::BCM_WipingLevel &wipingLevel) {};
        // void ServiceCreator::setWipingLevel_Subs(const eevp::simulation::BCM_WipingLevel &wipingLevel) {};

        void ServiceCreator::getWiperRecv()
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
        void ServiceCreator::getWiperSend()
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

        void ServiceCreator::setWiperSend(std::uint16_t &wipingInterval)
        {
            ServiceCreator::wiperSend.wipingInterval = wipingInterval;
        }

        void ServiceCreator::setWiperSend(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            ServiceCreator::wiperSend.wipingLevel = wipingLevel;
        }

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

        bool ServiceCreator::startServiceCreatorStub()
        {
            mLogger.LogInfo() << __func__;

            ara::core::InstanceSpecifier specifier_WiperWash("ServiceCreator/AA/PPort_BCM_WiperWash");

            wiperSkeletonImpl = std::make_shared<eevp::simulation::WiperSkeletonImpl>(specifier_WiperWash);
            auto wiperListener = std::make_shared<WiperListener>(this);
            wiperSkeletonImpl->setEventListener(wiperListener);
            wiperSkeletonImpl->OfferService();
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

            // get함수로 값 받아와서 Send데이터 계속 송신
            // instance->getWipingLevel();
            // instance->getWipingInterval();
            while(mRunning){
                std::this_thread::sleep_for(std::chrono::seconds(3));
                instance->getWiperRecv();
                instance->getWiperSend();
            }

            // 서버 소켓과 연결 후 송신해야 하는 이벤트 발생 시 데이터 송신
            // while (mRunning)
            // {
            //     std::this_thread::sleep_for(std::chrono::seconds(3));
            //     instance->mLogger.LogInfo() << "SendSocket running";
            //     ServiceCreator::wiperRecv.wipingInterval--;
            //     ServiceCreator::wiperSend.wipingInterval -= 2;
            //     instance->getWiperRecv();
            //     instance->getWiperSend();
            // }
            return nullptr;
        }

        void *ServiceCreator::socket_recv(void *inst)
        {
            ServiceCreator *instance = static_cast<ServiceCreator *>(inst);
            instance->mLogger.LogInfo() << __func__;
            
            ///////////////////// 값을 소켓으로 받아서 recv데이터로 대입 /////////////////////

            ///////////////////// recv데이터 set함수로 보내기 /////////////////////
            // Wiper
            // instance->setWipingLevel(wiperRecv.wipingLevel);
            // instance->setWipingInterval(wiperRecv.wipingInterval);

                // while (mRunning)
                // {
                //     std::this_thread::sleep_for(std::chrono::seconds(2));
                //     instance->mLogger.LogInfo() << "ReceiveSocket running";
                //     ServiceCreator::wiperRecv.wipingInterval++;
                //     ServiceCreator::wiperSend.wipingInterval += 2;
                //     instance->getWiperRecv();
                //     instance->getWiperSend();
                // }

                // 서버 소켓과 연결 후 계속 돌면서 data수신 및 파싱(wiperRecv)
                return nullptr;

            /*소켓 코드*/
            // int sock;
            // char message[BUF_SIZE];
            // int str_len;
            // struct sockaddr_in serv_adr;

            // sock = socket(PF_INET, SOCK_STREAM, 0);
            // if (sock == -1)
            //     mLogger.LogInfo() << "socket() error";

            // memset(&serv_adr, 0, sizeof(serv_adr));
            // serv_adr.sin_family = AF_INET;
            // // ip 및 port 입력
            // serv_adr.sin_addr.s_addr = inet_addr("192.168.100.242");
            // serv_adr.sin_port = htons(5000);

            // // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
            // if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
            //     mLogger.LogInfo() << "connect() error!";
            // else
            //     mLogger.LogInfo() << "Connected...........";

            // // 소켓 read 루프 => read 후 다른 서비스로 스켈레톤을 통해 전송 구현 필요
            // for (int i = 0;; i++)
            // {
            //     // std::string str = "hello" + std::to_string(i);
            //     // strcpy(message, str.c_str());
            //     str_len = read(sock, message, BUF_SIZE - 1);
            //     if (str_len==-1)
            //     {
            //         mLogger.LogInfo() << "Connect is broken";
            //         break;
            //     }
            //     write(sock, message, strlen(message));
            //     message[str_len] = 0;
            //     mLogger.LogInfo() << strlen;
            //     mLogger.LogInfo() << "Message from server and send: " << message;
            //     // json 형식 파싱 예정
            // }
            // close(sock);
            /*소켓 코드 완료*/
        }

    }
}