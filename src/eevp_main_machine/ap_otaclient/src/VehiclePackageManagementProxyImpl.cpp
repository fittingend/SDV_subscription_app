#include "VehiclePackageManagementProxyImpl.h"

using namespace ara::core;
using namespace ara::vucm::pkgmgr;

namespace eevp {
namespace ota {
namespace vucm {

VehiclePackageManagementProxyImpl::VehiclePackageManagementProxyImpl() :
        listener{nullptr},
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
        transferState{ara::ucm::TransferStateType::kIdle},
        mLogger(ara::log::CreateLogger("OTAC", "VUCM", ara::log::LogLevel::kInfo)) {
}

VehiclePackageManagementProxyImpl::~VehiclePackageManagementProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy = nullptr;
    }
}

void
VehiclePackageManagementProxyImpl::setEventListener(std::shared_ptr<IVehiclePackageManagementListener> _listener) {
    listener = _listener;
}

bool
VehiclePackageManagementProxyImpl::init() {
    ara::core::InstanceSpecifier specifier("OTAClient/AA/VehiclePackageManagement");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::VehiclePackageManagementProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        mLogger.LogInfo() << "VehiclePackageManagementProxy StartFindService() timeout";
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "VehiclePackageManagementProxy StartFindService() Failed";
        return false;
    }

    return true;
}

std::shared_ptr<ara::vucm::pkgmgr::proxy::VehiclePackageManagementProxy>
VehiclePackageManagementProxyImpl::getVehiclePackageManagementProxy() {
    return mProxy;
}

bool
VehiclePackageManagementProxyImpl::allowCampaign() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->AllowCampaign();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call CancelCampaign";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::cancelCampaign(const bool& disableCampaign) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->CancelCampaign(disableCampaign);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call CancelCampaign";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::deleteTransfer(const ara::ucm::TransferIdType& id) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->DeleteTransfer(id);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call DeleteTransfer";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getCampaignHistory(
                const std::uint64_t& timestampGE,
                const std::uint64_t& timestampLT,
                ara::ucm::CampaignHistoryType& campaignHistory) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->GetCampaignHistory(timestampGE, timestampLT);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            campaignHistory = value.CampaignHistory;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call GetCampaignHistory";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getSwClusterInfo(ara::ucm::SwClusterInfoVectorType& swInfo) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->GetSwClusterInfo();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            swInfo = value.SwInfo;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call GetSwClusterInfo";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getSwPackages(ara::ucm::SwPackageInfoVectorType& packages) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->GetSwPackages();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            packages = value.Packages;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call GetSwPackages";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::swPackageInventory(
                const ara::ucm::SwNameVersionVectorType& availableSoftwarePackages,
                ara::ucm::SwNameVersionVectorType& requiredSoftwarePackages) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->SwPackageInventory(availableSoftwarePackages);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            requiredSoftwarePackages = value.RequiredSoftwarePackages;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call SwPackageInventory";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::transferData(
                const ara::ucm::TransferIdType& id,
                const ara::ucm::ByteVectorType& data,
                const std::uint64_t& blockCounter) {
    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->TransferData(id, data, blockCounter);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call TransferData";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::transferExit(const ara::ucm::TransferIdType& id) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->TransferExit(id);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call TransferExit";
    }

    transferState = ara::ucm::TransferStateType::kIdle;
    return false;
}

bool
VehiclePackageManagementProxyImpl::transferStart(
                const ara::ucm::SwNameType& softwarePackageName,
                ara::ucm::TransferIdType& id,
                const std::uint64_t& size,
                std::uint32_t& blockSize) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->TransferStart(softwarePackageName, size);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            id = value.id;
            blockSize = value.BlockSize;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call TransferStart";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::transferVehiclePackage(
                const std::uint64_t& size,
                ara::ucm::TransferIdType& id,
                std::uint32_t& blockSize) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    requestedPackageList.clear();
    dataReady = false;

    mLogger.LogInfo() << __func__ << "size = " << size;

    auto future = mProxy->TransferVehiclePackage(size);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            id = value.id;
            blockSize = value.BlockSize;
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call TransferVehiclePackage";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getterRequestedPackage(ara::ucm::SwNameVersionType& requestedPackage) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->RequestedPackage.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            requestedPackage = static_cast<ara::ucm::SwNameVersionType>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestedPackage's Getter";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getterSafetyState(bool& safetyState) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->SafetyState.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            safetyState = static_cast<bool>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call SafetyState's Getter";
    }

    return false;
}

bool
VehiclePackageManagementProxyImpl::getterTransferState(ara::ucm::TransferStateType& transferState) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->TransferState.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            transferState = static_cast<ara::ucm::TransferStateType>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call TransferState's Getter";
    }

    return false;
}

ara::ucm::TransferStateType
VehiclePackageManagementProxyImpl::getTransferState() {
    mLogger.LogInfo() << __func__ << CurrentStatusToString(transferState);
    return transferState;
}

ara::core::Vector<ara::ucm::SwNameVersionType>
VehiclePackageManagementProxyImpl::getRequestedPackageList() {
    std::unique_lock<std::mutex> lck(requestMutex);
    if (requestedPackageList.empty()) {
        requestCond.wait(lck, [this] { return dataReady; });
    }
    return requestedPackageList;
}

void
VehiclePackageManagementProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::VehiclePackageManagementProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    std::lock_guard<std::mutex> lock(mHandle);

    if (mProxy != nullptr) {
        UnsubscribeEvent();
        UnsubscribeField();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (!container.empty()) {
        mLogger.LogInfo() << "VehiclePackageManagementProxy Start Find Service Success";

        mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
        mProxy = std::make_shared<proxy::VehiclePackageManagementProxy>(container.at(0));

        SubscribeEvent();
        SubscribeField();

        cvHandle.notify_one();
    }
}

void
VehiclePackageManagementProxyImpl::SubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }
}

void
VehiclePackageManagementProxyImpl::SubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->RequestedPackage.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->RequestedPackage.SetReceiveHandler(std::bind(&VehiclePackageManagementProxyImpl::cbRequestedPackage, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for RequestedPackage with " << result.Error().Message();
        }

        result = mProxy->RequestedPackage.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for RequestedPackage with " << result.Error().Message();
        }
    }

    if (mProxy->SafetyState.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->SafetyState.SetReceiveHandler(std::bind(&VehiclePackageManagementProxyImpl::cbSafetyState, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for SafetyState with " << result.Error().Message();
        }

        result = mProxy->SafetyState.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for SafetyState with " << result.Error().Message();
        }
    }

    if (mProxy->TransferState.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->TransferState.SetReceiveHandler(std::bind(&VehiclePackageManagementProxyImpl::cbTransferState, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for TransferState with " << result.Error().Message();
        }

        result = mProxy->TransferState.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for TransferState with " << result.Error().Message();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void
VehiclePackageManagementProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }
}

void
VehiclePackageManagementProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->RequestedPackage.Unsubscribe();
    mProxy->SafetyState.Unsubscribe();
    mProxy->TransferState.Unsubscribe();
}

void
VehiclePackageManagementProxyImpl::cbRequestedPackage() {
    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->RequestedPackage.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    ara::ucm::SwNameVersionType requestedPackage;

    std::unique_lock<std::mutex> lck(requestMutex);

    mProxy->RequestedPackage.GetNewSamples([&](auto msg) {
        requestedPackage = static_cast<ara::ucm::SwNameVersionType>(*msg);

        if (requestedPackage.Name.size() > 0) {
            mLogger.LogInfo() << __func__ << "(" << requestedPackage.Name << ":" << requestedPackage.Version << ")";

            std::size_t last_path_separator_position(requestedPackage.Name.find_last_of("/"));
            if (last_path_separator_position != ara::core::String::npos) {
                requestedPackage.Name
                    = requestedPackage.Name.substr(last_path_separator_position + 1, ara::core::String::npos);
            }
            requestedPackageList.push_back(requestedPackage);
            if (listener != nullptr) {
                listener->notifyRequestedPackage(requestedPackage);
            }
        }
        dataReady = true;
    });

    lck.unlock();
    requestCond.notify_one();
}

void
VehiclePackageManagementProxyImpl::cbSafetyState() {
    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->SafetyState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    bool safetyState;

    mProxy->SafetyState.GetNewSamples([&](auto msg) {
        safetyState = static_cast<bool>(*msg);
        mLogger.LogInfo() << "cbSafetyState" << "(" << (safetyState ? "true" : "false") << ")";
        if (listener != nullptr) {
            listener->notifySafetyState(safetyState);
        }
    });
}

void
VehiclePackageManagementProxyImpl::cbTransferState() {
    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->TransferState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->TransferState.GetNewSamples([&](auto msg) {
        transferState = static_cast<ara::ucm::TransferStateType>(*msg);
        mLogger.LogInfo() << "cbTransferState" << "(" << CurrentStatusToString(transferState) << ")";
        if (listener != nullptr) {
            listener->notifyTransferState(transferState);
        }
    });
}

ara::core::String
VehiclePackageManagementProxyImpl::CurrentStatusToString(ara::ucm::TransferStateType status) {
    switch (status) {
        case ara::ucm::TransferStateType::kIdle:
            return "Idle";
        case ara::ucm::TransferStateType::kTransferring:
            return "Transferring";
        case ara::ucm::TransferStateType::kUpdating:
            return "Updating";
        case ara::ucm::TransferStateType::kCancelling:
            return "Cancelling";
        default:
            return "Unknown";
    }
}

} /// namespace vucm
} /// namespace ota
} /// namespace eevp
