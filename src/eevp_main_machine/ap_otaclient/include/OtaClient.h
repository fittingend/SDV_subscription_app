#include <csignal>
#include <thread>

#include <ara/log/logger.h>
#include <ara/vucm/pkgmgr/vehiclepackagemanagement_proxy.h>

#include "IOtaMonitoringListener.h"
#include "IOtaSubscriptionListener.h"
#include "IVehiclePackageManagementListener.h"

#include "DataTransfer.h"
#include "OtaMonitoringSkeletonImpl.h"
#include "OtaSubscriptionSkeletonImpl.h"
#include "VehiclePackageManagementProxyImpl.h"

#include "OtaDefine.h"

#ifdef HAWKBIT
#include "hawkbit_config_file.h"
#include "hawkbit_client.h"
#include "vpackage_management_app.h"
#endif

namespace eevp {
namespace ota {

class OtaClient {
public:
    /// @brief Constructor
    OtaClient();
    /// @brief Destructor
    ~OtaClient();

    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run(int ac, char** av);
    /// @brief Terminate S/W Component
    void Terminate();

    // IVehiclePackageManagementListener
    void notifyRequestedPackage(const ara::ucm::SwNameVersionType& requestedPackage);
    void notifySafetyState(const bool& safetyState);
    void notifyTransferState(const ara::ucm::TransferStateType& transferState);

    // IOtaMonitoringListener
    void requestServiceInstall(const eevp::type::String& serviceName);
    void requestServiceUpdate(const eevp::type::String& serviceName);
    void requestServiceInfoMap(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap);
    void resetUcmTest();

    // IOtaSubscriptionListener
    void requestAppInstall(const eevp::type::String& appName);
    void requestAppUpdate(const eevp::type::String& appName);
    void requestAppInfoMap(eevp::ota::subscription::type::RequestAppInfoMap& requestAppInfoMap);

private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);

    /// @brief set Running State
    bool setRunningState();

    /// @brief Find Proxy
    bool startVehiclePackageManagementProxy();

    /// @brief Start Stub
    bool startMonitoringStub();

    /// @brief Start Stub
    bool startSubscriptionStub();

    void deployment(const eevp::type::String& packageName);

#ifdef UCM_TEST
    void ucmtest(const std::vector<std::string>& packages);
#endif

#ifdef HAWKBIT
    void RunHawkbitProvider(
            VehiclePackageManagementApp<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy>& app,
            std::string const& configFile);
#endif

    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;

    std::shared_ptr<eevp::ota::DataTransfer> dataTransfer;
    std::shared_ptr<eevp::ota::vucm::VehiclePackageManagementProxyImpl> vehiclePackageManagementProxyImpl;
    std::shared_ptr<eevp::ota::monitoring::OtaMonitoringSkeletonImpl> otaMonitoringSkeletonImpl;
    std::shared_ptr<eevp::ota::subscription::OtaSubscriptionSkeletonImpl> otaSubscriptionSkeletonImpl;

    eevp::ota::OtaUtils* pOtaUtils;

    eevp::ota::monitoring::type::RequestServiceInfoMap serviceInfoMap;
    eevp::ota::subscription::type::RequestAppInfoMap appInfoMap;
    stSessionInfo sessionInfo;
};

}   // namespace ota
}   // namespace eevp
