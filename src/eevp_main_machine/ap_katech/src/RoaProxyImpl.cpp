#include "../include/eevp/control/RoaProxyImpl.h"

using namespace ara::core;
using namespace eevp::control;
using namespace eevp::control::roa;

namespace eevp {
namespace control {
namespace roa {

RoaProxyImpl::RoaProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("ROA", "ROA", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

RoaProxyImpl::~RoaProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
RoaProxyImpl::setEventListener(std::shared_ptr<IRoaListener> _listener) {
    listener = _listener;
}

bool
RoaProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("KATECH/AA/KATEHCH_RPort");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaRoaProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaRoaProxy StartFindService() Failed";
        return false;
    }

    return true;
}

bool
RoaProxyImpl::getterSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->soaRoaDetectState.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto soaRoaDetectState = future.GetResult();
        if (soaRoaDetectState.HasValue()) {
            soaRoaDetectState = static_cast<eevp::control::SoaRoaDetectState>(soaRoaDetectState.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << soaRoaDetectState.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRoaDetectState's Getter";
    }

    return false;
}

void
RoaProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaRoaProxy::HandleType> container,
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
    mProxy = std::make_shared<proxy::SoaRoaProxy>(container.at(0));

    SubscribeEvent();
    SubscribeField();

    cvHandle.notify_one();
}

void
RoaProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;
    // not used
}

void
RoaProxyImpl::SubscribeField() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    // auto result = mProxy->soaRoaDetectState.SetReceiveHandler(std::bind(&RoaProxyImpl::cbSoaRctnStatus, this));
    // if (!result.HasValue()) {
    //     mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRctnStatus with " << result.Error().Message();
    // }

    // result = mProxy->soaRoaDetectState.Subscribe(10);
    // if (!result.HasValue()) {
    //     mLogger.LogWarn() << "Failed to Subscribe for soaRoaDetectState with " << result.Error().Message();
    // }
}

void
RoaProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }
}

void
RoaProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaRoaDetectState.Unsubscribe();
}
/*
void
RoaProxyImpl::cbSoaRctnStatus() {
    mLogger.LogInfo() << "cbSoaRctnStatus";

    eevp::control::SoaRctnStatus fieldValue;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRctnStatus.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRctnStatus.GetNewSamples([&](auto msg) {
        fieldValue = static_cast<eevp::control::SoaRctnStatus>(*msg);   // fieldValue = *msg
        // mLogger.LogInfo() << "cbSoaRctnStatus : " << fieldValue;
        if (listener != nullptr) {
            listener->notifySoaRctnStatus(fieldValue);
        }
    });
}
*/
} /// namespace roa
} /// namespace control
} /// namespace eevp
