#include "PdwProxyImpl.h"

using namespace ara::core;
using namespace eevp::pdw;
using namespace eevp::pdw::type;
using namespace eevp::pdw::service;

namespace eevp {
namespace pdw {

PdwProxyImpl::PdwProxyImpl() :
        mProxy{nullptr},
        mFindHandle{nullptr},
        mHandle{},
        cvHandle{},
    mLogger(ara::log::CreateLogger("MONM", "PDW", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

PdwProxyImpl::~PdwProxyImpl() {
    if (mProxy) {
        mProxy->StopFindService(*mFindHandle);
        mProxy.reset();
    }
}

void
PdwProxyImpl::setEventListener(std::shared_ptr<IPdwListener> _listener) {
    listener = _listener;
}

bool
PdwProxyImpl::init() {
    mLogger.LogInfo() << __func__;

    ara::core::InstanceSpecifier specifier("MonitoringManager/AA/RPortPdw");

    auto callback = [&](auto container, auto findHandle) {
        FindServiceCallback(container, findHandle);
    };

    std::unique_lock<std::mutex> lock(mHandle);

    auto result = proxy::Main_PDW_ServiceProxy::StartFindService(callback, specifier);

    if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout) {
        return false;
    }

    if (!result.HasValue()) {
        mLogger.LogInfo() << "Main_PDW_ServiceProxy StartFindService() Failed";
        return false;
    }

    return true;
}


void
PdwProxyImpl::FindServiceCallback(
        ara::com::ServiceHandleContainer<proxy::Main_PDW_ServiceProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle) {
    mLogger.LogInfo() << __func__;

    std::lock_guard<std::mutex> lock(mHandle);

    int size = container.size();
    mLogger.LogInfo() << "pdw  container size = " << size;

    if (mProxy != nullptr) {
        UnsubscribeEvent();

        mFindHandle = nullptr;
        mProxy = nullptr;
    }

    if (container.empty()) {
        mLogger.LogWarn() << __func__ << "container empty";
        mProxy = nullptr;
        return;
    }

    mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
    mProxy = std::make_shared<proxy::Main_PDW_ServiceProxy>(container.at(0));

    SubscribeEvent();

    cvHandle.notify_one();
}

void
PdwProxyImpl::SubscribeEvent() {
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->DistanceLevel.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed) {
        return;
    }

    auto result = mProxy->DistanceLevel.SetReceiveHandler(std::bind(&PdwProxyImpl::cbDistanceLevel, this));
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to SetReceiveHandler for DistanceLevel with " << result.Error().Message();
    }

    mProxy->DistanceLevel.Subscribe(10);
    if (!result.HasValue()) {
        mLogger.LogWarn() << "Failed to Subscribe for DistanceLevel with " << result.Error().Message();
    }
}


void
PdwProxyImpl::UnsubscribeEvent() {
    if (mProxy == nullptr) {
        return;
    }

    mProxy->DistanceLevel.Unsubscribe();
}



void
PdwProxyImpl::cbDistanceLevel() {
    mLogger.LogInfo() << "cbDistanceLevel";

    if (mProxy == nullptr) {
        return;
    }

    if (mProxy->DistanceLevel.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed) {
        return;
    }

    mProxy->DistanceLevel.GetNewSamples([&](auto msg) {
        eevp::pdw::type::DistanceLevel distanceLevel = static_cast<eevp::pdw::type::DistanceLevel>(*msg);
        if (listener != nullptr) {
            listener->notifyDistanceLevel(distanceLevel);
        }
    });
}



} /// namespace pdw
} /// namespace eevp