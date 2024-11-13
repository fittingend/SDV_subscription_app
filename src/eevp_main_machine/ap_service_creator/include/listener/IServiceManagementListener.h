#ifndef __ISERVICE_MANAGEMENT_LISTENER_H__
#define __ISERVICE_MANAGEMENT_LISTENER_H__

#include "eevp/simulation/impl_type_bcm_returncode.h"
#include "eevp/simulation/impl_type_bcm_wipinglevel.h"

namespace eevp
{
    namespace service
    {

        class IServiceManagementListener
        {
        public:
            virtual ~IServiceManagementListener() {};

            virtual bool isWiping() = 0;
            virtual std::uint16_t getWipingInterval() = 0;
            virtual eevp::simulation::BCM_WipingLevel getWipingLevel() = 0;
            virtual eevp::simulation::BCM_ReturnCode stopWiping() = 0;
            virtual eevp::simulation::BCM_ReturnCode startWiping() = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingLevelImme(const eevp::simulation::BCM_WipingLevel &wipingLevel) = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingInterval(std::uint16_t &wipingInterval) = 0;
            virtual eevp::simulation::BCM_ReturnCode setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel) = 0;
        };

    } /// namespace monitoring
} /// namespace eevp

#endif // __ISERVICE_MANAGEMENT_LISTENER_H__