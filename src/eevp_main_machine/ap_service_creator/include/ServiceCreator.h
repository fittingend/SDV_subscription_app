#include <csignal>
#include <thread>
#include <ara/log/logger.h>

namespace eevp {
namespace simulation {

class ServiceCreator {
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
    ara::log::Logger& mLogger;

};

}   // namespace monitoring
}   // namespace eevp
