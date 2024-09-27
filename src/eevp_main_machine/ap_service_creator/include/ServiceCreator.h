#include <csignal>
#include <thread>
#include <ara/log/logger.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

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

        private:
            static void SignalHandler(std::int32_t signal);

            /// @brief set Running State
            bool setRunningState();

            static std::atomic_bool mRunning;
            ara::log::Logger &mLogger;
        };

    } // namespace monitoring
} // namespace eevp
