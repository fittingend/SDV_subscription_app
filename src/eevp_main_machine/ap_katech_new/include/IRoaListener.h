#ifndef IROA_LISTENER_H
#define IROA_LISTENER_H

#include "eevp/control/impl_type_soaroadetectstate.h"

namespace eevp {
namespace control {
namespace roa {

class IRoaListener {
public:
    virtual ~IRoaListener() {};
    virtual void notifyRoaDetectState(const eevp::control::SoaRoaDetectState& fieldValue) = 0;

    virtual void getSoaRoaDetectState() = 0;
};

} /// namespace roa
} /// namespace control
} /// namespace eevp

#endif /* IROA_LISTENER_H */