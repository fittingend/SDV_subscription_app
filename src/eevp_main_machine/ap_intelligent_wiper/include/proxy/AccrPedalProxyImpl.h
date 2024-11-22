#ifndef __ACCRPEDAL_PROXY_IMPL_H_
#define __ACCRPEDAL_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>

#include "eevp/simulation/vcs_accrpedal_proxy.h"
#include "ara/log/logger.h"

#include "listener/IAccrPedalListener.h"

using namespace ara::com;

namespace eevp
{
    namespace simulation
    {

        class AccrPedalProxyImpl
        {
        public:
            AccrPedalProxyImpl();
            ~AccrPedalProxyImpl();

            void setEventListener(const std::shared_ptr<eevp::simulation::IAccrPedalListener> _listener);
            bool init();

            // getter method
            eevp::simulation::type::VCS_AccrPedal get_accrPedal();

        private:
            void FindServiceCallback(
                ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_AccrPedalProxy::HandleType> container,
                ara::com::FindServiceHandle findHandle);

            ara::log::Logger &mLogger;
            std::shared_ptr<eevp::simulation::IAccrPedalListener> listener;
            std::shared_ptr<eevp::simulation::proxy::VCS_AccrPedalProxy> mProxy;
            std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

            std::mutex mHandle;
            std::condition_variable cvHandle;

            eevp::simulation::type::VCS_AccrPedal vcs_accrPedal;
        };
    } // namespace simulation
} // namespace eevp

#endif //__ACCRPEDAL_PROXY_IMPL_H_