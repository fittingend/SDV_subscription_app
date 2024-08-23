#include "OtaSubscriptionSkeletonImpl.h"

using namespace eevp::ota;
using namespace eevp::ota::subscription::service;
using namespace eevp::ota::subscription::type;

namespace eevp {
namespace ota {
namespace subscription {

OtaSubscriptionSkeletonImpl::OtaSubscriptionSkeletonImpl(
                ara::core::InstanceSpecifier instanceSpec,
                ara::com::MethodCallProcessingMode mode) :
        listener{nullptr},
        OtaSubscriptionSkeleton(instanceSpec, mode),
        mLogger(ara::log::CreateLogger("OTAC", "SUBS", ara::log::LogLevel::kInfo)) {
}

OtaSubscriptionSkeletonImpl::~OtaSubscriptionSkeletonImpl() {
    StopOfferService();
}

void
OtaSubscriptionSkeletonImpl::setEventListener(std::shared_ptr<IOtaSubscriptionListener> _listener) {
    listener = _listener;
}

ara::core::Future<skeleton::OtaSubscriptionSkeleton::requestAppInstallOutput>
OtaSubscriptionSkeletonImpl::requestAppInstall(const eevp::type::String& appName) {
    skeleton::OtaSubscriptionSkeleton::requestAppInstallOutput response;
    ara::core::Promise<skeleton::OtaSubscriptionSkeleton::requestAppInstallOutput> promise;

    if (listener != nullptr) {
        listener->requestAppInstall(appName);
    }

    response.returnValue = true;
    mLogger.LogInfo() << "[requestServiceInstall] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<skeleton::OtaSubscriptionSkeleton::requestAppUpdateOutput>
OtaSubscriptionSkeletonImpl::requestAppUpdate(const eevp::type::String& appName) {
    skeleton::OtaSubscriptionSkeleton::requestAppUpdateOutput response;
    ara::core::Promise<skeleton::OtaSubscriptionSkeleton::requestAppUpdateOutput> promise;

    if (listener != nullptr) {
        listener->requestAppUpdate(appName);
    }

    response.returnValue = true;
    mLogger.LogInfo() << "[requestServiceUpdate] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<skeleton::OtaSubscriptionSkeleton::requestVersionInfoOutput>
OtaSubscriptionSkeletonImpl::requestVersionInfo() {
    skeleton::OtaSubscriptionSkeleton::requestVersionInfoOutput response;
    ara::core::Promise<skeleton::OtaSubscriptionSkeleton::requestVersionInfoOutput> promise;

    eevp::ota::subscription::type::RequestAppInfoMap appInfoMap;
    if (listener != nullptr) {
        listener->requestVersionInfo(appInfoMap);
    }

    response.returnValue = true;
    response.requestAppInfoMap = appInfoMap;
    mLogger.LogInfo() << "[requestVersionInfo] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

void
OtaSubscriptionSkeletonImpl::sendNotifyAppEvent(RequestAppInfo& info) {
#if 0
    skeleton::events::notifyAppEvent::SampleType data;

    data.appName = "appName";
    data.version = "1.0.0";
    data.lastUpdateDate = "2024.05.22";

    mLogger.LogInfo() << "[sendNotifyAppEvent] ("
                      << data.appName << ":"
                      << data.version << ":"
                      << data.lastUpdateDate << ")";

    notifyAppEvent.Send(data);
#endif

    notifyAppEvent.Send(info);
}

void
OtaSubscriptionSkeletonImpl::sendNotifyUpdatableApp(UpdatableAppInfo& appInfo) {
    mLogger.LogInfo() << __func__;
    notifyUpdatableApp.Send(appInfo);
}

} /// namespace subscription
} /// namespace ota
} /// namespace eevp
