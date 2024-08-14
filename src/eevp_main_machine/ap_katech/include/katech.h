#include <csignal>
#include <thread>

#include <ara/log/logger.h>

#include <queue>
#include <mutex>
#include <condition_variable>

//#include "IKatechListener.h"
#include "IRoaListener.h"

//#include "KatechSkeletonImpl.h"
#include "RoaProxyImpl.h"

namespace eevp {
namespace control {

class KATECH {
public:
    /// @brief Constructor
    KATECH();
    /// @brief Destructor
    ~KATECH();

    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run();
    /// @brief Terminate S/W Component
    void Terminate();

    //void startThirtySecondTask();
    //void stopThirtySecondTask();
    //void thirtySecondTask();

    // IRearCurtainListener
    //void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue);
    void getSoaRoaDetectState();

private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Start Stub
    bool startKatechStub();

    /// @brief Find Control Proxy
    bool startRoaProxy();

    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    //std::shared_ptr<eevp::monitoring::MonitoringManagementSkeletonImpl> monitoringManagementSkeletonImpl;
    std::shared_ptr<eevp::control::roa::RoaProxyImpl> roaProxyImpl;

 
    std::thread thrityThread;
    std::atomic_bool thrityRunning;

    void eventProcessingThread();
    std::thread eventProcessingThreadHandle;

    //std::queue<Event> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondVar;

};

}   // namespace monitoring
}   // namespace eevp
