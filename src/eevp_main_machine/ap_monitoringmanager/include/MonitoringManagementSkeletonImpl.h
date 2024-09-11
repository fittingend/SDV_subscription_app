#ifndef EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_
#define EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_

#include "ara/log/logger.h"
#include "eevp/monitoring/service/monitoringmanagement_skeleton.h"

#include "IMonitoringManagementListener.h"

using namespace ara::core;

namespace eevp {
namespace monitoring {

class MonitoringManagementSkeletonImpl : public eevp::monitoring::service::skeleton::MonitoringManagementSkeleton {
public:
    MonitoringManagementSkeletonImpl(
            InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEventSingleThread);

    ~MonitoringManagementSkeletonImpl();

    void setEventListener(std::shared_ptr<eevp::monitoring::IMonitoringManagementListener> _listener);

    /// Method
    Future<requestAppInstallOutput> requestAppInstall(const eevp::type::String& serviceName) override;
    Future<requestAppUpdateOutput> requestAppUpdate(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceInfoOutput> requestControllerServiceInfo(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceInfoAllOutput> requestControllerServiceInfoAll() override;
    Future<requestControllerServiceStatusOutput> requestControllerServiceStatus(const eevp::type::String& serviceName) override;
    Future<requestControllerServiceStatusAllOutput> requestControllerServiceStatusAll() override;
    Future<setEnableControllerServiceOutput> setEnableControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& enable) override;
    Future<requestControllerServiceInfoAllSpareOutput> requestControllerServiceInfoAllSpare() override;
    Future<requestControllerServiceStatusAllSpareOutput> requestControllerServiceStatusAllSpare() override;
    Future<setControlControllerServiceOutput> setControlControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& serviceControl) override;

    Future<resetUcmTestOutput> resetUcmTest() override;

    void sendeventServiceError(eevp::monitoring::type::ControllerServiceErrorEvent& info);
    void sendeventServiceInfoSpare(eevp::monitoring::type::ControllerServiceInfoSpare& info);
    void sendeventServiceStatusSpare(eevp::monitoring::type::ControllerServiceStatusSpare& info);
    void sendupdatableserviceEvent(eevp::monitoring::type::UpdatableServiceList& info);

    void notifyMbTemp(const eevp::type::String& mbTempValue);
    Future<service::skeleton::fields::mbTemp::FieldType> mbTempGetter();

    /// MoodLamp
    Future<RequestMlmSetRgbColorOutput> RequestMlmSetRgbColor(const std::uint8_t& colorTableIndex) override;

    Future<service::skeleton::fields::soaMlmStatus::FieldType> soaMlmStatusGetter();
    void updateMlmStatus(const eevp::control::SoaMlmStatus& mlmStatus);

    Future<service::skeleton::fields::soaMlmSwVersion::FieldType> soaMlmSwVersionGetter();
    void updateMlmSwVersion(const std::uint8_t& mlmSwVersion);

    /// Pdw
    void notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel);

    /// Roa
    Future<ResetRoaDetectInfoOutput> ResetRoaDetectInfo() override;
    Future<SetRoaModeOutput> SetRoaMode(const eevp::control::SoaRoaMode& mode) override;
    Future<StartRoaOutput> StartRoa() override;
    Future<StopRoaOutput> StopRoa() override;

    Future<service::skeleton::fields::soaRoaDetectCount::FieldType> soaRoaDetectCountGetter();
    void updateRoaDetectCount(const std::uint8_t& roaDetectCount);

    Future<service::skeleton::fields::soaRoaDetectState::FieldType> soaRoaDetectStateGetter();
    void updateRoaDetectState(const eevp::control::SoaRoaDetectState& roaDetectState);

    Future<service::skeleton::fields::soaRoaMode::FieldType> soaRoaModeGetter();
    void updateRoaMode(const eevp::control::SoaRoaMode& roaDetectCount);

    Future<service::skeleton::fields::soaRoaRunningState::FieldType> soaRoaRunningStateGetter();
    void updateRoaRunningState(const eevp::control::SoaRoaRunningState& roaDetectState);

    Future<service::skeleton::fields::soaRoaSensorError::FieldType> soaRoaSensorErrorGetter();
    void updateRoaSensorError(const eevp::control::SoaRoaSensorError& roaDetectState);

    Future<service::skeleton::fields::soaRoaDeviceNormal::FieldType> soaRoaDeviceNormalGetter();
    void updateRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);

    Future<service::skeleton::fields::soaRoaSwVersion::FieldType> soaRoaSwVersionGetter();
    void updateRoaStatus(const std::uint8_t& roaSwVersion);

    /// DriveSeat
    Future<RequestMoveDrvSeatHeightOutput> RequestMoveDrvSeatHeight(const eevp::control::SoaSeatHeightDirection& dir) override;
    Future<RequestMoveDrvSeatReclineOutput> RequestMoveDrvSeatRecline(const eevp::control::SoaSeatReclineDirection& dir) override;
    Future<RequestMoveDrvSeatSlideOutput> RequestMoveDrvSeatSlide(const eevp::control::SoaSeatSlideDirection& dir) override;
    Future<RequestMoveDrvSeatTiltOutput> RequestMoveDrvSeatTilt(const eevp::control::SoaSeatTiltDirection& dir) override;

    Future<service::skeleton::fields::soaDrvSeatMotorDirection::FieldType> soaDrvSeatMotorDirectionGetter();
    void updateDrvseatMotorDirection(const eevp::control::SoaRoaRunningState& roaDetectState);

    Future<service::skeleton::fields::soaDrvSeatMotorPosition::FieldType> soaDrvSeatMotorPositionGetter();
    void updateDrvseatMotorPosition(const eevp::control::SoaRoaSensorError& roaDetectState);

    Future<service::skeleton::fields::soaDrvSeatDeviceNormal::FieldType> soaDrvSeatDeviceNormalGetter();
    void updateDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);

    Future<service::skeleton::fields::soaDrvSeatSwVersion::FieldType> soaDrvSeatSwVersionGetter();
    void updateDrvseatStatus(const std::uint8_t& drvseatSwVersion);

    /// Wiper
    Future<RequestWiperOperationOutput> RequestWiperOperation(const eevp::control::SoaWiperMode& mode) override;
    Future<SetWiperAutoSpeedOutput> SetWiperAutoSpeed(const bool& isAutoSpeed) override;

    Future<service::skeleton::fields::soaWiperDeviceNormal::FieldType> soaWiperDeviceIsNormalGetter();
    void updateSoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);

    Future<service::skeleton::fields::soaWiperStatus::FieldType> soaWiperStatusGetter();
    void updateSoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue);

    Future<service::skeleton::fields::soaWiperSwVersion::FieldType> soaWiperSwVersionGetter();
    void updateSoaWiperSwVersion(const std::uint8_t& wiperSwVersion);

    /// RearCurtain
    Future<RequestRearCurtainOperationOutput> RequestRearCurtainOperation(
                        const eevp::control::SoaRctnMotorDir& motorDir) override;
    Future<RequestRearCurtainPositionOutput> RequestRearCurtainPosition(const std::uint8_t& posPercentage) override;

    Future<service::skeleton::fields::soaRctnStatus::FieldType> soaRctnStatusGetter();
    void updateRctnStatus(const eevp::control::SoaRctnStatus& fieldValue);

    Future<service::skeleton::fields::soaRctnSwVersion::FieldType> soaRctnSwVersionGetter();
    void updateRctnVersion(const std::uint8_t& rctnSwVersion);

    /// Power
    Future<service::skeleton::fields::soaPowerDeviceNormal::FieldType> soaPowerDeviceNormalGetter();
    void updatePowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal);

    Future<service::skeleton::fields::soaPowerSwVersion::FieldType> soaPowerSwVersionGetter();
    void updatePowerStatus(const std::uint8_t& powerSwVersion);

private:
    ara::log::Logger& mLogger;
    std::shared_ptr<IMonitoringManagementListener> listener;

    service::skeleton::fields::mbTemp::FieldType mbTempField;

    service::skeleton::fields::soaMlmStatus::FieldType mlmStatusField;
    service::skeleton::fields::soaMlmSwVersion::FieldType mlmVersionField;

    service::skeleton::fields::soaRoaDeviceNormal::FieldType roaDeviceNormalField;
    service::skeleton::fields::soaRoaSwVersion::FieldType roaVersionField;

    service::skeleton::fields::soaDrvSeatDeviceNormal::FieldType drvseatDeviceNormalField;
    service::skeleton::fields::soaDrvSeatSwVersion::FieldType drvseatVersionField;

    service::skeleton::fields::soaWiperDeviceNormal::FieldType wiperDeviceNormalField;
    service::skeleton::fields::soaWiperStatus::FieldType wiperStatusField;
    service::skeleton::fields::soaWiperSwVersion::FieldType wiperVersionField;

    service::skeleton::fields::soaRctnStatus::FieldType rctnStatusField;
    service::skeleton::fields::soaRctnSwVersion::FieldType rctnVersionField;

    service::skeleton::fields::soaPowerDeviceNormal::FieldType powerDeviceNormalField;
    service::skeleton::fields::soaPowerSwVersion::FieldType powerVersionField;

};

} /// namespace monitoring
} /// namespace eevp

#endif /// EEVP_MONITORING_MANAGEMENT_SKELETON_IMPL_H_
