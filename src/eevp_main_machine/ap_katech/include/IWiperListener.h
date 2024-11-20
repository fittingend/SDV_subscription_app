#ifndef WIPER_LISTENER_H
#define WIPER_LISTENER_H

#include "eevp/simulation/impl_type_bcm_wipinglevel.h"
#include "eevp/simulation/impl_type_bcm_returncode.h"

namespace eevp
{
    namespace simulation
    {
        class IWiperListener
        {
        public:
            virtual ~IWiperListener() {};
            virtual bool isWiping() = 0;
            virtual eevp::simulation::BCM_ReturnCode stopWiping() = 0;
            virtual eevp::simulation::BCM_ReturnCode startWiping() = 0;

            virtual std::uint16_t getWipingInterval() = 0;
            virtual eevp::simulation::BCM_WipingLevel getWipingLevel() = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel) = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval) = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) = 0;
        };
    } /// namespace control
} /// namespace eevp

#endif // WIPER_LISTENER_H