#include "proxy/WiperProxyImpl.h"
using namespace eevp::simulation;
using namespace ara::core;

namespace eevp
{
    namespace simulation
    {

        WiperProxyImpl::WiperProxyImpl() : mProxy{nullptr},
                                           mFindHandle{nullptr},
                                           mHandle{},
                                           cvHandle{},
                                           mLogger(ara::log::CreateLogger("WIPR", "WIPR", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        WiperProxyImpl::~WiperProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        WiperProxyImpl::setEventListener(std::shared_ptr<IWiperListener> _listener)
        {
            listener = _listener;
        }

        bool WiperProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;
            ara::core::InstanceSpecifier specifier("IntelligentWiper/AA/RPort_BCM_WiperWash");
            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);
            auto result = proxy::BCM_WiperWashProxy::StartFindService(callback, specifier);
            if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cvHandle is empty";
                return false;
            }
            if (!result.HasValue())
            {
                mLogger.LogInfo() << "Wiper StartFindService() Failed";
                return false;
            }

            return true;
        }

        eevp::simulation::BCM_WipingLevel
        WiperProxyImpl::get_wipingLevel()
        {
            // mLogger.LogInfo() << __func__;
            if (mProxy == nullptr)
            {
                return this->mWipingLevel;
            }
            auto future = mProxy->wiperLevel.Get();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    this->mWipingLevel = static_cast<eevp::simulation::BCM_WipingLevel>(result.Value());
                    mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(this->mWipingLevel) << ")";
                    return this->mWipingLevel;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call BCM_WipingLevel's Getter";
            }

            return this->mWipingLevel;
        }

        std::uint16_t
        WiperProxyImpl::get_wipingInterval()
        {
            // mLogger.LogInfo() << __func__;
            if (mProxy == nullptr)
            {
                return this->mWipingInterval;
            }
            auto future = mProxy->wiperInterval.Get();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    mWipingInterval = static_cast<std::uint16_t>(result.Value());
                    mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(this->mWipingInterval) << ")";
                    return this->mWipingInterval;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call BCM_WipingInterval's Getter";
            }

            return this->mWipingInterval;
        }

        eevp::simulation::BCM_ReturnCode WiperProxyImpl::startWiping()
        {
            // mLogger.LogInfo() << __func__;
            if (mProxy == nullptr)
            {
                return eevp::simulation::BCM_ReturnCode::FAIL_OTHERS;
            }

            auto future = mProxy->startWiping();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return eevp::simulation::BCM_ReturnCode::SUCCESS;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call startWiping";
            }

            return eevp::simulation::BCM_ReturnCode::FAIL_TIMEOUT;
        }

        eevp::simulation::BCM_ReturnCode WiperProxyImpl::stopWiping()
        {
            // mLogger.LogInfo() << __func__;

            auto future = mProxy->stopWiping();
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return eevp::simulation::BCM_ReturnCode::SUCCESS;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call stopWiping";
            }

            return eevp::simulation::BCM_ReturnCode::FAIL_TIMEOUT;
        }

        eevp::simulation::BCM_ReturnCode
        WiperProxyImpl::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
        {
            // mLogger.LogInfo() << __func__;

            auto future = mProxy->setWipingLevel(wipingLevel);
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return eevp::simulation::BCM_ReturnCode::SUCCESS;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call setwipingLevel";
            }

            return eevp::simulation::BCM_ReturnCode::FAIL_TIMEOUT;
        }

        eevp::simulation::BCM_ReturnCode
        WiperProxyImpl::setWipingInterval(const std::uint16_t &wipingInterval)
        {
            // mLogger.LogInfo() << __func__;

            auto future = mProxy->setWipingInterval(wipingInterval);
            auto status = future.wait_for(std::chrono::milliseconds(10));
            if (status == future_status::ready)
            {
                auto result = future.GetResult();
                if (result.HasValue())
                {
                    auto value = result.Value();
                    return eevp::simulation::BCM_ReturnCode::SUCCESS;
                }
                else
                {
                    mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
                }
            }
            else
            {
                mLogger.LogError() << "Timeout to call setwipingInterval";
            }

            return eevp::simulation::BCM_ReturnCode::FAIL_TIMEOUT;
        }

        void
        WiperProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<eevp::simulation::proxy::BCM_WiperWashProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;
            std::lock_guard<std::mutex> lock(mHandle);

            if (mProxy != nullptr)
            {
                mLogger.LogInfo() << "wiperProxy isn't empty, unsubscribe";
                UnsubscribeField();
                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogInfo() << "wiperProxyContainer is empty";
                mProxy = nullptr;
                return;
            }

            mLogger.LogInfo() << "Find wiperProxyContainer, subscribeWiperService";

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<proxy::BCM_WiperWashProxy>(container.at(0));

            SubscribeWiperLevel();

            SubscribeWiperInterval();

            cvHandle.notify_one();
            return;
        }

        void
        WiperProxyImpl::SubscribeWiperLevel()
        {
            mLogger.LogInfo() << __func__;

            if (mProxy == nullptr)
            {
                mLogger.LogInfo() << "mProxy is nullptr";
                return;
            }

            if (mProxy->wiperLevel.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed)
            {
                return;
            }

            auto result = mProxy->wiperLevel.SetReceiveHandler(std::bind(&WiperProxyImpl::cbWiperLevel, this));
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to SetReceiveHandler for cbWiperLevel with " << result.Error().Message();
            }

            result = mProxy->wiperLevel.Subscribe(10);
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to Subscribe for cbWiperLevel with " << result.Error().Message();
            }
            mLogger.LogInfo() << "SubscribeWiperLevel() Success";
        }

        void
        WiperProxyImpl::SubscribeWiperInterval()
        {
            mLogger.LogInfo() << __func__;

            if (mProxy == nullptr)
            {
                mLogger.LogInfo() << "mProxy is nullptr";
                return;
            }

            if (mProxy->wiperInterval.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed)
            {
                return;
            }

            auto result = mProxy->wiperInterval.SetReceiveHandler(std::bind(&WiperProxyImpl::cbWiperInterval, this));
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to SetReceiveHandler for cbWiperInterval with " << result.Error().Message();
            }

            result = mProxy->wiperInterval.Subscribe(10);
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to Subscribe for cbWiperInterval with " << result.Error().Message();
            }
            mLogger.LogInfo() << "SubscribeWiperInterval() Success";
        }

        void WiperProxyImpl::UnsubscribeField()
        {
            mLogger.LogInfo() << __func__;
            if (mProxy == nullptr)
            {
                return;
            }
            mProxy->wiperLevel.Unsubscribe();
            mProxy->wiperInterval.Unsubscribe();
        }

        void
        WiperProxyImpl::cbWiperLevel()
        {
            // mLogger.LogInfo() << __func__;

            if (mProxy == nullptr)
            {
                return;
            }

            if (mProxy->wiperLevel.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed)
            {
                return;
            }

            mProxy->wiperLevel.GetNewSamples([&](auto msg)
                                             {
            this->mWipingLevel = static_cast<eevp::simulation::BCM_WipingLevel>(*msg);
                    if (listener != nullptr) {
                        // mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingLevel) << ")";
                    } });
        }

        void
        WiperProxyImpl::cbWiperInterval()
        {
            // mLogger.LogInfo() << __func__;

            std::uint16_t wipingInterval;
            if (mProxy == nullptr)
            {
                return;
            }

            if (mProxy->wiperInterval.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed)
            {
                return;
            }

            mProxy->wiperInterval.GetNewSamples([&](auto msg)
                                                {
                this->mWipingInterval = static_cast<std::uint16_t>(*msg);
                    if (listener != nullptr) {
                        // mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingInterval) << ")";
                    } });
        }

    }
}
