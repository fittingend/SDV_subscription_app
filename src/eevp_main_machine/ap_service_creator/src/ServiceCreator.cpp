#include "ara/exec/execution_client.h"
#include <ctime>
#include "ServiceCreator.h"
#include "ara/log/logger.h"

namespace eevp
{
    namespace simulation
    {
        eevp::service::type::wiperRecv ServiceCreator::wiperRecv = {eevp::simulation::BCM_WipingLevel::STOP, 0};
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

        class WiperListener : public eevp::simulation::wiper::IWiperListener
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

            void getWipinginterval(std::uint16_t &wipingInterval) { return serviceCreator->getWipinginterval(wipingInterval); }
            void getWipinglevel(eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->getWipinglevel(wipingLevel); }
            void setWipingLevelimme(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipingLevelimme(wipingLevel); }
            void setWipinginterval(std::uint16_t &wipingInterval) { return serviceCreator->setWipinginterval(wipingInterval); }
            void setWipinglevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) { return serviceCreator->setWipinglevel(wipingLevel); }

        private:
            ServiceCreator *serviceCreator;
        };

        ServiceCreator::ServiceCreator() : mLogger(ara::log::CreateLogger("SVCC", "SVCC", ara::log::LogLevel::kInfo)),
                                           wiperProxyImpl{nullptr},
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

            if (!startSocketClient())
            {
                return false;
            }

            if (!startServiceCreatorStub())
            {
                return false;
            }

            if (!startWiperProxy())
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
                std::this_thread::sleep_for(std::chrono::seconds(3));
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
        }

        bool ServiceCreator::isWiping()
        {
            mLogger.LogInfo() << __func__;

            serviceManagementSkeletonImpl->isWiping();
            return true;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::stopWiping()
        {
            mLogger.LogInfo() << __func__;
            setWiperSend(BCM_WipingLevel::STOP);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::startWiping()
        {
            mLogger.LogInfo() << __func__;
            setWiperSend(BCM_WipingLevel::LOW);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            setWiperSend(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            setWiperSend(wipingLevel);
            return BCM_ReturnCode::SUCCESS;
        }

        eevp::simulation::BCM_ReturnCode ServiceCreator::setWipingInterval(std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            setWiperSend(wipingInterval);
            return BCM_ReturnCode::SUCCESS;
        }

        std::uint16_t ServiceCreator::getWipingInterval()
        {
            mLogger.LogInfo() << __func__;
            serviceManagementSkeletonImpl->updateWipingInterval(ServiceCreator::wiperRecv.wipingInterval);
            return 0;
        }

        eevp::simulation::BCM_WipingLevel ServiceCreator::getWipingLevel()
        {
            mLogger.LogInfo() << __func__;
            serviceManagementSkeletonImpl->updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return wiperRecv.wipingLevel;
        }

        void ServiceCreator::getWipinginterval(std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;
            serviceManagementSkeletonImpl->updateWipingInterval(ServiceCreator::wiperRecv.wipingInterval);
            return;
        }
        void ServiceCreator::getWipinglevel(eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            serviceManagementSkeletonImpl->updateWipingLevel(ServiceCreator::wiperRecv.wipingLevel);
            return;
        }
        void ServiceCreator::setWipingLevelimme(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            return;
        }
        void ServiceCreator::setWipinginterval(std::uint16_t &wipingInterval)
        {
            mLogger.LogInfo() << __func__;

            return;
        }
        void ServiceCreator::setWipinglevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            mLogger.LogInfo() << __func__;
            return;
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

        bool ServiceCreator::startWiperProxy()
        {
            mLogger.LogInfo() << __func__;
            ServiceCreator::getWiperRecv();
            ServiceCreator::getWiperSend();

            wiperProxyImpl = std::make_shared<eevp::simulation::wiper::WiperProxyImpl>();
            auto wiperListener = std::make_shared<WiperListener>(this);
            wiperProxyImpl->setEventListener(wiperListener);
            wiperProxyImpl->init();
            return true;
        }

        bool ServiceCreator::startServiceCreatorStub()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier_WiperWash("ServiceCreator/AA/PPort_BCM_WiperWash");
            ara::core::InstanceSpecifier specifier("ServiceCreator/AA/PPort_ServiceManagement");
            serviceManagementSkeletonImpl = std::make_shared<eevp::service::ServiceManagementSkeletonImpl>(specifier);
            auto serviceManagementListener = std::make_shared<ServiceManagementListener>(this);
            serviceManagementSkeletonImpl->setEventListener(serviceManagementListener);
            serviceManagementSkeletonImpl->OfferService();
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
            // 서버 소켓과 연결 후 송신해야 하는 이벤트 발생 시 데이터 송신
            while (mRunning)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                instance->mLogger.LogInfo() << "SendSocket running";
                ServiceCreator::wiperRecv.wipingInterval--;
                ServiceCreator::wiperSend.wipingInterval -= 2;
                instance->getWiperRecv();
                instance->getWiperSend();
            }
        }

        void *ServiceCreator::socket_recv(void *inst)
        {
            ServiceCreator *instance = static_cast<ServiceCreator *>(inst);
            instance->mLogger.LogInfo() << __func__;

            while (mRunning)
            {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                instance->mLogger.LogInfo() << "ReceiveSocket running";
                ServiceCreator::wiperRecv.wipingInterval++;
                ServiceCreator::wiperSend.wipingInterval += 2;
                instance->getWiperRecv();
                instance->getWiperSend();
            }

            // 서버 소켓과 연결 후 계속 돌면서 data수신 및 파싱(wiperRecv)
            // int sock;
            // char message[BUF_SIZE];
            // int str_len;
            // struct sockaddr_in serv_adr;

            // sock = socket(PF_INET, SOCK_STREAM, 0);
            // if (sock == -1)
            //     instance->mLogger.LogInfo() << "socket() error";

            // memset(&serv_adr, 0, sizeof(serv_adr));
            // serv_adr.sin_family = AF_INET;
            // // ip 및 port 입력
            // serv_adr.sin_addr.s_addr = inet_addr("192.168.100.242");
            // serv_adr.sin_port = htons(5000);

            // // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
            // if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
            //     instance->mLogger.LogInfo() << "connect() error!";
            // else
            //     instance->mLogger.LogInfo() << "Connected...........";

            // // 소켓 read 루프 => read 후 wiperRecv로 저장
            // for (int i = 0;; i++)
            // {
            //     // std::string str = "hello" + std::to_string(i);
            //     // strcpy(message, str.c_str());
            //     str_len = read(sock, message, BUF_SIZE - 1);
            //     if (str_len == -1)
            //     {
            //         instance->mLogger.LogInfo() << "Connect is broken";
            //         break;
            //     }
            //     write(sock, message, strlen(message));
            //     message[str_len] = 0;
            //     instance->mLogger.LogInfo() << strlen;
            //     instance->mLogger.LogInfo() << "Message from server and send: " << message;
            //     // json 형식 파싱 예정
            // }
            // close(sock);
            /*소켓 코드 완료*/

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