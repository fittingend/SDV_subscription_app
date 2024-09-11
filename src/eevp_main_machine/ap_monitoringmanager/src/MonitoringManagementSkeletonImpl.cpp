#include "MonitoringManagementSkeletonImpl.h"
// #define DLT_LOG_ON

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

    auto mbTemp_get_handler = [this]() {
        return this->mbTempGetter();
    };

    auto soaMlmStatus_get_handler = [this]() {
        return this->soaMlmStatusGetter();
    };

    auto soaMlmSwVersion_get_handler = [this]() {
        return this->soaMlmSwVersionGetter();
    };

    auto soaWiperDeviceNormal_get_handler = [this]() {
        return this->soaWiperDeviceIsNormalGetter();
    };

    auto soaWiperStatus_get_handler = [this]() {
        return this->soaWiperStatusGetter();
    };

    auto soaWiperSwVersion_get_handler = [this]() {
        return this->soaWiperSwVersionGetter();
    };

    auto soaRctnStatus_get_handler = [this]() {
        return this->soaRctnStatusGetter();
    };

    auto soaRctnSwVersion_get_handler = [this]() {
        return this->soaRctnSwVersionGetter();
    };

    soaMlmStatus.RegisterGetHandler(soaMlmStatus_get_handler);
    soaMlmSwVersion.RegisterGetHandler(soaMlmSwVersion_get_handler);

    soaWiperDeviceNormal.RegisterGetHandler(soaWiperDeviceNormal_get_handler);
    soaWiperStatus.RegisterGetHandler(soaWiperStatus_get_handler);
    soaWiperSwVersion.RegisterGetHandler(soaWiperSwVersion_get_handler);

    soaRctnStatus.RegisterGetHandler(soaRctnStatus_get_handler);
    soaRctnSwVersion.RegisterGetHandler(soaRctnSwVersion_get_handler);
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
    } /*else {
        response.serviceName = {"error"};
        response.version = {"error"};
        response.lastUpdateTime = {0};
    } */

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
    } /* else {
        response.serviceName = {"error"};
        response.serviceStatus = {"error"};
        response.serviceEnable = {"error"};
        response.serviceControl = {"error"};
    } */

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

void
MonitoringManagementSkeletonImpl::notifyMbTemp(const eevp::type::String& mbTempValue) {
    mbTemp.Update(mbTempValue);
}

Future<service::skeleton::fields::mbTemp::FieldType>
MonitoringManagementSkeletonImpl::mbTempGetter()
{
    ara::core::Promise<skeleton::fields::mbTemp::FieldType> promise;
    promise.set_value(this->mbTempField);
    return promise.get_future();
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

/// MoodLamp Start

Future<skeleton::MonitoringManagementSkeleton::RequestMlmSetRgbColorOutput>
MonitoringManagementSkeletonImpl::RequestMlmSetRgbColor(const std::uint8_t& colorTableIndex){
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestMlmSetRgbColorOutput response;
    Promise<RequestMlmSetRgbColorOutput> promise;

    if (listener != nullptr) {
        listener->RequestMlmSetRgbColor(colorTableIndex);
    }

    promise.set_value(response);
    return promise.get_future();
}
Future<service::skeleton::fields::soaMlmStatus::FieldType>
MonitoringManagementSkeletonImpl::soaMlmStatusGetter()
{
    ara::core::Promise<skeleton::fields::soaMlmStatus::FieldType> promise;
    promise.set_value(this->mlmStatusField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateMlmStatus(const eevp::control::SoaMlmStatus& mlmStatus){
    mLogger.LogInfo() << __func__;

    soaMlmStatus.Update(mlmStatus);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "("  << static_cast<uint8_t>(mlmStatus.colorTableIndex) << ":"
                                         << static_cast<uint8_t>(mlmStatus.moodMode) << ":"
                                         << static_cast<uint8_t>(mlmStatus.brightness) <<":"
                                         << static_cast<uint8_t>(mlmStatus.isNormal)<<")";
    #endif
}

Future<service::skeleton::fields::soaMlmSwVersion::FieldType>
MonitoringManagementSkeletonImpl::soaMlmSwVersionGetter()
{
    ara::core::Promise<skeleton::fields::soaMlmSwVersion::FieldType> promise;
    promise.set_value(this->mlmVersionField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateMlmSwVersion(const std::uint8_t& mlmSwVersion){
    mLogger.LogInfo() << __func__;

    soaMlmSwVersion.Update(mlmSwVersion);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << mlmSwVersion <<")";
    #endif
}

/// MoodLamp End

/// Pdw Start

void
MonitoringManagementSkeletonImpl::notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel) {
    mLogger.LogInfo() << "__func__";

    DistanceLevel.Send(dLevel);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(dLevel.Left) << ":"
                                        << static_cast<uint8_t>(dLevel.Right) << ":"
                                        << static_cast<uint8_t>(dLevel.Center) << ":"
                                        << static_cast<uint8_t>(dLevel.SensorDirection) << ")";
    #endif
}

/// Pdw End

/// Roa Start

Future<skeleton::MonitoringManagementSkeleton::ResetRoaDetectInfoOutput>
MonitoringManagementSkeletonImpl::ResetRoaDetectInfo() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::ResetRoaDetectInfoOutput response;
    Promise<ResetRoaDetectInfoOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::SetRoaModeOutput>
MonitoringManagementSkeletonImpl::SetRoaMode(const eevp::control::SoaRoaMode& mode) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::SetRoaModeOutput response;
    Promise<SetRoaModeOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::StartRoaOutput>
MonitoringManagementSkeletonImpl::StartRoa() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::StartRoaOutput response;
    Promise<StartRoaOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::StopRoaOutput>
MonitoringManagementSkeletonImpl::StopRoa() {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::StopRoaOutput response;
    Promise<StopRoaOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<service::skeleton::fields::soaRoaDeviceNormal::FieldType>
MonitoringManagementSkeletonImpl::soaRoaDeviceNormalGetter()
{
    ara::core::Promise<skeleton::fields::soaRoaDeviceNormal::FieldType> promise;
    promise.set_value(this->roaDeviceNormalField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal)
{
    mLogger.LogInfo() << __func__;

    soaRoaDeviceNormal.Update(deviceIsNormal);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(deviceIsNormal) <<")";
    #endif
}

/// Roa End

/// DriveSeat Start

Future<skeleton::MonitoringManagementSkeleton::RequestMoveDrvSeatHeightOutput>
MonitoringManagementSkeletonImpl::RequestMoveDrvSeatHeight(const eevp::control::SoaSeatHeightDirection& dir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestMoveDrvSeatHeightOutput response;
    Promise<RequestMoveDrvSeatHeightOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::RequestMoveDrvSeatReclineOutput>
MonitoringManagementSkeletonImpl::RequestMoveDrvSeatRecline(const eevp::control::SoaSeatReclineDirection& dir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestMoveDrvSeatReclineOutput response;
    Promise<RequestMoveDrvSeatReclineOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::RequestMoveDrvSeatSlideOutput>
MonitoringManagementSkeletonImpl::RequestMoveDrvSeatSlide(const eevp::control::SoaSeatSlideDirection& dir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestMoveDrvSeatSlideOutput response;
    Promise<RequestMoveDrvSeatSlideOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::RequestMoveDrvSeatTiltOutput>
MonitoringManagementSkeletonImpl::RequestMoveDrvSeatTilt(const eevp::control::SoaSeatTiltDirection& dir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestMoveDrvSeatTiltOutput response;
    Promise<RequestMoveDrvSeatTiltOutput> promise;

    if (listener != nullptr) {
        //listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<service::skeleton::fields::soaDrvSeatDeviceNormal::FieldType>
MonitoringManagementSkeletonImpl::soaDrvSeatDeviceNormalGetter()
{
    ara::core::Promise<skeleton::fields::soaDrvSeatDeviceNormal::FieldType> promise;
    promise.set_value(this->drvseatDeviceNormalField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal)
{
    mLogger.LogInfo() << __func__;

    soaDrvSeatDeviceNormal.Update(deviceIsNormal);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(deviceIsNormal) <<")";
    #endif
}

/// DriveSeat End

/// Wiper Start

Future<skeleton::MonitoringManagementSkeleton::RequestWiperOperationOutput>
MonitoringManagementSkeletonImpl::RequestWiperOperation(const eevp::control::SoaWiperMode& mode) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestWiperOperationOutput response;
    Promise<RequestWiperOperationOutput> promise;

    if (listener != nullptr) {
        listener->requestWiperOperation(mode);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::SetWiperAutoSpeedOutput>
MonitoringManagementSkeletonImpl::SetWiperAutoSpeed(const bool& isAutoSpeed) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::SetWiperAutoSpeedOutput response;
    Promise<SetWiperAutoSpeedOutput> promise;

    if (listener != nullptr) {
        listener->setWiperAutoSpeed(isAutoSpeed);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<service::skeleton::fields::soaWiperDeviceNormal::FieldType>
MonitoringManagementSkeletonImpl::soaWiperDeviceIsNormalGetter()
{
    ara::core::Promise<skeleton::fields::soaWiperDeviceNormal::FieldType> promise;
    promise.set_value(this->wiperDeviceNormalField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateSoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) {
    mLogger.LogInfo() << __func__;

    soaWiperDeviceNormal.Update(deviceIsNormal);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(deviceIsNormal) <<")";
    #endif
}

Future<service::skeleton::fields::soaWiperStatus::FieldType>
MonitoringManagementSkeletonImpl::soaWiperStatusGetter()
{
    ara::core::Promise<skeleton::fields::soaWiperStatus::FieldType> promise;
    promise.set_value(this->wiperStatusField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateSoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue) {
    mLogger.LogInfo() << __func__;

    soaWiperStatus.Update(wiperStatusValue);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << wiperStatusValue.isAutoMode
                                         << static_cast<uint8_t>(wiperStatusValue.mode) << ")";
    #endif
}

Future<service::skeleton::fields::soaWiperSwVersion::FieldType>
MonitoringManagementSkeletonImpl::soaWiperSwVersionGetter()
{
    ara::core::Promise<skeleton::fields::soaWiperSwVersion::FieldType> promise;
    promise.set_value(this->wiperVersionField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateSoaWiperSwVersion(const std::uint8_t& wiperSwVersion) {
    mLogger.LogInfo() << __func__;

    soaWiperSwVersion.Update(wiperSwVersion);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << wiperSwVersion <<")";
    #endif
}

/// Wiper End

/// RearCurtain Start

Future<skeleton::MonitoringManagementSkeleton::RequestRearCurtainOperationOutput>
MonitoringManagementSkeletonImpl::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestRearCurtainOperationOutput response;
    Promise<RequestRearCurtainOperationOutput> promise;

    if (listener != nullptr) {
        listener->RequestRearCurtainOperation(motorDir);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::MonitoringManagementSkeleton::RequestRearCurtainPositionOutput>
MonitoringManagementSkeletonImpl::RequestRearCurtainPosition(const std::uint8_t& posPercentage){
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestRearCurtainPositionOutput response;
    Promise<RequestRearCurtainPositionOutput> promise;

    if (listener != nullptr) {
        listener->RequestRearCurtainPosition(posPercentage);
    }

    promise.set_value(response);
    return promise.get_future();
}

Future<skeleton::fields::soaRctnStatus::FieldType>
MonitoringManagementSkeletonImpl::soaRctnStatusGetter()
{
    ara::core::Promise<skeleton::fields::soaRctnStatus::FieldType> promise;
    promise.set_value(this->rctnStatusField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) {
    mLogger.LogInfo() << __func__;

    soaRctnStatus.Update(fieldValue);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(fieldValue.errorState) << ":"
                                         <<static_cast<uint8_t>(fieldValue.curMotorDirection) << ":"
                                         <<static_cast<uint8_t>(fieldValue.curtainState) <<":"
                                         <<static_cast<uint8_t>(fieldValue.isNormal)<<")";
    #endif

}

Future<skeleton::fields::soaRctnSwVersion::FieldType>
MonitoringManagementSkeletonImpl::soaRctnSwVersionGetter()
{
    ara::core::Promise<skeleton::fields::soaRctnSwVersion::FieldType> promise;
    promise.set_value(this->rctnVersionField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updateRctnVersion(const std::uint8_t& rctnSwVerison) {
    soaRctnSwVersion.Update(rctnSwVerison);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << rctnSwVerison <<")";
    #endif
}

/// RearCurtain End

/// Power Start

Future<service::skeleton::fields::soaPowerDeviceNormal::FieldType>
MonitoringManagementSkeletonImpl::soaPowerDeviceNormalGetter()
{
    ara::core::Promise<skeleton::fields::soaPowerDeviceNormal::FieldType> promise;
    promise.set_value(this->powerDeviceNormalField);
    return promise.get_future();
}

void
MonitoringManagementSkeletonImpl::updatePowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal)
{
    mLogger.LogInfo() << __func__;

    soaPowerDeviceNormal.Update(deviceIsNormal);

    #ifdef DLT_LOG_ON
    mLogger.LogInfo() << __func__<< "(" << static_cast<uint8_t>(deviceIsNormal) <<")";
    #endif
}

///

} /// namespace monitoring
} /// namespace eevp
