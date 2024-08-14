#ifndef IROA_LISTENER_H
#define IROA_LISTENER_H

#include "eevp/control/impl_type_soaroadetectstate.h"

namespace eevp {
namespace control {
namespace roa {

class IRoaListener {
public:
    virtual ~IRoaListener() {};
    //virtual void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) = 0;

    virtual void getSoaRoaDetectState() = 0;
};

} /// namespace rearcurtain
} /// namespace control
} /// namespace eevp

#endif /* IREAR_CURTAIN_LISTENER_H */