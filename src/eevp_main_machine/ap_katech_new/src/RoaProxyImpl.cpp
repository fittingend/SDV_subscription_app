#include "RoaProxyImpl.h"
#include "eevp/control/impl_type_soaroadetectstate.h"

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
    mLogger(ara::log::CreateLogger("KATC", "ROA", ara::log::LogLevel::kInfo)) {
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
/*
bool
RoaProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("KATECH/AA/KATEHCH_RPort");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

//    std::unique_lock<std::mutex> lock(mHandle);
    //ok until here

    auto result = proxy::SoaRoaProxy::StartFindService(callback, specifier);
    //이후 execution 이 안됨 
    mLogger.LogInfo() << "sujin";
    

    // if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
    //     return false;
    // }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaRoaProxy StartFindService() Failed";
        return false;
    }

    return true;
}*/
bool
RoaProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("KATECH/AA/KATEHCH_RPort");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);
    //ok until here

    auto ret = proxy::SoaRoaProxy::StartFindService(callback, specifier);
    //이후 execution 이 안됨 
    mLogger.LogInfo() << "sujin";
    if (ret.HasValue()) {
        mLogger.LogInfo() << "SoaRoaProxy Start Find Service Success";
        //mRunning = true;
        return true;
    } else {
        mLogger.LogInfo() << "SoaRoaProxy Start Find Service Failed";
        return false;
    }

    // if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
    //     return false;
    // }

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

    if ((offeredFlag == false)&&(findFlag == true)) {
        mRPort = std::make_unique<eevp::control::proxy::SoaRoaProxy>(proxyHandle);
        mFindHandle = new ara::com::FindServiceHandle(handle);
        mProxyHandle = proxyHandle;
        SubscribeField();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (findFlag == false) {
        mLogger.LogInfo() << "Not available ServiceProvider";
        mRPort = nullptr;
    }
}
/*
void
RoaProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::SoaRoaProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;
    //std::lock_guard<std::mutex> lock(mHandle);
    //TO DO: 뮤텍스 쓰니까 아래 코드 실행이 안됨. 임시적으로 comment out 함

    if (mProxy != nullptr) {
        //UnsubscribeEvent();

        UnsubscribeField();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (container.empty()) {
        mProxy = nullptr;
        mLogger.LogInfo() << "container empty";
        return;
    }
    mLogger.LogInfo() << "123123";

    mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
    mProxy = std::make_shared<proxy::SoaRoaProxy>(container.at(0));

    //SubscribeEvent();
    SubscribeField();

    cvHandle.notify_one();
    mLogger.LogInfo() << "test";

}

*/
/*
void
RoaProxyImpl::SubscribeField() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->soaRoaDetectState.SetReceiveHandler(std::bind(&RoaProxyImpl::cbSoaRoaDetectState, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for cbSoaRoaDetectState with " << result.Error().Message();
    }

    result = mProxy->soaRoaDetectState.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for soaRoaDetectState with " << result.Error().Message();
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
        GetFieldValue();
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
void RoaProxyImpl::GetFieldValue()
{
    mLogger.LogInfo() << "test3";

    if (mRPort->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        mLogger.LogInfo() << "not subscribed";
        return;
    }
    mRPort->soaRoaDetectState.GetNewSamples([&](auto noti){
        /*switch(noti)
        {
            case eevp::control::soaRoaDetectState::kEMPTY:
            mLogger.LogInfo() << "kEMPTY";
            case eevp::control::soaRoaDetectState::kDETECTED_ONCE:
            mLogger.LogInfo() << "kDETECTED_ONCE";
            case eevp::control::soaRoaDetectState::kDETECTED_SEVERAL:
            mLogger.LogInfo() << "kDETECTED_SEVERAL";
            case eevp::control::soaRoaDetectState::kUNKNOWN:
            mLogger.LogInfo() << "kUNKNOWN";
        }*/
        mLogger.LogInfo() << "[FIELD NOTIFICATION]:";
    });
}


void
RoaProxyImpl::UnsubscribeField() {
    mLogger.LogInfo() << __func__;
    if (mProxy == nullptr) {
        return;
    }

    mProxy->soaRoaDetectState.Unsubscribe();
}

void
RoaProxyImpl::cbSoaRoaDetectState() {
    mLogger.LogInfo() << "cbSoaRoaDetectState";

    eevp::control::SoaRoaDetectState fieldValue;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->soaRoaDetectState.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->soaRoaDetectState.GetNewSamples([&](auto msg) {
        fieldValue = static_cast<eevp::control::SoaRoaDetectState>(*msg);   // fieldValue = *msg
        // mLogger.LogInfo() << "cbSoaRctnStatus : " << fieldValue;
        if (listener != nullptr) {
            listener->notifyRoaDetectState(fieldValue);
        }
    });
}

} /// namespace roa
} /// namespace control
} /// namespace eevp
