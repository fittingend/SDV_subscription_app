#ifndef IOTA_MONITORING_LISTENER_H
#define IOTA_MONITORING_LISTENER_H

#include "eevp/ota/monitoring/type/impl_type_requestserviceinfo.h"
#include "eevp/ota/monitoring/type/impl_type_updatableserviceinfo.h"

namespace eevp {
namespace monitoring {

class IOtaMonitoringListener {
public:
    virtual ~IOtaMonitoringListener() {};
    virtual void notifyServiceEvent(const eevp::ota::monitoring::type::RequestServiceInfo& requestServiceInfo) = 0;
    virtual void notifyUpdatableService(const eevp::ota::monitoring::type::UpdatableServiceInfo& updatableServiceInfo) = 0;
};

} /// namespace monitoring
} /// namespace eevp

#endif /* IOTA_MONITORING_LISTENER_H */