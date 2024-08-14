#include "MonitoringManagementSkeletonImpl.h"

using namespace ara::core;
using namespace eevp::monitoring;
using namespace eevp::monitoring::type;
using namespace eevp::monitoring::service;

namespace eevp {
namespace monitoring {

MonitoringManagementSkeletonImpl::MonitoringManagementSkeletonImpl(
                InstanceSpecifier instanceSpec,
                ara::com::MethodCallProcessingMode mode) :
        listener{nullptr},
        MonitoringManagementSkeleton(instanceSpec, mode),
    mLogger(ara::log::CreateLogger("MONM", "MGR", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;
}

MonitoringManagementSkeletonImpl::~MonitoringManagementSkeletonImpl() {
    StopOfferService();
}

void
MonitoringManagementSkeletonImpl::setEventListener(std::shared_ptr<IMonitoringManagementListener> _listener) {
    listener = _listener;
}

Future<skeleton::MonitoringManagementSkeleton::requestAppInstallOutput>
MonitoringManagementSkeletonImpl::requestAppInstall(const eevp::type::String& controllerServiceName) {
    mLogger.LogInfo() << __func__;

    skeleton::MonitoringManagementSkeleton::requestAppInstallOutput response;
    Promise<skeleton::MonitoringManagementSkeleton::requestAppInstallOutput> promise;

    if (listener != nullptr) {
        response.returnValue = listener->requestAppInstall(controllerServiceName);
    }

    promise.set_value(response);
    return promise.get_future();
}


Future<skeleton::MonitoringManagementSkeleton::requestAppUpdateOutput>
MonitoringManagementSkeletonImpl::requestAppUpdate(const eevp::type::String& controllerServiceName) {
    mLogger.LogInfo() << __func__;

    eevp::monitoring::service::skeleton::MonitoringManagementSkeleton::requestAppUpdateOutput response;
    ara::core::Promise<requestAppUpdateOutput> promise;

    if (listener != nullptr) {
        response.returnValue = listener->requestAppUpdate(controllerServiceName);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceInfoOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceInfo(const eevp::type::String& controllerServiceName) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceInfoOutput response;
    ara::core::Promise<requestControllerServiceInfoOutput> promise;

    bool retVal = false;
    eevp::monitoring::type::ControllerServiceInfo serviceInfo;

    if (listener != nullptr) {
        retVal = listener->requestControllerServiceInfo(controllerServiceName, serviceInfo);
    }

    if (retVal) {
        response.controllerServiceInfo = serviceInfo;
        response.returnValue = retVal;
    } else {
        response.controllerServiceInfo = serviceInfo;
        response.returnValue = retVal;
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceStatusOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceStatus(const eevp::type::String& controllerServiceName) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceStatusOutput response;
    Promise<requestControllerServiceStatusOutput> promise;
    bool retVal;
    eevp::type::String status;

    if (listener != nullptr) {
        retVal = listener->requestControllerServiceStatus(controllerServiceName, status);
    }

    response.controllerServiceStatus = status;
    response.returnValue = retVal;

    if (controllerServiceName == "RearCurtain" || controllerServiceName == "MoodLamp") {
        mLogger.LogInfo () << "[requestControllerServiceStatus] ("
                            << controllerServiceName << ":"
                            << response.controllerServiceStatus << ":"
                            << response.returnValue << ")";
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::setEnableControllerServiceOutput>
MonitoringManagementSkeletonImpl::setEnableControllerService(
                const eevp::type::String& controllerServiceName,
                const eevp::type::String& enable) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::setEnableControllerServiceOutput response;
    Promise<setEnableControllerServiceOutput> promise;

    if (listener != nullptr) {
       response.returnValue = listener->setEnableControllerService(controllerServiceName, enable);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceInfoAllSpareOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceInfoAllSpare() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceInfoAllSpareOutput response;
    Promise<requestControllerServiceInfoAllSpareOutput> promise;

    bool retVal = false;
    eevp::monitoring::type::StringArray serviceName;
    eevp::monitoring::type::StringArray version;
    eevp::monitoring::type::TimeArray lastUpdateTime;

    if (listener != nullptr) {
        retVal = listener->requestControllerServiceInfoAllSpare(serviceName, version, lastUpdateTime);
    }

    if (retVal) {
        response.serviceName = serviceName;
        response.version = version;
        response.lastUpdateTime = lastUpdateTime;
    } else {
        response.serviceName = {"error"};
        response.version = {"error"};
        response.lastUpdateTime = {0};
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceStatusAllSpareOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceStatusAllSpare() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceStatusAllSpareOutput response;
    Promise<requestControllerServiceStatusAllSpareOutput> promise;

    bool retVal = false;
    eevp::monitoring::type::StringArray serviceName;
    eevp::monitoring::type::StringArray serviceStatus;
    eevp::monitoring::type::StringArray serviceEnable;
    eevp::monitoring::type::StringArray serviceControl;

    if (listener != nullptr) {
       retVal = listener->requestControllerServiceStatusAllSpare(
                    serviceName,
                    serviceStatus,
                    serviceEnable,
                    serviceControl);
    }

    if (retVal) {
        response.serviceName = serviceName;
        response.serviceStatus = serviceStatus;
        response.serviceEnable = serviceEnable;
        response.serviceControl = serviceControl;
    } else {
        response.serviceName = {"error"};
        response.serviceStatus = {"error"};
        response.serviceEnable = {"error"};
        response.serviceControl = {"error"};
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::setControlControllerServiceOutput>
MonitoringManagementSkeletonImpl::setControlControllerService(
                const eevp::type::String& serviceName,
                const eevp::type::String& serviceControl) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::setControlControllerServiceOutput response;
    Promise<setControlControllerServiceOutput> promise;

    if (listener != nullptr) {
        response.returnValue = listener->setControlControllerService(serviceName, serviceControl);
    }

    promise.set_value(response);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::sendeventServiceError(ControllerServiceErrorEvent& info) {
    if (info.serviceName == "RearCurtain" || info.serviceName == "MoodLamp") {
        mLogger.LogInfo() << "[sendeventServiceError] ("
                          << info.serviceName   << ":"
                          << info.serviceStatus << ":"
                          << info.serviceError  << ")";
    }

    eventServiceError.Send(info);
}

void
MonitoringManagementSkeletonImpl::sendeventServiceInfoSpare(ControllerServiceInfoSpare& info) {
    if (info.serviceName == "RearCurtain" || info.serviceName == "MoodLamp") {
        mLogger.LogInfo() << "[sendeventServiceInfoSpare] ("
                          << info.serviceName       << ":"
                          << info.version           << ":"
                          << info.lastUpdateTime    << ")";
    }

    eventServiceInfoSpare.Send(info);
}

void
MonitoringManagementSkeletonImpl::sendeventServiceStatusSpare(ControllerServiceStatusSpare& info) {
    if (info.serviceName == "RearCurtain" || info.serviceName == "MoodLamp") {
        mLogger.LogInfo() << "[sendeventServiceStatusSpare] ("
                          << info.serviceName       << ":"
                          << info.serviceStatus     << ":"
                          << info.serviceEnable     << ":"
                          << info.serviceControl    << ")";
    }

    eventServiceStatusSpare.Send(info);
}

void
MonitoringManagementSkeletonImpl::sendupdatableserviceEvent(UpdatableServiceList& info) {
    mLogger.LogInfo() << "[sendupdatableserviceEvent] ("
                      << info.serviceName   << ":"
                      << info.version       << ":"
                      << info.actionType    << ")";

    eventUpdatableService.Send(info);
}

// not use this time

void
MonitoringManagementSkeletonImpl::sendeventServiceInfo() {
    // TODO
}
void
MonitoringManagementSkeletonImpl::sendeventServiceStatus() {
    // TODO
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceInfoAllOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceInfoAll() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceInfoAllOutput response;
    Promise<requestControllerServiceInfoAllOutput> promise;

    bool retVal = false;
    eevp::monitoring::type::ControllerServiceInfoMap infoMap;

    if (listener != nullptr) {
        retVal = listener->requestControllerServiceInfoAll(infoMap);
    }

    if (retVal) {
        response.controllerServiceInfoMap = infoMap;
    }
    response.returnValue = retVal;

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::requestControllerServiceStatusAllOutput>
MonitoringManagementSkeletonImpl::requestControllerServiceStatusAll() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::requestControllerServiceStatusAllOutput response;
    Promise<requestControllerServiceStatusAllOutput> promise;

    bool retVal = false;
    eevp::monitoring::type::ControllerServiceStatusMap statusMap;

    if (listener != nullptr) {
        retVal = listener->requestControllerServiceStatusAll(statusMap);
    }

    if (retVal) {
        response.controllerServiceStatusMap = statusMap;
    }
    response.returnValue = retVal;

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::resetUcmTestOutput>
MonitoringManagementSkeletonImpl::resetUcmTest() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::resetUcmTestOutput response;
    Promise<resetUcmTestOutput> promise;

    if (listener != nullptr) {
        listener->resetUcmTest();
    }

    promise.set_value(response);
    return promise.get_future();
}

} /// namespace monitoring
} /// namespace eevp
