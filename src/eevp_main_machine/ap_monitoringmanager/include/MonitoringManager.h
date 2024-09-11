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
#include "IPdwListener.h"
#include "IWiperListener.h"
#include "IRoaListener.h"
#include "IDrvseatListener.h"
#include "IRearCurtainListener.h"
#include "IPowerListener.h"

#include "MonitoringManagementSkeletonImpl.h"
#include "OtaMonitoringProxyImpl.h"
#include "StateManagerProxyImpl.h"
#include "MoodLampProxyImpl.h"
#include "PdwProxyImpl.h"
#include "WiperProxyImpl.h"
#include "RoaProxyImpl.h"
#include "DrvseatProxyImpl.h"
#include "RearCurtainProxyImpl.h"
#include "PowerProxyImpl.h"

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

    int i;

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

    /// IStateManagerListener
    void notifyNotifySystemState(const ivi::info::statemanager::type::State& state);
    void notifyNotifyTime(const std::uint8_t& notifyTime);
    void notifySystemState(const ivi::info::statemanager::type::State& state);

    /// IOtaMonitoringListener
    void notifyServiceEvent(const eevp::ota::monitoring::type::RequestServiceInfo& requestServiceInfo);
    void notifyUpdatableService(const eevp::ota::monitoring::type::UpdatableServiceInfo& updatableServiceInfo);

    void resetUcmTest();

    /// IMoodLampListener
    void notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue);
    void notifySoaMlmSwVersion(const std::uint8_t & fieldValue);
    void getSoaMlmStatus(eevp::control::SoaMlmStatus& fieldValue);
    void getSoaMlmSwVersion(std::uint8_t& fieldValue);

    void RequestMlmSetRgbColor(const std::uint8_t& colorTableIndex);

    /// IPdwListener
    void notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel);

    /// IWiperListener
    void notifySoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void notifySoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue);
    void notifySoaWiperSwVersion(const std::uint8_t& wiperSwVersion);
    void getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue);
    void getSoaWiperSwVersion(std::uint8_t& wiperSwVersion);

    void requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode);
    void setWiperAutoSpeed(const bool& isAutoSpeed);

    /// IRoaListener
    void notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void notifySoaRoaSwVersion(const std::uint8_t& fieldValue);
    void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaRoaSwVersion(std::uint8_t& fieldValue);

    /// IDrvseatListener
    void notifySoaDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void notifySoaDrvseatSwVersion(const std::uint8_t& drvseatSwVersion);
    void getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaDrvseatSwVersion(std::uint8_t& drvseatSwVersion);

    /// IRearCurtainListener
    void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue);
    void notifySoaRctnSwVersion(const std::uint8_t& fieldValue);
    void getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue);
    void getSoaRctnSwVersion(std::uint8_t& fieldValue);

    void RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir);
    void RequestRearCurtainPosition(const std::uint8_t& posPercentage);

    /// IPowerListener
    void notifySoaPowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void notifySoaPowerSwVersion(const std::uint8_t& fieldValue);

    void getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal);
    void getSoaPowerSwVersion( std::uint8_t& fieldValue);

    //test
    void getSoaRoaDetectState();
    void getSoaRoaDetectCount();


private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Find StateManager Proxy
    bool startStateManagerProxy();

    /// @brief Find Ota Proxy
    bool startOtaMonitoringProxy();

    /// @brief Find MoodLamp Proxy
    bool startMoodLampProxy();

/// @brief Find Pdw Proxy
    bool startPdwProxy();

    /// @brief Find Wiper Proxy
    bool startWiperProxy();

    /// @brief Find Roa Proxy
    bool startRoaProxy();

    /// @brief Find DriverSeat Proxy
    bool startDrvseatProxy();

    /// @brief Find RearCurtain Proxy
    bool startRearCurtainProxy();

    /// @brief Find Power Proxy
    bool startPowerProxy();

    /// @brief Start Stub
    bool startMonitoringManagementStub();

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
    std::shared_ptr<eevp::pdw::PdwProxyImpl> pdwProxyImpl;
    std::shared_ptr<eevp::control::wiper::WiperProxyImpl> wiperProxyImpl;
    std::shared_ptr<eevp::control::rearcurtain::RearCurtainProxyImpl> rearCurtainProxyImpl;
    std::shared_ptr<eevp::control::roa::RoaProxyImpl> roaProxyImpl;
    std::shared_ptr<eevp::control::drvseat::DrvseatProxyImpl> drvseatProxyImpl;
    std::shared_ptr<eevp::control::power::PowerProxyImpl> powerProxyImpl;


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

    ivi::info::statemanager::type::State state;
    std::uint8_t notifyTime;
};

}   // namespace monitoring
}   // namespace eevp
