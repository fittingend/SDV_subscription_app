#include "proxy/GearProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        GearProxyImpl::GearProxyImpl() : mProxy{nullptr},
                                         mFindHandle{nullptr},
                                         mHandle{},
                                         cvHandle{},
                                         mLogger(ara::log::CreateLogger("GEAR", "GEAR", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        GearProxyImpl::~GearProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        GearProxyImpl::setEventListener(std::shared_ptr<IGearListener> _listener)
        {
            listener = _listener;
        }

        bool GearProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_VCS_Gear");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::VCS_GearProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "Gear StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::type::VCS_Gear
        GearProxyImpl::get_Gear()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->notifyGear();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->vcs_Gear = value.VCS_Gear;
                    return this->vcs_Gear;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call notifyGear";
            }
            return this->vcs_Gear;
        }

        void GearProxyImpl::set_Gear()
        {
            mLogger.LogInfo() << __func__;
            auto future = mProxy->setTarget(this->vcs_Gear);
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call setTarget";
            }
            return;
        }

        void
        GearProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_GearProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "GearProxy isn't empty, unsubscribe";
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "GearProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find GearProxyContainer, subscribeGearService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::VCS_GearProxy>(container.at(0));

            cvHandle.notify_one();
            return;
        }
    }
}
