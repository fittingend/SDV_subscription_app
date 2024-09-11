#ifndef IMOOD_LAMP_LISTENER_H
#define IMOOD_LAMP_LISTENER_H

#include "eevp/control/impl_type_soamlmstatus.h"

namespace eevp {
namespace control {
namespace moodlamp {

class IMoodLampListener {
public:
    virtual ~IMoodLampListener() {};
    virtual void notifySoaMlmStatus(const eevp::control::SoaMlmStatus& fieldValue) = 0;
    virtual void notifySoaMlmSwVersion(const std::uint8_t& fieldValue) = 0;

    virtual void getSoaMlmStatus(eevp::control::SoaMlmStatus& fieldValue) = 0;
    virtual void getSoaMlmSwVersion(std::uint8_t& fieldValue) = 0;
};

} /// namespace moodlamp
} /// namespace control
} /// namespace eevp

#endif /* IMOOD_LAMP_LISTENER_H */