#include "StateManagerProxyImpl.h"

using namespace ara::core;
using namespace ivi::info::statemanager;
using namespace ivi::info::statemanager::type;
using namespace ivi::info::statemanager::service;

namespace ivi {
namespace info {
namespace statemanager {

StateManagerProxyImpl::StateManagerProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "IVSM", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

StateManagerProxyImpl::~StateManagerProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
StateManagerProxyImpl::setEventListener(std::shared_ptr<IStateManagerListener> _listener) {
    listener = _listener;
}

bool
StateManagerProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortStateManager");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::StateManagerProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "StateManagerProxy StartFindService() Failed";
        return false;
    }

    return true;
}

bool
StateManagerProxyImpl::getterNotifyTime(std::uint8_t& notifyTime) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->NotifyTime.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            notifyTime = static_cast<std::uint8_t>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call NotifyTime's Getter";
    }

    return false;
}

bool
StateManagerProxyImpl::getterSystemState(State& systemState) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->SystemState.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            systemState = static_cast<State>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call SystemState's Getter";
    }

    return false;
}

bool
StateManagerProxyImpl::setterNotifyTime(const std::uint8_t& notifyTime) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->NotifyTime.Set(notifyTime);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            return result.Value();
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call NotifyTime's Setter";
    }
}

void
StateManagerProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::StateManagerProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;

    std::lock_guard<std::mutex> lock(mHandle);

    int size = container.size();
    mLogger.LogInfo() << "statemanager container size = " << size;

    if (mProxy != nullptr) {
        UnsubscribeEvent();
        UnsubscribeField();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (container.empty()) {
        mLogger.LogWarn() << __func__ << "container empty";
        mProxy = nullptr;
        return;
    }

    mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
    mProxy = std::make_shared<proxy::StateManagerProxy>(container.at(0));

    SubscribeEvent();
    SubscribeField();

    cvHandle.notify_one();
}

void
StateManagerProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->NotifySystemState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->NotifySystemState.SetReceiveHandler(std::bind(&StateManagerProxyImpl::cbNotifySystemState, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for NotifySystemState with " << result.Error().Message();
    }

    mProxy->NotifySystemState.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for NotifySystemState with " << result.Error().Message();
    }
}

void
StateManagerProxyImpl::SubscribeField() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->NotifyTime.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->NotifyTime.SetReceiveHandler(std::bind(&StateManagerProxyImpl::cbNotifyTime, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for NotifyTime with " << result.Error().Message();
        }

        mProxy->NotifyTime.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for NotifyTime with " << result.Error().Message();
        }
    }

    if (mProxy->SystemState.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->SystemState.SetReceiveHandler(std::bind(&StateManagerProxyImpl::cbSystemState, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for SystemState with " << result.Error().Message();
        }

        mProxy->SystemState.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for SystemState with " << result.Error().Message();
        }
    }
}

void
StateManagerProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->NotifySystemState.Unsubscribe();
}

void
StateManagerProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->NotifyTime.Unsubscribe();
    mProxy->SystemState.Unsubscribe();
}

void
StateManagerProxyImpl::cbNotifySystemState() {
    mLogger.LogInfo() << "cbNotifySystemState";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->NotifySystemState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->NotifySystemState.GetNewSamples([&](auto msg) {
        State notifySystemState = static_cast<State>(*msg);
        if (listener != nullptr) {
            listener->notifyNotifySystemState(notifySystemState);
        }
    });
}

void
StateManagerProxyImpl::cbNotifyTime() {
    mLogger.LogInfo() << "cbNotifyTime";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->NotifyTime.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->NotifyTime.GetNewSamples([&](auto msg) {
        std::uint32_t notifyTime = static_cast<std::uint8_t>(*msg);
        if (listener != nullptr) {
            listener->notifyNotifyTime(notifyTime);
        }
    });
}

void
StateManagerProxyImpl::cbSystemState() {
    mLogger.LogInfo() << "cbSystemState";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->SystemState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->SystemState.GetNewSamples([&](auto msg) {
        State systemState = static_cast<State>(*msg);
        if (listener != nullptr) {
            listener->notifySystemState(systemState);
            mLogger.LogInfo() << "callback system state" << static_cast<uint8_t>(systemState);
        }
    });
}

} /// namespace statemanager
} /// namespace info
} /// namespace monitoring