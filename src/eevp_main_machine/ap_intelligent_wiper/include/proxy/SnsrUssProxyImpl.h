#ifndef __SNSRUSS_PROXY_IMPL_H_
#define __SNSRUSS_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <typeinfo>

#include "eevp/simulation/snsr_uss_proxy.h"
#include "ara/log/logger.h"

#include "listener/ISnsrUssListener.h"

using namespace ara::com;

namespace eevp
{
    namespace simulation
    {

        class SnsrUssProxyImpl
        {
        public:
            SnsrUssProxyImpl();
            ~SnsrUssProxyImpl();

            void setEventListener(const std::shared_ptr<eevp::simulation::ISnsrUssListener> _listener);
            bool init();

            // getter method
            eevp::simulation::type::USSSonarInfo get_Sonar();
            bool isDetect();

        private:
            void FindServiceCallback(
                ara::com::ServiceHandleContainer<eevp::simulation::proxy::Snsr_USSProxy::HandleType> container,
                ara::com::FindServiceHandle findHandle);

            ara::log::Logger &mLogger;
            std::shared_ptr<eevp::simulation::ISnsrUssListener> listener;
            std::shared_ptr<eevp::simulation::proxy::Snsr_USSProxy> mProxy;
            std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

            std::mutex mHandle;
            std::condition_variable cvHandle;

            eevp::simulation::type::USSSonarInfo sonarInfo;
        };
    } // namespace simulation
} // namespace eevp

#endif //__SNSRUSS_PROXY_IMPL_H_