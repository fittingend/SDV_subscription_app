#ifndef EEVP_OTA_DATA_TRANSFER_H_
#define EEVP_OTA_DATA_TRANSFER_H_

#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <ara/vucm/pkgmgr/vehiclepackagemanagement_proxy.h>
#include <ara/log/logger.h>

namespace eevp {
namespace ota {

template <class VehiclePackageManagementService>
class DataTransfer
{
public:
    /// @brief Initializes this object with a reference to the PackageManagement
    /// service
    ///
    /// @param vehiclePackageManagementService The instance of the PackageManagement
    /// service to be used
    explicit DataTransfer(const std::shared_ptr<VehiclePackageManagementService>& vehiclePackageManagementService) :
            vehiclePackageManagementService_(vehiclePackageManagementService),
            blockSize_(0),
//          currentSession_(0),
            logger_(ara::log::CreateLogger("DT", "DataTransfer", ara::log::LogLevel::kVerbose)) {
    }

    ~DataTransfer() = default;

    /// @brief Initializes a new session
    ///
    /// @param size The size of the data that should be transmitted
    ///
    /// @return Boolean indicating whether the session was successfully initiated
    bool InitSession(uint64_t size);

    /// @brief Initializes a new session
    ///
    /// @param name The name of the data that should be transmitted
    ///
    /// @return Boolean indicating whether the session was successfully initiated
    bool InitSession(const ara::core::String& name, const uint64_t size);

    /// @brief Transfers data to UCM sending the provided collection of bytes
    /// to UCM, possibly by using multiple smaller data blocks accoring to the
    /// configured block size.
    ///
    /// @param data The data that should be sent to UCM
    ///
    /// @return Boolean indicating whether the data was successfully sent
    bool Transfer(const std::vector<uint8_t>& data);

    /// @brief Exits the current session
    ///
    /// @return Boolean indicating whether this session was successfully exited
    bool ExitSession();

    /// @brief Returns the session id of the current session.
    ///
    /// @return The id of the current session
    ara::ucm::TransferIdType GetTransferId() const;

private:
    /// @brief The instance of the PackageManagement service used
    std::shared_ptr<VehiclePackageManagementService> vehiclePackageManagementService_;

    /// @brief The configured block size for transmitting data
    uint32_t blockSize_;

    /// @brief The id of the current transfer
    ara::ucm::TransferIdType currentSession_;

    /// @brief For logging errors during transferring.
    ara::log::Logger& logger_;
};

}  // namespace ota
}  // namespace eevp

#endif  // EEVP_OTA_DATA_TRANSFER_H_
