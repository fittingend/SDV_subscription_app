#include "data_transfer.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"

using ara::core::Future;
using ara::core::Promise;
using ara::ucm::TransferIdType;

namespace eevp {
namespace ota {

// helper methods
static uint64_t
CalculateBlockCount(uint64_t dataAmountInBytes, uint64_t blockSizeInBytes) {
    uint64_t blockCount = dataAmountInBytes / blockSizeInBytes;
    if (dataAmountInBytes % blockSizeInBytes != 0) {
        blockCount++;
    }
    return blockCount;
}

static void
InitDataBlock(
        const uint64_t startIndex,
        const uint64_t blockSize,
        const std::vector<uint8_t>& data,
        std::vector<uint8_t>& dataBlock) {
    for (uint64_t i = startIndex; i < startIndex + blockSize; i++) {
        if (i < data.size()) {
            dataBlock.push_back(data[i]);
        } else {
            break;
        }
    }
}

template <class VehiclePackageManagementService>
bool
DataTransfer<VehiclePackageManagementService>::InitSession(uint64_t size) {
    auto transferStartResult = vehiclePackageManagementService_->TransferVehiclePackage(size).GetResult();

    if (!transferStartResult) {
        logger_.LogError() << "Error while initializing vehicle package transfer session"
                           << "Error Code:" << transferStartResult.Error();
        return false;
    } else {
        currentSession_ = transferStartResult.Value().id;
        std::string currentSessionStr(std::begin(currentSession_), std::end(currentSession_));
        blockSize_ = transferStartResult.Value().BlockSize;
        logger_.LogInfo() << "InitSession was successful for software package session" << currentSessionStr.c_str()
                          << "with received block size:" << blockSize_;
        return true;
    }
}

template <class VehiclePackageManagementService>
bool
DataTransfer<VehiclePackageManagementService>::InitSession(const ara::core::String& name, const uint64_t size) {
    auto transferStartResult = vehiclePackageManagementService_->TransferStart(name, size).GetResult();

    if (!transferStartResult) {
        logger_.LogError() << "Error while initializing software package transfer session"
                           << "Error Code:" << transferStartResult.Error();
        return false;
    } else {
        currentSession_ = transferStartResult.Value().id;
        std::string currentSessionStr(std::begin(currentSession_), std::end(currentSession_));
        blockSize_ = transferStartResult.Value().BlockSize;
        logger_.LogInfo() << "InitSession was successful for software package session" << currentSessionStr.c_str()
                          << "with received block size:" << blockSize_;
        return true;
    }
}

template <class VehiclePackageManagementService>
bool
DataTransfer<VehiclePackageManagementService>::Transfer(const std::vector<uint8_t>& data) {
    uint64_t blockCount = CalculateBlockCount(data.size(), blockSize_);
    uint64_t blocksSent = 0;

    std::string currentSessionStr(std::begin(currentSession_), std::end(currentSession_));

    while (blocksSent < blockCount) {
        std::vector<uint8_t> dataBlock;
        InitDataBlock(blocksSent * blockSize_, blockSize_, data, dataBlock);

        auto transferDataResult
            = vehiclePackageManagementService_->TransferData(currentSession_, dataBlock, blocksSent + 1).GetResult();
        if (!transferDataResult) {
            logger_.LogError() << "Error while sending data block number" << blocksSent << "in session"
                               << currentSessionStr.c_str() << ". Error:" << transferDataResult.Error().Message();
            return false;
        }
        ++blocksSent;
    }
    logger_.LogInfo() << "Successful transfer of data of size" << data.size() << "with block count" << blocksSent
                      << "in session" << currentSessionStr.c_str();
    return true;
}

template <class VehiclePackageManagementService>
bool
DataTransfer<VehiclePackageManagementService>::ExitSession() {
    auto transferExitResult = vehiclePackageManagementService_->TransferExit(currentSession_).GetResult();

    std::string currentSessionStr(std::begin(currentSession_), std::end(currentSession_));

    if (!transferExitResult) {
        logger_.LogError() << "Error while exiting session" << currentSessionStr.c_str()
                           << ". Error:" << transferExitResult.Error().Message();
        return false;
    }
    logger_.LogInfo() << "Session exited successfully for session" << currentSessionStr.c_str() << ".";
    return true;
}

template <class VehiclePackageManagementService>
TransferIdType
DataTransfer<VehiclePackageManagementService>::GetTransferId() const {
    return currentSession_;
}

template class DataTransfer<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy>;

}  // namespace ota
}  // namespace eevp
