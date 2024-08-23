#ifndef EEVP_OTA_VEHICLE_PACKAGE_MANAGEMENT_PROXY_IMPL_H_
#define EEVP_OTA_VEHICLE_PACKAGE_MANAGEMENT_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "ara/vucm/pkgmgr/vehiclepackagemanagement_proxy.h"
#include "ara/log/logger.h"

#include "IVehiclePackageManagementListener.h"

namespace eevp {
namespace ota {
namespace vucm {

class VehiclePackageManagementProxyImpl {
public:
    VehiclePackageManagementProxyImpl();
    ~VehiclePackageManagementProxyImpl();

    void setEventListener(std::shared_ptr<eevp::ota::vucm::IVehiclePackageManagementListener> _listener);
    bool init();

    std::shared_ptr<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy> getVehiclePackageManagementProxy();

    // method
    bool allowCampaign();
    bool cancelCampaign(const bool& disableCampaign);
    bool deleteTransfer(const ara::ucm::TransferIdType& id);
    bool getCampaignHistory(
                    const std::uint64_t& timestampGE,
                    const std::uint64_t& timestampLT,
                    ara::ucm::CampaignHistoryType& campaignHistory);
    bool getSwClusterInfo(ara::ucm::SwClusterInfoVectorType& swInfo);
    bool getSwPackages(ara::ucm::SwPackageInfoVectorType& packages);
    bool swPackageInventory(
                    const ara::ucm::SwNameVersionVectorType& availableSoftwarePackages,
                    ara::ucm::SwNameVersionVectorType& requiredSoftwarePackages);
    bool transferData(
                    const ara::ucm::TransferIdType& id,
                    const ara::ucm::ByteVectorType& data,
                    const std::uint64_t& blockCounter);
    bool transferExit(const ara::ucm::TransferIdType& id);
    bool transferStart(
                    const ara::ucm::SwNameType& softwarePackageName,
                    ara::ucm::TransferIdType& id,
                    const std::uint64_t& size,
                    std::uint32_t& blockSize);
    bool transferVehiclePackage(
                    const std::uint64_t& size,
                    ara::ucm::TransferIdType& id,
                    std::uint32_t& blockSize);

    // field getter
    bool getterRequestedPackage(ara::ucm::SwNameVersionType& requestedPackage);
    bool getterSafetyState(bool& safetyState);
    bool getterTransferState(ara::ucm::TransferStateType& transferState);

    ara::ucm::TransferStateType getTransferState();
    ara::core::Vector<ara::ucm::SwNameVersionType> getRequestedPackageList();

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Event
    void SubscribeEvent();
    /// @brief Subscribe Field
    void SubscribeField();

    /// @brief Unsubscribe Event
    void UnsubscribeEvent();
    /// @brief Unsubscribe Field
    void UnsubscribeField();

    /// @brief Process received field value
    void cbRequestedPackage();
    void cbSafetyState();
    void cbTransferState();

    /// @brief Convert current status to string.
    /// @return Status string
    ara::core::String CurrentStatusToString(ara::ucm::TransferStateType status);

    ara::log::Logger& mLogger;

    std::shared_ptr<eevp::ota::vucm::IVehiclePackageManagementListener> listener;

    /// @brief Service Proxy
    std::shared_ptr<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy> mProxy;
    /// @brief FindServiceHandle
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    ara::ucm::TransferStateType transferState;
    ara::core::Vector<ara::ucm::SwNameVersionType> requestedPackageList;

    std::mutex requestMutex;
    std::condition_variable requestCond;
    bool dataReady{false};

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace vucm
} // namespace ota
} // namespace eevp

#endif /// EEVP_OTA_VEHICLE_PACKAGE_MANAGEMENT_PROXY_IMPL_H_