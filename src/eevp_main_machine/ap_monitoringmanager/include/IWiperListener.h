#ifndef IWIPER_LISTENER_H
#define IWIPER_LISTENER_H

#include "eevp/control/impl_type_soadeviceisnormal.h"
#include "eevp/control/impl_type_soawiperstatus.h"
#include "eevp/control/impl_type_soawipermode.h"

namespace eevp {
namespace control {
namespace wiper {

class IWiperListener {
public:
    virtual ~IWiperListener() {};
    virtual void notifySoaWiperDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void notifySoaWiperStatus(const eevp::control::SoaWiperStatus& wiperStatusValue) = 0;
    virtual void notifySoaWiperSwVersion(const std::uint8_t& wiperSwVersion) = 0;

    virtual void getSoaWiperDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void getSoaWiperStatus(eevp::control::SoaWiperStatus& wiperStatusValue) = 0;
    virtual void getSoaWiperSwVersion(std::uint8_t& wiperSwVersion) = 0;

    virtual void requestWiperOperation(const eevp::control::SoaWiperMode& wiperOperationMode) = 0;
    virtual void setWiperAutoSpeed(const bool& isAutoSpeed) = 0;
};

} /// namespace wiper
} /// namespace control
} /// namespace eevp

#endif /* IWIPER_LISTENER_H */