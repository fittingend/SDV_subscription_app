#ifndef IREAR_CURTAIN_LISTENER_H
#define IREAR_CURTAIN_LISTENER_H

#include "eevp/control/impl_type_soarctnstatus.h"

namespace eevp {
namespace control {
namespace rearcurtain {

class IRearCurtainListener {
public:
    virtual ~IRearCurtainListener() {};
    virtual void notifySoaRctnStatus(const eevp::control::SoaRctnStatus& fieldValue) = 0;
    virtual void notifySoaRctnSwVersion(const std::uint8_t& fieldValue) = 0;

    virtual void getSoaRctnStatus(eevp::control::SoaRctnStatus& fieldValue) = 0;
    virtual void getSoaRctnSwVersion(std::uint8_t& fieldValue) = 0;
};

} /// namespace rearcurtain
} /// namespace control
} /// namespace eevp

#endif /* IREAR_CURTAIN_LISTENER_H */