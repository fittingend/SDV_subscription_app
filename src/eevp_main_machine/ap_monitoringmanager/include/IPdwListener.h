#ifndef IPDW_LISTENER_H
#define IPDW_LISTENER_H

#include "eevp/pdw/type/impl_type_direction.h"

namespace eevp {
namespace pdw {
class IPdwListener {
public:
    virtual ~IPdwListener() {};
    virtual void notifyDistanceLevel(const eevp::pdw::type::DistanceLevel& dLevel) = 0;
};


} /// namespace pdw
} /// namespace eevp


#endif /* IPDW_LISTENER_H */