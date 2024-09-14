#ifndef ROA_LISTENER_H
#define ROA_LISTENER_H

#include "eevp/control/impl_type_soadeviceisnormal.h"

namespace eevp {
namespace control {
namespace roa {

class IRoaListener {
public:
    virtual ~IRoaListener() {};
    virtual void notifySoaRoaDetectCount(std::uint8_t& value) = 0;
};

} /// namespace roa
} /// namespace control
} /// namespace eevp

#endif /* ROA_LISTENER_H */