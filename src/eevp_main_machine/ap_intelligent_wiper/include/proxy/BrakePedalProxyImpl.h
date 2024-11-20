#ifndef __BRAKEPEDAL_PROXY_IMPL_H_
#define __BRAKEPEDAL_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>

#include "eevp/simulation/vcs_brakepedal_proxy.h"
#include "ara/log/logger.h"

#include "listener/IBrakePedalListener.h"

using namespace ara::com;

namespace eevp
{
    namespace simulation
    {

        class BrakePedalProxyImpl
        {
        public:
            BrakePedalProxyImpl();
            ~BrakePedalProxyImpl();

            void setEventListener(const std::shared_ptr<eevp::simulation::IBrakePedalListener> _listener);
            bool init();

            // getter method
            eevp::simulation::type::VCS_BrakePosn get_BrakePosn();
            eevp::simulation::type::VCS_BrakeSwitch get_BrakeSwitch();
            


        private:
            void FindServiceCallback(
                ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_BrakePedalProxy::HandleType> container,
                ara::com::FindServiceHandle findHandle);

            ara::log::Logger &mLogger;
            std::shared_ptr<eevp::simulation::IBrakePedalListener> listener;
            std::shared_ptr<eevp::simulation::proxy::VCS_BrakePedalProxy> mProxy;
            std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

            std::mutex mHandle;
            std::condition_variable cvHandle;

            eevp::simulation::type::VCS_BrakePosn vcs_BrakePosn;
            eevp::simulation::type::VCS_BrakeSwitch vcs_BrakeSwitch;

        }; // namespace wiper
    } // namespace simulation
} // namespace eevp

#endif //__BRAKEPEDAL_PROXY_IMPL_H_