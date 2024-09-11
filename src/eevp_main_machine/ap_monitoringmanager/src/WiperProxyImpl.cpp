#include "WiperProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::wiper;

namespace eevp {
namespace control {
namespace wiper {

WiperProxyImpl::WiperProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "WPER", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

WiperProxyImpl::~WiperProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
WiperProxyImpl::setEventListener(std::shared_ptr<IWiperListener> _listener) {
    listener = _listener;
}

bool
WiperProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortWiper");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaWiperProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaWiperProxy StartFindService() Failed";
        return false;
    }

    return true;
}


void
WiperProxyImpl::getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaWiperDeviceNormal.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaWiperDeviceNormal's Getter";
    }
    return;
}

void
WiperProxyImpl::getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaWiperStatus.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            wiperStatusValue = static_cast<eevp::control::SoaWiperStatus>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaWiperStatus's Getter";
    }
    return;
}

void
WiperProxyImpl::getSoaWiperSwVersion(std::uint8_t& wiperSwVersion) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaWiperSwVersion.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            wiperSwVersion = static_cast<std::uint8_t>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaWiperSwVersion's Getter";
    }
    return;
}

void
WiperProxyImpl::requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    mProxy->RequestWiperOperation(wiperOperationMode);
    return;
}

void
WiperProxyImpl::setWiperAutoSpeed(const bool& isAutoSpeed) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    mProxy->SetWiperAutoSpeed(isAutoSpeed);
    return;
}

void
WiperProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaWiperProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;

    std::lock_guard<std::mutex> lock(mHandle);

    if (mProxy != nullptr) {
        UnsubscribeField();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (container.empty()) {
        mProxy = nullptr;
        return;
    }

    mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
    mProxy = std::make_shared<proxy::SoaWiperProxy>(container.at(0));

    SubscribesoaWiperDeviceNormal();
    SubscribeSoaWiperStatus();
    SubscribeSoaWiperSwVersion();

    cvHandle.notify_one();
}


void
WiperProxyImpl::SubscribesoaWiperDeviceNormal() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaWiperDeviceNormal.SetReceiveHandler(std::bind(&WiperProxyImpl::cbSoaWiperIsDeviceNormal, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaWiperIsDeviceNormal with " << result.Error().Message();
    }

    result = mProxy->soaWiperDeviceNormal.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaWiperIsDeviceNormal with " << result.Error().Message();
    }
}
void
WiperProxyImpl::SubscribeSoaWiperStatus() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperStatus.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaWiperStatus.SetReceiveHandler(std::bind(&WiperProxyImpl::cbSoaWiperStatus, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaWiperStatus with " << result.Error().Message();
    }

    result = mProxy->soaWiperStatus.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaWiperStatus with " << result.Error().Message();
    }
}

void
WiperProxyImpl::SubscribeSoaWiperSwVersion() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaWiperSwVersion.SetReceiveHandler(std::bind(&WiperProxyImpl::cbSoaWiperSwVersion, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaWiperSwVersion with " << result.Error().Message();
    }

    result = mProxy->soaWiperSwVersion.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaWiperSwVersion with " << result.Error().Message();
    }
}

void
WiperProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaWiperDeviceNormal.Unsubscribe();
    mProxy->soaWiperStatus.Unsubscribe();
    mProxy->soaWiperSwVersion.Unsubscribe();
}

void
WiperProxyImpl::cbSoaWiperIsDeviceNormal() {
    mLogger.LogInfo() << "cbSoaWiperIsDeviceNormal";
    eevp::control::SoaDeviceIsNormal deviceIsNormal;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaWiperDeviceNormal.GetNewSamples([&](auto msg) {
        deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(*msg);
        if (listener != nullptr) {
            listener->notifySoaWiperDeviceNormal(deviceIsNormal);
        }
    });
}

void
WiperProxyImpl::cbSoaWiperStatus() {
    mLogger.LogInfo() << "cbSoaWiperStatus";

    eevp::control::SoaWiperStatus wiperStatusValue;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperStatus.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaWiperStatus.GetNewSamples([&](auto msg) {
        wiperStatusValue = static_cast<eevp::control::SoaWiperStatus>(*msg);
        if (listener != nullptr) {
            listener->notifySoaWiperStatus(wiperStatusValue);
        }
    });
}

void
WiperProxyImpl::cbSoaWiperSwVersion() {
    mLogger.LogInfo() << "cbSoaWiperSwVersion";

    std::uint8_t wiperSwVersion;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaWiperSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaWiperSwVersion.GetNewSamples([&](auto msg) {
        wiperSwVersion = static_cast<std::uint8_t>(*msg);
        if (listener != nullptr) {
            listener->notifySoaWiperSwVersion(wiperSwVersion);
        }
    });
}

} /// namespace wiper
} /// namespace control
} /// namespace eevp
