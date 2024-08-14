#include "OtaMonitoringProxyImpl.h"

using namespace ara::core;
using namespace eevp::monitoring;
using namespace eevp::ota::monitoring::type;
using namespace eevp::ota::monitoring::service;

namespace eevp {
namespace monitoring {

OtaMonitoringProxyImpl::OtaMonitoringProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("SUBM", "OTA", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

OtaMonitoringProxyImpl::~OtaMonitoringProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
OtaMonitoringProxyImpl::setEventListener(std::shared_ptr<IOtaMonitoringListener> _listener) {
    listener = _listener;
}

bool
OtaMonitoringProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortOtaMonitoring");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::OtaMonitoringProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "OtaMonitoringProxy StartFindService() Failed";
        return false;
    }

    return true;
}

bool
OtaMonitoringProxyImpl::requestServiceInstall(const eevp::type::String& serviceName) {
    mLogger.LogInfo() << __func__ << "OTA" << serviceName;

    if (mProxy == nullptr) {
        return false;
    }

    mLogger.LogInfo() << __func__ << "OTA" << serviceName << "1";

    auto future = mProxy->requestServiceInstall(serviceName);

    mLogger.LogInfo() << __func__ << "OTA" << serviceName << "2";
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            return value.returnValue;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestRearCurtainOperation";
    }

    return false;
}

bool
OtaMonitoringProxyImpl::requestServiceUpdate(const eevp::type::String& serviceName) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->requestServiceUpdate(serviceName);
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            return value.returnValue;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestRearCurtainOperation";
    }

    return false;
}

bool
OtaMonitoringProxyImpl::requestVersionInfo(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->requestVersionInfo();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            if (value.returnValue) {
                requestServiceInfoMap = value.requestServiceInfoMap;
            }
            return value.returnValue;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestRearCurtainOperation";
    }

    return false;
}

void
OtaMonitoringProxyImpl::resetUcmTest() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->resetUcmTest();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            mLogger.LogError() << __func__ << " call success";
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call resetUcmTest";
    }
}

void
OtaMonitoringProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::OtaMonitoringProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;

    std::lock_guard<std::mutex> lock(mHandle);

    int size = container.size();
    mLogger.LogInfo() << "otaclient container size = " << size;

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
    mProxy = std::make_shared<proxy::OtaMonitoringProxy>(container.at(0));

    SubscribeEvent();
    SubscribeField();
    cvHandle.notify_one();
}

void
OtaMonitoringProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->notifyServiceEvent.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->notifyServiceEvent.SetReceiveHandler(std::bind(&OtaMonitoringProxyImpl::cbServiceInfoEvent, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for notifyServiceEvent with " << result.Error().Message();
        }

        result = mProxy->notifyServiceEvent.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for notifyServiceEvent with " << result.Error().Message();
        }
    }

    if (mProxy->notifyUpdatableService.GetSubscriptionState() == ara::com::SubscriptionState::kNotSubscribed) {
        auto result = mProxy->notifyUpdatableService.SetReceiveHandler(std::bind(&OtaMonitoringProxyImpl::cbServiceUpdateEvent, this));
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to SetReceiveHandler for notifyUpdatableService with " << result.Error().Message();
        }

        result = mProxy->notifyUpdatableService.Subscribe(10);
        if (!result.HasValue()) {
            mLogger.LogWarn() << "Failed to Subscribe for notifyUpdatableService with " << result.Error().Message();
        }
    }
}

void
OtaMonitoringProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->notifyServiceEvent.Unsubscribe();
    mProxy->notifyUpdatableService.Unsubscribe();
}

void
OtaMonitoringProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }
}

void
OtaMonitoringProxyImpl::cbServiceInfoEvent() {
    mLogger.LogInfo() << "cbServiceInfoEvent";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->notifyServiceEvent.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->notifyServiceEvent.GetNewSamples([&](auto msg) {
        requestServiceInfo = static_cast<RequestServiceInfo>(*msg);
        if (listener != nullptr) {
            listener->notifyServiceEvent(requestServiceInfo);
        }
        mLogger.LogInfo() << requestServiceInfo.serviceName << requestServiceInfo.version << requestServiceInfo.lastUpdateTime;
    });
}

void
OtaMonitoringProxyImpl::cbServiceUpdateEvent() {
    mLogger.LogInfo() << "cbServiceUpdateEvent";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->notifyUpdatableService.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->notifyUpdatableService.GetNewSamples([&](auto msg) {
        updatableServiceInfo = static_cast<UpdatableServiceInfo>(*msg);
        if (listener != nullptr) {
            listener->notifyUpdatableService(updatableServiceInfo);
        }
        mLogger.LogInfo() << updatableServiceInfo.serviceName << updatableServiceInfo.version << updatableServiceInfo.actionType;
    });
}

void
OtaMonitoringProxyImpl::SubscribeField() {
    mLogger.LogInfo() << __func__;
    // not used
}

} /// namespace monitoring
} /// namespace eevp
