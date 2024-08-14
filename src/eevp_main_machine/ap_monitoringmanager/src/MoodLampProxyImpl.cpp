#include "MoodLampProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::moodlamp;

namespace eevp {
namespace control {
namespace moodlamp {

MoodLampProxyImpl::MoodLampProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "MOOD", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

MoodLampProxyImpl::~MoodLampProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
MoodLampProxyImpl::setEventListener(std::shared_ptr<IMoodLampListener> _listener) {
    listener = _listener;
}

bool
MoodLampProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortMoodLamp");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaMlmProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaMlmProxy StartFindService() Failed";
        return false;
    }

    return true;
}

bool
MoodLampProxyImpl::requestMlmSetRGBColor(const std::uint8_t& colorTableIndex) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }
    mProxy->RequestMlmSetRgbColor(colorTableIndex);

    return true;
}

void
MoodLampProxyImpl::requestMlmSetMode(const eevp::control::SoaMlmMoodMode& mood) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }
    mProxy->RequestMlmSetMode(mood);
}

void
MoodLampProxyImpl::requestMlmSetBrightness(const std::int16_t& brightness) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }
    mProxy->RequestMlmSetBrightness(brightness);
}

bool
MoodLampProxyImpl::getterSoaMlmStatus(eevp::control::SoaMlmStatus& soaMlmStatus) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->soaMlmStatus.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            soaMlmStatus = static_cast<eevp::control::SoaMlmStatus>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaMlmStatus's Getter";
    }

    return false;
}

void
MoodLampProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaMlmProxy::HandleType> container,
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
    mProxy = std::make_shared<proxy::SoaMlmProxy>(container.at(0));

    SubscribeEvent();
    SubscribeField();

    cvHandle.notify_one();
}

void
MoodLampProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;
    // not used
}

void
MoodLampProxyImpl::SubscribeField() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaMlmStatus.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaMlmStatus.SetReceiveHandler(std::bind(&MoodLampProxyImpl::cbSoaMlmStatus, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaMlmStatus with " << result.Error().Message();
    }

    result = mProxy->soaMlmStatus.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for soaMlmStatus with " << result.Error().Message();
    }
}

void
MoodLampProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }
}

void
MoodLampProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaMlmStatus.Unsubscribe();
}

void
MoodLampProxyImpl::cbSoaMlmStatus() {
    mLogger.LogInfo() << "cbSoaMlmStatus";

    eevp::control::SoaMlmStatus fieldValue;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaMlmStatus.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaMlmStatus.GetNewSamples([&](auto msg) {
        fieldValue = static_cast<eevp::control::SoaMlmStatus>(*msg);    // fieldValue = *msg;
        // mLogger.LogInfo() << "cbSoaMlmStatus : " << fieldValue;
        if (listener != nullptr) {
            listener->notifySoaMlmStatus(fieldValue);
        }
    });
}

} /// namespace moodlamp
} /// namespace control
} /// namespace eevp
