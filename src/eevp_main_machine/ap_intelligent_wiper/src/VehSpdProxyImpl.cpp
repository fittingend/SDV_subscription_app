#include "proxy/VehSpdProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        VehSpdProxyImpl::VehSpdProxyImpl() : mProxy{nullptr},
                                             mFindHandle{nullptr},
                                             mHandle{},
                                             cvHandle{},
                                             mLogger(ara::log::CreateLogger("VSPD", "VSPD", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        VehSpdProxyImpl::~VehSpdProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        VehSpdProxyImpl::setEventListener(std::shared_ptr<IVehSpdListener> _listener)
        {
            listener = _listener;
        }

        bool VehSpdProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_VCS_VehSpd");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::VCS_VehSpdProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "VehSpd StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::type::VCS_VehSpd
        VehSpdProxyImpl::get_VehSpd()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->notifyVehSpd();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->vcs_VehSpd = value.VCS_VehSpd;
                    return this->vcs_VehSpd;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call notifyVehSpd";
            }
            return this->vcs_VehSpd;
        }

        void
        VehSpdProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_VehSpdProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "VehSpdProxy isn't empty, unsubscribe";
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "VehSpdProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find VehSpdProxyContainer, subscribeVehSpdService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::VCS_VehSpdProxy>(container.at(0));

            cvHandle.notify_one();
            return;
        }
    }
}
