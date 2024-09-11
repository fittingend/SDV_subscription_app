#include "RoaProxyImpl.h"

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
    mLogger(ara::log::CreateLogger("MONM", "ROA", ara::log::LogLevel::kInfo)) {
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

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortRoa");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::SoaRoaProxy::StartFindService(callback, specifier);
    mLogger.LogInfo() << "sujin-test";

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaRoaProxy StartFindService() Failed";
        return false;
    }

    return true;
}


void
RoaProxyImpl::getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaRoaDeviceNormal.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(result.Value());
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRoaDeviceNormal's Getter";
    }
    return;
}

void
RoaProxyImpl::getSoaRoaSwVersion(std::uint8_t& roaSwVersion) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    auto future = mProxy->soaRoaSwVersion.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            roaSwVersion = static_cast<std::uint8_t>(result.Value());
            mLogger.LogInfo() << "roaSwVersion:" << roaSwVersion;

        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRoaSwVersion's Getter";
    }
    return;
}


bool
RoaProxyImpl::getSoaRoaDetectState(eevp::control::SoaRoaDetectState& soaRoaDetectState) {
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

bool
RoaProxyImpl::getSoaRoaDetectCount(uint8_t& soaRoaDetectCount) {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return false;
    }

    auto future = mProxy->soaRoaDetectCount.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            soaRoaDetectCount =result.Value();
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call soaRoaDetectCount's Getter";
    }

    return false;
}
/*
void RoaProxyImpl::FindServiceCallback(ara::com::ServiceHandleContainer<proxy::SoaRoaProxy::HandleType> services, ara::com::FindServiceHandle handle)
{
    proxy::SoaRoaProxy::HandleType proxyHandle;
    bool findFlag = false;
    bool offeredFlag = false;
    mLogger.LogInfo() << "Current offered service list";
    for (auto service : services)
    {   
        mLogger.LogInfo() 
            << "ServiceID : " << service.GetServiceHandle().serviceId
            << "InstanceID : " << service.GetServiceHandle().instanceId
            << "MajorVersion : "<< service.GetServiceHandle().version.major
            << "MinorVesion : " << service.GetServiceHandle().version.minor ;
        if (service.GetServiceHandle().serviceId != 4947) {
            continue;
        }
        if (service.GetServiceHandle().version.major != 1) {
            continue;
        }
        if (mProxyHandle == service) {
            offeredFlag = true;
        }
        findFlag = true;
        proxyHandle = service;
    }
    std::lock_guard<std::mutex> lock(mHandle);

    if ((offeredFlag == false)&&(findFlag == true)) {
        mRPort = std::make_unique<eevp::control::proxy::SoaRoaProxy>(proxyHandle);
        mFindHandle = std::make_shared<ara::com::FindServiceHandle>(handle);
        //mFindHandle = new ara::com::FindServiceHandle(handle);
        mProxyHandle = proxyHandle;
        SubscribeField();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mLogger.LogInfo() << "SubscribeField end";


    }
    if (findFlag == false) {
        mLogger.LogInfo() << "Not available ServiceProvider";
        mRPort = nullptr;
    }
}
*/
void RoaProxyImpl::SubscribeField()
{

    if (mRPort->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        mLogger.LogInfo() << "test1";
        return;
    }
    auto fieldCallback = [&](auto state) {
        mLogger.LogInfo() << "test2";
        StateChangeCallback("soaRoaDetectState", state);
    };
    mRPort->soaRoaDetectState.SetSubscriptionStateChangeHandler(fieldCallback);
    auto receiveEvent = [&] () {
        mLogger.LogInfo() << "test22";
        //GetFieldValue();
    };
    mLogger.LogInfo() << "test21";
    mRPort->soaRoaDetectState.SetReceiveHandler(receiveEvent);
    mRPort->soaRoaDetectState.Subscribe(10);

}

void RoaProxyImpl::StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state) 
{
    switch (state)
    {
    case ara::com::SubscriptionState::kNotSubscribed : 
        mLogger.LogInfo() << callsign<< " : state changed to kNotSubscribed";
        break;
    case ara::com::SubscriptionState::kSubscriptionPending : 
        mLogger.LogInfo() << callsign<< " : state changed to kSubscriptionPending";
        break;
    case ara::com::SubscriptionState::kSubscribed : 
        mLogger.LogInfo() << callsign<< " : state changed to kSubscribed";
        break;
    default:
        mLogger.LogError() << callsign<< " : not allowed state";
        break;
    }
}

void
RoaProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaRoaProxy::HandleType> container,
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
    mProxy = std::make_shared<proxy::SoaRoaProxy>(container.at(0));

    SubscribeRoaSwVersion();
    SubscribeRoaDeviceNormal();
   // GetFieldValue();

    cvHandle.notify_one();
}

// void RoaProxyImpl::GetFieldValue()
// {
//     mLogger.LogInfo() << "test3";

//     if (mRPort->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
//         mLogger.LogInfo() << "not subscribed";
//         return;
//     }
//     mRPort->soaRoaDetectState.GetNewSamples([&](auto noti){
//         noti=static_cast<eevp::control::SoaDeviceIsNormal>(*noti);

//         if (noti == eevp::control::SoaRoaDetectState::kEMPTY){
//             mLogger.LogInfo() << "kEMPTY";
//         }
//         if (noti == eevp::control::SoaRoaDetectState::kDETECTED_ONCE){
//             mLogger.LogInfo() << "kDETECTED_ONCE";
//         }
//         if (noti == eevp::control::SoaRoaDetectState::kDETECTED_SEVERAL){
//             mLogger.LogInfo() << "kDETECTED_SEVERAL";
//         }
//     });
// }
void
RoaProxyImpl::SubscribeRoaDeviceNormal() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        mLogger.LogInfo() << "not subscribed";

        return;
    }

    auto result = mProxy->soaRoaDeviceNormal.SetReceiveHandler(std::bind(&RoaProxyImpl::cbSoaRoaIsDeviceNormal, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRoaIsDeviceNormal with " << result.Error().Message();
    }

    result = mProxy->soaRoaDeviceNormal.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaRoaIsDeviceNormal with " << result.Error().Message();
    }
}

void
RoaProxyImpl::SubscribeRoaSwVersion() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        mLogger.LogInfo() << "not subscribed";

        return;
    }

    auto result = mProxy->soaRoaSwVersion.SetReceiveHandler(std::bind(&RoaProxyImpl::cbSoaRoaSwVersion, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRoaSwVersion with " << result.Error().Message();
    }

    result = mProxy->soaRoaSwVersion.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for cbSoaRoaSwVersion with " << result.Error().Message();
    }
}

void
RoaProxyImpl::UnsubscribeField() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaRoaDeviceNormal.Unsubscribe();
    mProxy->soaRoaSwVersion.Unsubscribe();
}

void
RoaProxyImpl::cbSoaRoaIsDeviceNormal() {
    mLogger.LogInfo() << "cbSoaRoaIsDeviceNormal";
    eevp::control::SoaDeviceIsNormal deviceIsNormal;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaDeviceNormal.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRoaDeviceNormal.GetNewSamples([&](auto msg) {
        deviceIsNormal = static_cast<eevp::control::SoaDeviceIsNormal>(*msg);
        if (listener != nullptr) {
            listener->notifySoaRoaDeviceNormal(deviceIsNormal);
        }
    });
}


void
RoaProxyImpl::cbSoaRoaSwVersion() {
    mLogger.LogInfo() << "cbSoaRoaSwVersion";

    std::uint8_t roaSwVersion;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaSwVersion.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRoaSwVersion.GetNewSamples([&](auto msg) {
        roaSwVersion = static_cast<std::uint8_t>(*msg);
        if (listener != nullptr) {
            listener->notifySoaRoaSwVersion(roaSwVersion);
        }
    });
}

} /// namespace roa
} /// namespace control
} /// namespace eevp
