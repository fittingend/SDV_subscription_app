#ifndef __IBRAKEPEDAL_LISTENER_H__
#define __IBRAKEPEDAL_LISTENER_H__

#include "eevp/simulation/type/impl_type_vcs_brakeposn.h"
#include "eevp/simulation/type/impl_type_vcs_brakeswitch.h"


namespace eevp {
namespace simulation {

class IBrakePedalListener {
public:
    virtual ~IBrakePedalListener() {};
   

};

} /// namespace simulation
} /// namespace eevp

#endif // __IBRAKEPEDAL_LISTENER_H__