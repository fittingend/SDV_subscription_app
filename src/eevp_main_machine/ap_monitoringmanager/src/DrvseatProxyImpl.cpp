#include "DrvseatProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::drvseat;

namespace eevp {
namespace control {
namespace drvseat {

DrvseatProxyImpl::DrvseatProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "DSET", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

DrvseatProxyImpl::~DrvseatProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
DrvseatProxyImpl::setEventListener(std::shared_ptr<IDrvseatListener> _listener) {
    listener = _listener;
}

bool
DrvseatProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortDrvseat");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaDriverSeatProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaDrvseatProxy StartFindService() Failed";
        return false;
    }

    return true;
}


void
DrvseatProxyImpl::getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaDrvSeatDeviceNormal.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaDrvseatDeviceNormal's Getter";
    }
    return;
}

void
DrvseatProxyImpl::getSoaDrvseatSwVersion(std::uint8_t& drvseatSwVersion) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaDrvSeatSwVersion.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            drvseatSwVersion = static_cast<std::uint8_t>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaDrvseatSwVersion's Getter";
    }
    return;
}

void
DrvseatProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaDriverSeatProxy::HandleType> container,
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
    mProxy = std::make_shared<proxy::SoaDriverSeatProxy>(container.at(0));

    SubscribeDrvSeatSwVersion();
    SubscribeDrvSeatDeviceNormal();

    cvHandle.notify_one();
}


void
DrvseatProxyImpl::SubscribeDrvSeatDeviceNormal() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaDrvSeatDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaDrvSeatDeviceNormal.SetReceiveHandler(std::bind(&DrvseatProxyImpl::cbSoaDrvseatIsDeviceNormal, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaDrvseatIsDeviceNormal with " << result.Error().Message();
    }

    result = mProxy->soaDrvSeatDeviceNormal.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaDrvseatIsDeviceNormal with " << result.Error().Message();
    }
}

void
DrvseatProxyImpl::SubscribeDrvSeatSwVersion() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaDrvSeatSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaDrvSeatSwVersion.SetReceiveHandler(std::bind(&DrvseatProxyImpl::cbSoaDrvseatSwVersion, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaDrvseatSwVersion with " << result.Error().Message();
    }

    result = mProxy->soaDrvSeatSwVersion.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaDrvseatSwVersion with " << result.Error().Message();
    }
}

void
DrvseatProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaDrvSeatDeviceNormal.Unsubscribe();
    mProxy->soaDrvSeatSwVersion.Unsubscribe();
}

void
DrvseatProxyImpl::cbSoaDrvseatIsDeviceNormal() {
    mLogger.LogInfo() << "cbSoaDrvseatIsDeviceNormal";
    eevp::control::SoaDeviceIsNormal deviceIsNormal;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaDrvSeatDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaDrvSeatDeviceNormal.GetNewSamples([&](auto msg) {
        deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(*msg);
        if (listener != nullptr) {
            listener->notifySoaDrvseatDeviceNormal(deviceIsNormal);
        }
    });
}


void
DrvseatProxyImpl::cbSoaDrvseatSwVersion() {
    mLogger.LogInfo() << "cbSoaDrvseatSwVersion";

    std::uint8_t drvseatSwVersion;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaDrvSeatSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaDrvSeatSwVersion.GetNewSamples([&](auto msg) {
        drvseatSwVersion = static_cast<std::uint8_t>(*msg);
        if (listener != nullptr) {
            listener->notifySoaDrvseatSwVersion(drvseatSwVersion);
        }
    });
}

} /// namespace drvseat
} /// namespace control
} /// namespace eevp
