#include "ara/exec/execution_client.h"
#include <ctime>
#include "ServiceCreator.h"
#include "ara/log/logger.h"

namespace eevp
{
    namespace simulation
    {

        std::atomic_bool ServiceCreator::mRunning(false);

        ServiceCreator::ServiceCreator() : mLogger(ara::log::CreateLogger("SVCC", "SVCC", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
            // std::signal(SIGINT, SignalHandler);
            std::signal(SIGTERM, SignalHandler);
        }

        ServiceCreator::~ServiceCreator()
        {
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

            if (!setRunningState())
            {
                return false;
            }

            return true;
        }

        void
        ServiceCreator::Run()
        {
            mLogger.LogInfo() << __func__;

            // while (mRunning)
            // {
            //     mLogger.LogInfo() << "Service Creator running";
            //     std::this_thread::sleep_for(std::chrono::seconds(2));
            // }
            /*소켓 코드*/
            int sock;
            char message[BUF_SIZE];
            int str_len;
            struct sockaddr_in serv_adr;

            sock = socket(PF_INET, SOCK_STREAM, 0);
            if (sock == -1)
                mLogger.LogInfo() << "socket() error";

            memset(&serv_adr, 0, sizeof(serv_adr));
            serv_adr.sin_family = AF_INET;
            serv_adr.sin_addr.s_addr = inet_addr("192.168.100.242");
            serv_adr.sin_port = htons(5000);

            // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
            if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
                mLogger.LogInfo() << "connect() error!";
            else
                mLogger.LogInfo() << "Connected...........";

            // 사용자가 q를 입력할 때까지 반복
            for (int i = 0; ; i++)
            {
                std::string str = "hello" + std::to_string(i);
                strcpy(message, str.c_str());

                // 콘솔창에 출력하는 함수
                str_len = read(sock, message, BUF_SIZE - 1);
                mLogger.LogInfo() << message;
                write(sock, message, strlen(message));
                message[str_len] = 0;
                mLogger.LogInfo() << "Message from server and send: " << message;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            close(sock);
            /*소켓 코드 완료*/
        }

        void
        ServiceCreator::Terminate()
        {
            mLogger.LogInfo() << __func__;
            mRunning = false;
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

    }
}