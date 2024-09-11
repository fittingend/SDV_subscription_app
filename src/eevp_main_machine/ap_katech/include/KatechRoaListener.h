#ifndef IROA_LISTENER_H
#define IROA_LISTENER_H

#include "eevp/control/impl_type_soadeviceisnormal.h"

namespace eevp {
namespace control {
namespace roa {

class KatechRoaListener {
public:
    virtual ~KatechRoaListener() {};
    virtual void notifySoaRoaDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void notifySoaRoaSwVersion(const std::uint8_t& fieldValue) = 0;

    virtual void getSoaRoaDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void getSoaRoaSwVersion(std::uint8_t& fieldValue) = 0;

    //virtual void notifyRoaDetectState(const eevp::control::SoaRoaDetectState& fieldValue) = 0;

};

} /// namespace roa
} /// namespace control
} /// namespace eevp

#endif /* IROA_LISTENER_H */