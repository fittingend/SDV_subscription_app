#include "eevp/control/soaroa_proxy.h"
//#include "eevp/control/soarcurtain_skeleton.h"

#include <csignal>
#include <thread>

#include <ara/log/logger.h>

#include <queue>
#include <mutex>
#include <condition_variable>

//#include "IKatechListener.h"
#include "IRoaListener.h"

//#include "KatechSkeletonImpl.h"
#include "KatechRoaProxyImpl.h"
#include "KatechSkeletonImpl.hpp"

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
 /// IRoaListener
    void notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void notifySoaRoaSwVersion(const std::uint8_t& fieldValue);
    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaRoaSwVersion(std::uint8_t& fieldValue);

    //new
    void notifyRoaDetectCount(std::uint8_t& soaRoaDetectCount);
    
    void getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState);
    void getSoaRoaDetectCount(std::uint8_t& soaRoaDetectCount);

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
    bool startKatechSkeleton();

    /// @brief Find Control Proxy
    bool startRoaProxy();
    bool startRearCurtainSkeleton();

    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    //std::shared_ptr<eevp::monitoring::MonitoringManagementSkeletonImpl> monitoringManagementSkeletonImpl;
    std::shared_ptr<eevp::control::roa::KatechRoaProxyImpl> roaProxyImpl;
    std::shared_ptr<eevp::control::KatechSkeletonImpl> mPPortImpl;
    eevp::control::KatechSkeletonImpl *mSoaRctn;

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
