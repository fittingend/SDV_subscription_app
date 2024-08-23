#ifndef OTA_DATA_TRANSFER_H_
#define OTA_DATA_TRANSFER_H_

#include "ara/log/logger.h"

#include "VehiclePackageManagementProxyImpl.h"

#include "OtaUtils.h"

namespace eevp {
namespace ota {

class DataTransfer {
public:
    DataTransfer();

    ~DataTransfer();

    void setVUCMProxy(std::shared_ptr<eevp::ota::vucm::VehiclePackageManagementProxyImpl> _vucmProxy);

    bool dataTransferVehiclePackage(const ara::core::String& targetManifest);
    bool dataTransferSoftwarePackage(const ara::core::String packageName, const ara::core::String& targetPackage);

private:
    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::ota::vucm::VehiclePackageManagementProxyImpl> vucmProxy;

    eevp::ota::OtaUtils* pOtaUtils;

    bool initSession(uint64_t size);
    bool initSession(const ara::core::String& name, const uint64_t size);

    bool transfer(const std::vector<uint8_t>& data);

    bool exitSession();

    uint64_t calculateBlockCount(uint64_t dataAmountInBytes, uint64_t blockSizeInBytes);
    void initDataBlock(
                const uint64_t startIndex,
                const uint64_t blockSize,
                const std::vector<uint8_t>& data,
                std::vector<uint8_t>& dataBlock);

    ara::ucm::TransferIdType currentSession;
    uint32_t blockSize;
};

} /// namespace ota
} /// namespace eevp

#endif /// OTA_DATA_TRANSFER_H_
