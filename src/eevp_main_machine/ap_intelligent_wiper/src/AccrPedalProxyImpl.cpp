#include "proxy/AccrPedalProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        AccrPedalProxyImpl::AccrPedalProxyImpl() : mProxy{nullptr},
                                           mFindHandle{nullptr},
                                           mHandle{},
                                           cvHandle{},
                                           mLogger(ara::log::CreateLogger("ACCR", "ACCR", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        AccrPedalProxyImpl::~AccrPedalProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        AccrPedalProxyImpl::setEventListener(std::shared_ptr<IAccrPedalListener> _listener)
        {
            listener = _listener;
        }

        bool AccrPedalProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_VCS_AccrPedal");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::VCS_AccrPedalProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "AccrPedal StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::type::VCS_AccrPedal
        AccrPedalProxyImpl::get_accrPedal()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->notifyAccrPedal();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->vcs_accrPedal = value.VCS_AccrPedal;
                    return this->vcs_accrPedal;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call notifyAccrPedal";
            }
            return vcs_accrPedal;
        }

        void
        AccrPedalProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_AccrPedalProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "AccrPedalProxy isn't empty, unsubscribe";
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "AccrPedalProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find AccrPedalProxyContainer, subscribeAccrPedalService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::VCS_AccrPedalProxy>(container.at(0));

            cvHandle.notify_one();
            return;
        }
    }
}
