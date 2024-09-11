#ifndef IDRVSEAT_LISTENER_H
#define IDRVSEAT_LISTENER_H

#include "eevp/control/impl_type_soadeviceisnormal.h"

namespace eevp {
namespace control {
namespace drvseat {

class IDrvseatListener {
public:
    virtual ~IDrvseatListener() {};
    virtual void notifySoaDrvseatDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void notifySoaDrvseatSwVersion(const std::uint8_t& drvseatSwVersion) = 0;

    virtual void getSoaDrvseatDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void getSoaDrvseatSwVersion(std::uint8_t& drvseatSwVersion) = 0;
};

} /// namespace drvseat
} /// namespace control
} /// namespace eevp

#endif /* IDRVSEAT_LISTENER_H */