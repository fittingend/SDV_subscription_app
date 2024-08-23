#ifndef IVEHICLE_PACKAGE_MANAGEMENT_LISTENER_H
#define IVEHICLE_PACKAGE_MANAGEMENT_LISTENER_H

#include "ara/ucm/impl_type_swnameversiontype.h"
#include "ara/ucm/impl_type_transferstatetype.h"

namespace eevp {
namespace ota {
namespace vucm {

class IVehiclePackageManagementListener {
public:
    virtual ~IVehiclePackageManagementListener() {};

    virtual void notifyRequestedPackage(const ara::ucm::SwNameVersionType& requestedPackage) = 0;
    virtual void notifySafetyState(const bool& safetyState) = 0;
    virtual void notifyTransferState(const ara::ucm::TransferStateType& transferState) = 0;
};

} /// namespace vucm
} /// namespace ota
} /// namespace eevp

#endif /* IVEHICLE_PACKAGE_MANAGEMENT_LISTENER_H */