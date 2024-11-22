#include "proxy/SnsrUssProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        SnsrUssProxyImpl::SnsrUssProxyImpl() : mProxy{nullptr},
                                               mFindHandle{nullptr},
                                               mHandle{},
                                               cvHandle{},
                                               mLogger(ara::log::CreateLogger("SNSR", "SNSR", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        SnsrUssProxyImpl::~SnsrUssProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        SnsrUssProxyImpl::setEventListener(std::shared_ptr<ISnsrUssListener> _listener)
        {
            listener = _listener;
        }

        bool SnsrUssProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_Snsr_USS");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::Snsr_USSProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "SnsrUss StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::type::USSSonarInfo
        SnsrUssProxyImpl::get_Sonar()
        {
            // mLogger.LogInfo() << __func__;
            auto future = mProxy->ntfSonarInfo();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    this->sonarInfo = value.UssSonarinfo;
                    return this->sonarInfo;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call ntfSonarInfo";
            }
            return this->sonarInfo;
        }

        bool SnsrUssProxyImpl::isDetect()
        {
            // mLogger.LogInfo() << __func__;
            auto future = mProxy->isDetect();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return value.detect;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call ntfSonarInfo";
            }
            return false;
        }

        void
        SnsrUssProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::Snsr_USSProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "SnsrUSSProxy isn't empty, unsubscribe";
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "SnsrUSSProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find SnsrUSSProxyContainer, subscribeSnsrUSSService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::Snsr_USSProxy>(container.at(0));

            cvHandle.notify_one();
            return;
        }
    }
}
