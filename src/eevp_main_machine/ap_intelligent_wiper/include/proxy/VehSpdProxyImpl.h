#ifndef __VEHSPD_PROXY_IMPL_H_
#define __VEHSPD_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>

#include "eevp/simulation/vcs_vehspd_proxy.h"
#include "ara/log/logger.h"

#include "listener/IVehSpdListener.h"

using namespace ara::com;

namespace eevp
{
    namespace simulation
    {

        class VehSpdProxyImpl
        {
        public:
            VehSpdProxyImpl();
            ~VehSpdProxyImpl();

            void setEventListener(const std::shared_ptr<eevp::simulation::IVehSpdListener> _listener);
            bool init();

            // getter method
            eevp::simulation::type::VCS_VehSpd get_VehSpd();

        private:
            void FindServiceCallback(
                ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_VehSpdProxy::HandleType> container,
                ara::com::FindServiceHandle findHandle);

            ara::log::Logger &mLogger;
            std::shared_ptr<eevp::simulation::IVehSpdListener> listener;
            std::shared_ptr<eevp::simulation::proxy::VCS_VehSpdProxy> mProxy;
            std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

            std::mutex mHandle;
            std::condition_variable cvHandle;

            eevp::simulation::type::VCS_VehSpd vcs_VehSpd;
        };
    } // namespace simulation
} // namespace eevp

#endif //__VEHSPD_PROXY_IMPL_H_