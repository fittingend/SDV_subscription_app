#include "provider_skeleton_impl.h"

#include <random>
#include <thread>
#include <chrono>
#include <csignal>
#include <ara/log/logger.h>

namespace swc
{

using namespace test::dummy::skeleton;
class Provider
{
public:
    /// @brief Constructor
    Provider();
    /// @brief Destructor
    ~Provider() = default;
    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run();
    /// @brief Terminate S/W Component
    void Terminate();
private:
    /// @brief Send Event
    void SendEvent();
    /// @brief Send Field Notification
    void SendNotification();
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);
    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;
    // ptr for skeleton
    std::unique_ptr<DummyTestSkeletonImpl> mPPortImpl;
    int i;
    bool tf;
};
}
