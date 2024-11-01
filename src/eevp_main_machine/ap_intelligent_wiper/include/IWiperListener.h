#include "WiperProxyImpl.h"

namespace eevp {
namespace simulation {

class IWiperListener {
public:
    virtual ~IWiperListener() {};
    virtual void notifyBCM_WipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel) = 0;
   

};

} /// namespace simulation
} /// namespace eevp