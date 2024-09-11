#ifndef IPOWER_LISTENER_H
#define IPOWER_LISTENER_H

#include "eevp/control/impl_type_soadeviceisnormal.h"

namespace eevp {
namespace control {
namespace power {

class IPowerListener {
public:
    virtual ~IPowerListener() {};
    virtual void notifySoaPowerDeviceNormal(const eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void notifySoaPowerSwVersion(const std::uint8_t& fieldValue) = 0;

    virtual void getSoaPowerDeviceNormal(eevp::control::SoaDeviceIsNormal& deviceIsNormal) = 0;
    virtual void getSoaPowerSwVersion(std::uint8_t& fieldValue) = 0;
};

} /// namespace power
} /// namespace control
} /// namespace eevp

#endif /* IPOWER_LISTENER_H */