#include <csignal>
#include <thread>

#include <ara/log/logger.h>

#include <queue>
#include <mutex>
#include <condition_variable>

#include "IMonitoringManagementListener.h"
#include "IOtaMonitoringListener.h"
#include "IStateManagerListener.h"
#include "IMoodLampListener.h"
#include "IRearCurtainListener.h"

#include "MonitoringManagementSkeletonImpl.h"
#include "OtaMonitoringProxyImpl.h"
#include "StateManagerProxyImpl.h"
#include "MoodLampProxyImpl.h"
#include "RearCurtainProxyImpl.h"

namespace eevp {
namespace monitoring {

class MonitoringManager {
public:
    /// @brief Constructor
    MonitoringManager();
    /// @brief Destructor
    ~MonitoringManager();

    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run(int ac, char** av);
    /// @brief Terminate S/W Component
    void Terminate();

    void startThirtySecondTask();
    void stopThirtySecondTask();
    void thirtySecondTask();

    // IMonitoringManagementListener.h
    bool requestAppInstall(const eevp::type::String& serviceName);
    bool requestAppUpdate(const eevp::type::String& serviceName);
    bool requestControllerServiceInfo(
                    const eevp::type::String& serviceName,
                    eevp::monitoring::type::ControllerServiceInfo& serviceInfo);
    bool requestControllerServiceInfoAll(eevp::monitoring::type::ControllerServiceInfoMap& infoMap);
    bool requestControllerServiceStatus(const eevp::type::String& serviceName, eevp::type::String& status);
    bool requestControllerServiceStatusAll(eevp::monitoring::type::ControllerServiceStatusMap& statusMap);
    bool setEnableControllerService(const eevp::type::String& serviceName, const eevp::type::String& enable);
    bool requestControllerServiceInfoAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& version,
                    eevp::monitoring::type::TimeArray& lastUpdateTime);
    bool requestControllerServiceStatusAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& serviceStatus,
                    eevp::monitoring::type::StringArray& serviceEnable,
                    eevp::monitoring::type::StringArray& serviceControl);
    bool setControlControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& serviceControl);
    void resetUcmTest();

    // IStateManagerListener
    void notifyNotifySystemState(const ivi::info::statemanager::type::State& state);
    void notifyNotifyTime(const std::uint8_t& notifyTime);
    void notifySystemState(const ivi::info::statemanager::type::State& state);

    // IOtaMonitoringListener
    void notifyServiceEvent(const eevp::ota::monitoring::type::RequestServiceInfo& requestServiceInfo);
    void notifyUpdatableService(const eevp::ota::monitoring::type::UpdatableServiceInfo& updatableServiceInfo);

    // IMoodLampListener
    void notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue);
    void getSoaMlmStatus();

    // IRearCurtainListener
    void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue);
    void getSoaRctnStatus();

    enum EventType {
        SERVICE_INFO_SPARE,
        SERVICE_STATUS_SPARE,
        SERVICE_ERROR,
        SERVICE_UPDATABLE
    };

    struct Event {
        EventType type;
        union {
            eevp::monitoring::type::ControllerServiceInfoSpare serviceInfoSpare;
            eevp::monitoring::type::ControllerServiceStatusSpare serviceStatusSpare;
            eevp::monitoring::type::ControllerServiceErrorEvent serviceErrorEvent;
            eevp::monitoring::type::UpdatableServiceList serviceUpdatableEvent;
        };

        Event(const eevp::monitoring::type::ControllerServiceInfoSpare& evt)
            : type(SERVICE_INFO_SPARE), serviceInfoSpare(evt) {}

        Event(const eevp::monitoring::type::ControllerServiceStatusSpare& evt)
            : type(SERVICE_STATUS_SPARE), serviceStatusSpare(evt) {}

        Event(const eevp::monitoring::type::ControllerServiceErrorEvent& evt)
            : type(SERVICE_ERROR), serviceErrorEvent(evt) {}

        Event(const eevp::monitoring::type::UpdatableServiceList& evt)
            : type(SERVICE_UPDATABLE), serviceUpdatableEvent(evt) {}

        ~Event() {
            switch (type) {
                case SERVICE_INFO_SPARE:
                    serviceInfoSpare.~ControllerServiceInfoSpare();
                    break;
                case SERVICE_STATUS_SPARE:
                    serviceStatusSpare.~ControllerServiceStatusSpare();
                    break;
                case SERVICE_ERROR:
                    serviceErrorEvent.~ControllerServiceErrorEvent();
                case SERVICE_UPDATABLE:
                    serviceUpdatableEvent.~UpdatableServiceList();
            }
        }

        Event(const Event& other) : type(other.type) {
            switch (type) {
                case SERVICE_INFO_SPARE:
                    new(&serviceInfoSpare) eevp::monitoring::type::ControllerServiceInfoSpare(other.serviceInfoSpare);
                    break;
                case SERVICE_STATUS_SPARE:
                    new(&serviceStatusSpare) eevp::monitoring::type::ControllerServiceStatusSpare(other.serviceStatusSpare);
                    break;
                case SERVICE_ERROR:
                    new(&serviceErrorEvent) eevp::monitoring::type::ControllerServiceErrorEvent(other.serviceErrorEvent);
                    break;
                case SERVICE_UPDATABLE:
                    new(&serviceUpdatableEvent) eevp::monitoring::type::UpdatableServiceList(other.serviceUpdatableEvent);
            }
        }

         Event& operator=(const Event& other) {
            if (this != &other) {
                this->~Event();
                new(this) Event(other);
            }
            return *this;
        }
    };

    void enqueueEvent(const Event& event);

private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Find StateManager Proxy
    bool startStateManagerProxy();

    /// @brief Find Proxy
    bool startOtaMonitoringProxy();

    /// @brief Start Stub
    bool startMonitoringManagementStub();

    /// @brief Find Control Proxy
    bool startMoodLampProxy();
    bool startRearCurtainProxy();

    void printMap();
    eevp::type::String getCurrentDate();
    void requestVersionInfo();

    std::thread periodicThread;
    std::atomic_bool stopPeriodicTask{false};

    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    std::shared_ptr<ivi::info::statemanager::StateManagerProxyImpl> stateManagerProxyImpl;
    std::shared_ptr<eevp::monitoring::OtaMonitoringProxyImpl> otaMonitoringProxyImpl;
    std::shared_ptr<eevp::monitoring::MonitoringManagementSkeletonImpl> monitoringManagementSkeletonImpl;
    std::shared_ptr<eevp::control::moodlamp::MoodLampProxyImpl> moodLampProxyImpl;
    std::shared_ptr<eevp::control::rearcurtain::RearCurtainProxyImpl> rearCurtainProxyImpl;

    eevp::monitoring::type::ControllerServiceInfoMap controllerInfoMap;
    eevp::monitoring::type::ControllerServiceStatusMap controllerStatusMap;

    struct controllerTemp {
        eevp::type::String serviceName;
        eevp::type::String serviceStatus;
        eevp::type::String serviceEnable;
        eevp::type::String serviceControl;
    };

    using ControllerServiceStatusMap = ara::core::Map<eevp::type::String, controllerTemp>;
    ControllerServiceStatusMap controllerServiceStatusMap;

    std::thread thrityThread;
    std::atomic_bool thrityRunning;

    void eventProcessingThread();
    std::thread eventProcessingThreadHandle;

    std::queue<Event> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondVar;

    ivi::info::statemanager::type::State state;
    std::uint8_t notifyTime;
};

}   // namespace monitoring
}   // namespace eevp
