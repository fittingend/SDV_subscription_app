#ifndef __GEAR_PROXY_IMPL_H_
#define __GEAR_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>

#include "eevp/simulation/vcs_gear_proxy.h"
#include "ara/log/logger.h"

#include "listener/IGearListener.h"

using namespace ara::com;

namespace eevp
{
    namespace simulation
    {

        class GearProxyImpl
        {
        public:
            GearProxyImpl();
            ~GearProxyImpl();

            void setEventListener(const std::shared_ptr<eevp::simulation::IGearListener> _listener);
            bool init();

            // getter method
            eevp::simulation::type::VCS_Gear get_Gear();

            // setter method
            void set_Gear(const eevp::simulation::type::VCS_Gear &vcs_gear);

        private:
            void FindServiceCallback(
                ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_GearProxy::HandleType> container,
                ara::com::FindServiceHandle findHandle);

            ara::log::Logger &mLogger;
            std::shared_ptr<eevp::simulation::IGearListener> listener;
            std::shared_ptr<eevp::simulation::proxy::VCS_GearProxy> mProxy;
            std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

            std::mutex mHandle;
            std::condition_variable cvHandle;

            eevp::simulation::type::VCS_Gear vcs_Gear;
        };
    } // namespace simulation
} // namespace eevp

#endif //__GEAR_PROXY_IMPL_H_