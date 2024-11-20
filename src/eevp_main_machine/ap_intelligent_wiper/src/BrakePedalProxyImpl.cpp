#include "proxy/BrakePedalProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        BrakePedalProxyImpl::BrakePedalProxyImpl() : mProxy{nullptr},
                                                     mFindHandle{nullptr},
                                                     mHandle{},
                                                     cvHandle{},
                                                     mLogger(ara::log::CreateLogger("BKPD", "BKPD", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        BrakePedalProxyImpl::~BrakePedalProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        BrakePedalProxyImpl::setEventListener(std::shared_ptr<IBrakePedalListener> _listener)
        {
            listener = _listener;
        }

        bool BrakePedalProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_VCS_BrakePedal");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::VCS_BrakePedalProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "BrakePedal StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::type::VCS_BrakePosn
        BrakePedalProxyImpl::get_BrakePosn()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->notifyBrakeStatus();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->vcs_BrakePosn = value.VCS_BrakePosn;
                    return this->vcs_BrakePosn;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call notifyBrakeStatus";
            }
            return this->vcs_BrakePosn;
        }

        eevp::simulation::type::VCS_BrakeSwitch
        BrakePedalProxyImpl::get_BrakeSwitch()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->notifyBrakeSwitch();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->vcs_BrakeSwitch = value.VCS_BrakeSwitch;
                    return this->vcs_BrakeSwitch;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call notifyBrakeSwitch";
            }
            return this->vcs_BrakeSwitch;
        }

        void
        BrakePedalProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_BrakePedalProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "BrakePedalProxy isn't empty, unsubscribe";
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "BrakePedalProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find BrakePedalProxyContainer, subscribeBrakePedalService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::VCS_BrakePedalProxy>(container.at(0));

            cvHandle.notify_one();
            return;
        }
    }
}
