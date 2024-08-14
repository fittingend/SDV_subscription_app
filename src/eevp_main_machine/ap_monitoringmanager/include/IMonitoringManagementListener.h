#ifndef IMONITORING_MANAGEMENT_LISTENER_H
#define IMONITORING_MANAGEMENT_LISTENER_H

#include "eevp/monitoring/type/impl_type_controllerserviceinfo.h"
#include "eevp/monitoring/type/impl_type_controllerserviceinfomap.h"
#include "eevp/monitoring/type/impl_type_controllerservicestatus.h"
#include "eevp/monitoring/type/impl_type_controllerservicestatusmap.h"

#include "eevp/monitoring/type/impl_type_controllerserviceerrorevent.h"
#include "eevp/monitoring/type/impl_type_controllerserviceinfospare.h"
#include "eevp/monitoring/type/impl_type_controllerservicestatusspare.h"
#include "eevp/monitoring/type/impl_type_updatableservicelist.h"
#include "eevp/monitoring/type/impl_type_stringarray.h"
#include "eevp/monitoring/type/impl_type_timearray.h"
#include "eevp/type/impl_type_string.h"

namespace eevp {
namespace monitoring {

class IMonitoringManagementListener {
public:
    virtual ~IMonitoringManagementListener() {};

    virtual bool requestAppInstall(const eevp::type::String& serviceName) = 0;
    virtual bool requestAppUpdate(const eevp::type::String& serviceName) = 0;
    virtual bool requestControllerServiceInfo(
                    const eevp::type::String& serviceName,
                    eevp::monitoring::type::ControllerServiceInfo& serviceInfo) = 0;
    virtual bool requestControllerServiceInfoAll(eevp::monitoring::type::ControllerServiceInfoMap& infoMap) = 0;
    virtual bool requestControllerServiceStatus(const eevp::type::String& serviceName, eevp::type::String& status) = 0;
    virtual bool requestControllerServiceStatusAll(eevp::monitoring::type::ControllerServiceStatusMap& statusMap) = 0;
    virtual bool setEnableControllerService(const eevp::type::String& serviceName, const eevp::type::String& enable) = 0;

    virtual bool requestControllerServiceInfoAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& version,
                    eevp::monitoring::type::TimeArray& lastUpdateTime) = 0;
    virtual bool requestControllerServiceStatusAllSpare(
                    eevp::monitoring::type::StringArray& serviceName,
                    eevp::monitoring::type::StringArray& serviceStatus,
                    eevp::monitoring::type::StringArray& serviceEnable,
                    eevp::monitoring::type::StringArray& serviceControl) = 0;
    virtual bool setControlControllerService(
                    const eevp::type::String& serviceName,
                    const eevp::type::String& serviceControl) = 0;

    virtual void resetUcmTest() = 0;
};

} /// namespace monitoring
} /// namespace eevp

#endif /* IMONITORING_MANAGEMENT_LISTENER_H */