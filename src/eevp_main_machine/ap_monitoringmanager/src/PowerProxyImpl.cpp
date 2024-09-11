#include "PowerProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::power;

namespace eevp {
namespace control {
namespace power {

PowerProxyImpl::PowerProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "PWER", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

PowerProxyImpl::~PowerProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
PowerProxyImpl::setEventListener(std::shared_ptr<IPowerListener> _listener) {
    listener = _listener;
}

bool
PowerProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortPower");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaPowerProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaPowerProxy StartFindService() Failed";
        return false;
    }

    return true;
}


void
PowerProxyImpl::getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaPowerDeviceNormal.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaPowerDeviceNormal's Getter";
    }
    return;
}

void
PowerProxyImpl::getSoaPowerSwVersion(std::uint8_t& powerSwVersion) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaPowerSwVersion.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            powerSwVersion = static_cast<std::uint8_t>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaPowerSwVersion's Getter";
    }
    return;
}

void
PowerProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaPowerProxy::HandleType> container,
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
    mProxy = std::make_shared<proxy::SoaPowerProxy>(container.at(0));

    SubscribePowerSwVersion();
    SubscribePowerDeviceNormal();

    cvHandle.notify_one();
}


void
PowerProxyImpl::SubscribePowerDeviceNormal() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaPowerDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaPowerDeviceNormal.SetReceiveHandler(std::bind(&PowerProxyImpl::cbSoaPowerIsDeviceNormal, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaPowerIsDeviceNormal with " << result.Error().Message();
    }

    result = mProxy->soaPowerDeviceNormal.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaPowerIsDeviceNormal with " << result.Error().Message();
    }
}

void
PowerProxyImpl::SubscribePowerSwVersion() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaPowerSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaPowerSwVersion.SetReceiveHandler(std::bind(&PowerProxyImpl::cbSoaPowerSwVersion, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaPowerSwVersion with " << result.Error().Message();
    }

    result = mProxy->soaPowerSwVersion.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaPowerSwVersion with " << result.Error().Message();
    }
}

void
PowerProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaPowerDeviceNormal.Unsubscribe();
    mProxy->soaPowerSwVersion.Unsubscribe();
}

void
PowerProxyImpl::cbSoaPowerIsDeviceNormal() {
    mLogger.LogInfo() << "cbSoaPowerIsDeviceNormal";
    eevp::control::SoaDeviceIsNormal deviceIsNormal;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaPowerDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaPowerDeviceNormal.GetNewSamples([&](auto msg) {
        deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(*msg);
        if (listener != nullptr) {
            listener->notifySoaPowerDeviceNormal(deviceIsNormal);
        }
    });
}


void
PowerProxyImpl::cbSoaPowerSwVersion() {
    mLogger.LogInfo() << "cbSoaPowerSwVersion";

    std::uint8_t powerSwVersion;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaPowerSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaPowerSwVersion.GetNewSamples([&](auto msg) {
        powerSwVersion = static_cast<std::uint8_t>(*msg);
        if (listener != nullptr) {
            listener->notifySoaPowerSwVersion(powerSwVersion);
        }
    });
}

} /// namespace power
} /// namespace control
} /// namespace eevp
