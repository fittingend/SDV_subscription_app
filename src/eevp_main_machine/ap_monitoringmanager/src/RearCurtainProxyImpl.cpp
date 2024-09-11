#include "RearCurtainProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::rearcurtain;

namespace eevp {
namespace control {
namespace rearcurtain {

RearCurtainProxyImpl::RearCurtainProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "RCTN", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

RearCurtainProxyImpl::~RearCurtainProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
RearCurtainProxyImpl::setEventListener(std::shared_ptr<IRearCurtainListener> _listener) {
    listener = _listener;
}

bool
RearCurtainProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortRearCurtain");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaRcurtainProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaRcurtainProxy StartFindService() Failed";
        return false;
    }

    return true;
}

eevp::control::SoaErrorState
RearCurtainProxyImpl::requestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return eevp::control::SoaErrorState::kERROR;
    }

    auto future = mProxy->RequestRearCurtainOperation(motorDir);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            return value.err;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestRearCurtainOperation";
    }

    return eevp::control::SoaErrorState::kERROR;

}

void
RearCurtainProxyImpl::requestRearCurtainPosition(const std::uint8_t& posPercentage) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    mProxy->RequestRearCurtainPosition(posPercentage);
    return;
}

bool
RearCurtainProxyImpl::getSoaRctnStatus(eevp::control::SoaRctnStatus& soaRctnStatus) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->soaRctnStatus.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            soaRctnStatus = static_cast<eevp::control::SoaRctnStatus>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRctnStatus's Getter";
    }

    return false;
}

bool
RearCurtainProxyImpl::getSoaRctnSwVersion(std::uint8_t& soaRctnSwVersion) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->soaRctnSwVersion.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            soaRctnSwVersion = static_cast<std::uint8_t>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRctnSwVersion's Getter";
    }

    return false;
}

void
RearCurtainProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaRcurtainProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;

    std::lock_guard<std::mutex> lock(mHandle);

    if (mProxy != nullptr) {
        UnsubscribeEvent();
        UnsubscribeField();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (container.empty()) {
        mProxy = nullptr;
        return;
    }

    mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
    mProxy = std::make_shared<proxy::SoaRcurtainProxy>(container.at(0));

    SubscribeEvent();
    SubscribeRctnStatus();
    SubscribeRctnSwVersion();

    cvHandle.notify_one();
}

void
RearCurtainProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;
    // not used
}

void
RearCurtainProxyImpl::SubscribeRctnStatus() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRctnStatus.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaRctnStatus.SetReceiveHandler(std::bind(&RearCurtainProxyImpl::cbSoaRctnStatus, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRctnStatus with " << result.Error().Message();
    }

    result = mProxy->soaRctnStatus.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for soaRctnStatus with " << result.Error().Message();
    }
}

void
RearCurtainProxyImpl::SubscribeRctnSwVersion() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRctnSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaRctnSwVersion.SetReceiveHandler(std::bind(&RearCurtainProxyImpl::cbSoaRctnSwVersion, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRctnSwVersion with " << result.Error().Message();
    }

    result = mProxy->soaRctnSwVersion.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for soaRctnSwVersion with " << result.Error().Message();
    }
}

void
RearCurtainProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }
}

void
RearCurtainProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaRctnStatus.Unsubscribe();
    mProxy->soaRctnSwVersion.Unsubscribe();
}

void
RearCurtainProxyImpl::cbSoaRctnStatus() {
    mLogger.LogInfo() << "cbSoaRctnStatus";


    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRctnStatus.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRctnStatus.GetNewSamples([&](auto msg) {
        eevp::control::SoaRctnStatus fieldValue = static_cast<eevp::control::SoaRctnStatus>(*msg);   // fieldValue = *msg
        //mLogger.LogInfo() << "cbSoaRctnStatus : " << fieldValue;
        if (listener != nullptr) {
            listener->notifySoaRctnStatus(fieldValue);
        }
    });
}

void
RearCurtainProxyImpl::cbSoaRctnSwVersion() {
    mLogger.LogInfo() << "cbSoaRctnSwVersion";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRctnStatus.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRctnSwVersion.GetNewSamples([&](auto msg) {
        std::uint8_t fieldValue = static_cast<std::uint8_t>(*msg);   // fieldValue = *msg
        mLogger.LogInfo() << "cbSoaRctnSwVersion : " << fieldValue;
        if (listener != nullptr) {
            listener->notifySoaRctnSwVersion(fieldValue);
        }
    });
}

} /// namespace rearcurtain
} /// namespace control
} /// namespace eevp
