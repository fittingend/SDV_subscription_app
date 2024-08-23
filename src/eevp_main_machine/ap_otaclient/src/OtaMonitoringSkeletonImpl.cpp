#include "OtaMonitoringSkeletonImpl.h"

using namespace eevp::ota;
using namespace eevp::ota::monitoring::service;
using namespace eevp::ota::monitoring::type;

namespace eevp {
namespace ota {
namespace monitoring {

OtaMonitoringSkeletonImpl::OtaMonitoringSkeletonImpl(
                ara::core::InstanceSpecifier instanceSpec,
                ara::com::MethodCallProcessingMode mode) :
        listener{nullptr},
        OtaMonitoringSkeleton(instanceSpec, mode),
        mLogger(ara::log::CreateLogger("OTAC", "MONI", ara::log::LogLevel::kInfo)) {
}

OtaMonitoringSkeletonImpl::~OtaMonitoringSkeletonImpl() {
    StopOfferService();
}

void
OtaMonitoringSkeletonImpl::setEventListener(std::shared_ptr<IOtaMonitoringListener> _listener) {
    listener = _listener;
}

ara::core::Future<skeleton::OtaMonitoringSkeleton::requestServiceInstallOutput>
OtaMonitoringSkeletonImpl::requestServiceInstall(const eevp::type::String& serviceName) {
    skeleton::OtaMonitoringSkeleton::requestServiceInstallOutput response;
    ara::core::Promise<skeleton::OtaMonitoringSkeleton::requestServiceInstallOutput> promise;

    if (listener != nullptr) {
        listener->requestServiceInstall(serviceName);
    }

    response.returnValue = true;
    mLogger.LogInfo() << "[requestServiceInstall] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<skeleton::OtaMonitoringSkeleton::requestServiceUpdateOutput>
OtaMonitoringSkeletonImpl::requestServiceUpdate(const eevp::type::String& serviceName) {
    skeleton::OtaMonitoringSkeleton::requestServiceUpdateOutput response;
    ara::core::Promise<skeleton::OtaMonitoringSkeleton::requestServiceUpdateOutput> promise;

    if (listener != nullptr) {
        listener->requestServiceUpdate(serviceName);
    }

    response.returnValue = true;
    mLogger.LogInfo() << "[requestServiceUpdate] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<skeleton::OtaMonitoringSkeleton::requestVersionInfoOutput>
OtaMonitoringSkeletonImpl::requestVersionInfo() {
    skeleton::OtaMonitoringSkeleton::requestVersionInfoOutput response;
    ara::core::Promise<skeleton::OtaMonitoringSkeleton::requestVersionInfoOutput> promise;

    eevp::ota::monitoring::type::RequestServiceInfoMap serviceInfoMap;
    if (listener != nullptr) {
        listener->requestVersionInfo(serviceInfoMap);
    }

    response.returnValue = true;
    response.requestServiceInfoMap = serviceInfoMap;
    mLogger.LogInfo() << "[requestVersionInfo] : " << response.returnValue;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<skeleton::OtaMonitoringSkeleton::resetUcmTestOutput>
OtaMonitoringSkeletonImpl::resetUcmTest() {
    skeleton::OtaMonitoringSkeleton::resetUcmTestOutput response{};
    ara::core::Promise<skeleton::OtaMonitoringSkeleton::resetUcmTestOutput> promise;

    if (listener != nullptr) {
        listener->resetUcmTest();
    }

    promise.set_value(response);
    return promise.get_future();
}

void
OtaMonitoringSkeletonImpl::sendNotifyServiceEvent(RequestServiceInfo& info) {
    mLogger.LogInfo() << __func__;

#if 0
    skeleton::events::notifyServiceEvent::SampleType data;

    data.serviceName = "dummytest_consumer";
    data.version = "1.0.1";
    data.lastUpdateTime = 1718601691;
    data.actionType = "install";

    mLogger.LogInfo() << "serviceName = "       << data.serviceName     << " / "
                      << "version = "           << data.version         << " / "
                      << "lastUpdateTime = "    << data.lastUpdateDate  << " / "
                      << "actionType = "        << data.actionType;

    notifyServiceEvent.Send(data);
#endif

    notifyServiceEvent.Send(info);
}

void
OtaMonitoringSkeletonImpl::sendNotifyUpdatableService(UpdatableServiceInfo& serviceInfo) {
    mLogger.LogInfo() << __func__;
    notifyUpdatableService.Send(serviceInfo);
}

} /// namespace monitoring
} /// namespace ota
} /// namespace eevp
