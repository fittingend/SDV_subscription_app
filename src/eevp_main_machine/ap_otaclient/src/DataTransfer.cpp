#include "DataTransfer.h"

namespace eevp {
namespace ota {

DataTransfer::DataTransfer() :
        pOtaUtils(nullptr),
        blockSize(0),
        currentSession({0,}),
        mLogger(ara::log::CreateLogger("OTAC", "TRAN", ara::log::LogLevel::kInfo)) {
    pOtaUtils = OtaUtils::getInstance();
}

DataTransfer::~DataTransfer() {
}

void
DataTransfer::setVUCMProxy(std::shared_ptr<eevp::ota::vucm::VehiclePackageManagementProxyImpl> _vucmProxy) {
    vucmProxy = _vucmProxy;
}

bool
DataTransfer::dataTransferVehiclePackage(const ara::core::String& targetManifest) {
    std::vector<uint8_t> buffer;

    if (pOtaUtils->loadBinaryFile(targetManifest, buffer)) {
        mLogger.LogInfo() << __func__ << "buffer size = " << buffer.size();

        if (initSession(buffer.size())) {
            if (transfer(buffer)) {
                return exitSession();
            }
        }
    }
    return false;
}

bool
DataTransfer::dataTransferSoftwarePackage(const ara::core::String packageName, const ara::core::String& targetPackage) {
    std::vector<uint8_t> buffer;

    if (pOtaUtils->loadBinaryFile(targetPackage, buffer)) {
        mLogger.LogInfo() << __func__ << "buffer size = " << buffer.size();

        if (initSession(packageName, buffer.size())) {
            if (transfer(buffer)) {
                return exitSession();
            }
        }
    }
    return false;
}

bool
DataTransfer::initSession(uint64_t size) {
    mLogger.LogInfo() << __func__;

    if (vucmProxy->transferVehiclePackage(size, currentSession, blockSize)) {
        std::string transferId(std::begin(currentSession), std::end(currentSession));
        mLogger.LogInfo() << "VehiclePackage : TransferVehiclePackage TransferID: " << transferId.c_str() << "BlockSize: " << blockSize;
        return true;
    } else {
        mLogger.LogInfo() << "VehiclePackage : TransferVehiclePackage failed";
    }

    return false;
}

bool
DataTransfer::initSession(const ara::core::String& name, const uint64_t size) {
    mLogger.LogInfo() << __func__;

    if (vucmProxy->transferStart(name, currentSession, size, blockSize)) {
        std::string transferId(std::begin(currentSession), std::end(currentSession));
        mLogger.LogInfo() << "VehiclePackage : TransferSoftwarePackage TransferID: " << transferId.c_str() << "BlockSize: " << blockSize;
        return true;
    } else {
        mLogger.LogInfo() << "VehiclePackage : TransferSoftwarePackage failed";
    }

    return false;
}

bool
DataTransfer::transfer(const std::vector<uint8_t>& data) {
    mLogger.LogInfo() << __func__;

    std::uint32_t sentBytes = 0;
    std::uint64_t blockCounter = 1;
    std::uint64_t size = data.size();

    std::uint64_t totalBlockCount = calculateBlockCount(size, blockSize);
    std::uint64_t sentBlockCount = 0;

    while (sentBlockCount < totalBlockCount) {
        std::vector<uint8_t> dataBlock;
        initDataBlock(sentBlockCount * blockSize, blockSize, data, dataBlock);

        if (!vucmProxy->transferData(currentSession, dataBlock, sentBlockCount + 1)) {
            mLogger.LogError() << "TransferData Error";
            currentSession = {0,};
            blockSize = 0;
            return false;
        }
        ++sentBlockCount;
    }

    std::string currentSessionStr(std::begin(currentSession), std::end(currentSession));
    mLogger.LogInfo() << "Successful transfer : data size(" << size << "), block count(" << sentBlockCount
                      << ") in session " << currentSessionStr.c_str();

    return true;
}

bool
DataTransfer::exitSession() {
    mLogger.LogInfo() << __func__;

    std::string currentSessionStr(std::begin(currentSession), std::end(currentSession));

    if (vucmProxy->transferExit(currentSession)) {
        mLogger.LogInfo() << "Session exited successfully for session " << currentSessionStr.c_str() << ".";
        return true;
    }

    mLogger.LogError() << "Error while exiting session" << currentSessionStr.c_str() << ".";
    return false;
}

uint64_t
DataTransfer::calculateBlockCount(uint64_t dataAmountInBytes, uint64_t blockSizeInBytes) {
    uint64_t blockCount = dataAmountInBytes / blockSizeInBytes;
    if (dataAmountInBytes % blockSizeInBytes != 0) {
        blockCount++;
    }
    return blockCount;
}

void
DataTransfer::initDataBlock(
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

} /// namespace ota
} /// namespace eevp
