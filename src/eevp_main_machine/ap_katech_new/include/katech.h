#include "eevp/control/soaroa_proxy.h"

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

    void startRoutineTask();
    void stopRoutineTask();
    void routineTask();

    // IRearCurtainListener
    void notifyRoaDetectState(const eevp::control::SoaRoaDetectState& fieldValue);
    void getSoaRoaDetectState();

private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief Find handler
    void StartFindCallback(ara::com::ServiceHandleContainer<eevp::control::proxy::SoaRoaProxy::HandleType> services, ara::com::FindServiceHandle handle);
    /// @brief Current ProxyHandle
    eevp::control::proxy::SoaRoaProxy::HandleType mProxyHandle;

    /// @brief Service Proxy
    std::unique_ptr<eevp::control::proxy::SoaRoaProxy> mRPort{nullptr};
    /// @brief FindServiceHandle
    ara::com::FindServiceHandle* mFindHandle{nullptr};
    /// @brief Current ProxyHandle
   /// @brief Subscribe Field
    void SubscribeField();
  /// @brief SubscriptionState handler
    void StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state) ;
   /// @brief Process received field value 
    void GetFieldValue();
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

 
    std::thread routineThread;
    std::atomic_bool routineTaskRunning;

    void eventProcessingThread();
    std::thread eventProcessingThreadHandle;

    //std::queue<Event> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondVar;

};

}   // namespace monitoring
}   // namespace eevp
