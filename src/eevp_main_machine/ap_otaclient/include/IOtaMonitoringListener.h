#ifndef IOTA_MONITORING_LISTENER_H
#define IOTA_MONITORING_LISTENER_H

#include "eevp/ota/monitoring/type/impl_type_requestserviceinfomap.h"

namespace eevp {
namespace ota {

class IOtaMonitoringListener {
public:
    virtual ~IOtaMonitoringListener() {};

    virtual void requestServiceInstall(const ara::core::String& serviceName) = 0;
    virtual void requestServiceUpdate(const ara::core::String& serviceName) = 0;
    virtual void requestVersionInfo(eevp::ota::monitoring::type::RequestServiceInfoMap& requestServiceInfoMap) = 0;
    virtual void resetUcmTest() = 0;
};

} /// namespace ota
} /// namespace eevp

#endif /* IOTA_MONITORING_LISTENER_H */