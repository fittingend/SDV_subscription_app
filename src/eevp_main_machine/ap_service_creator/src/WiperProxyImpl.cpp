#include "WiperProxyImpl.h"
#include "ServiceCreator.h"
using namespace eevp::simulation;
using namespace eevp::simulation::wiper;

namespace eevp
{
    namespace simulation
    {
        namespace wiper
        {

            WiperProxyImpl::WiperProxyImpl() : mProxy{nullptr},
                                               mFindHandle{nullptr},
                                               mHandle{},
                                               cvHandle{},
                                               mLogger(ara::log::CreateLogger("WPER", "WPER", ara::log::LogLevel::kInfo))
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

                ara::core::InstanceSpecifier specifier("ServiceCreator/AA/RPort_BCM_WiperWash");

                auto callback = [&](auto container, auto findHandle)
                {
                    FindServiceCallback(container, findHandle);
                };
                
                std::unique_lock<std::mutex> lock(mHandle);

                auto result = proxy::BCM_WiperWashProxy::StartFindService(callback, specifier);

                if (cvHandle.wait_for(lock, std::chrono::milliseconds(1000)) == std::cv_status::timeout)
                {
                    mLogger.LogInfo() << "cvHandle is empty";
                }

                if (!result.HasValue())
                {
                    mLogger.LogInfo() << "BCM_WiperWashProxy StartFindService() Failed";
                    return false;
                }
                else
                {
                    mLogger.LogInfo() << "BCM_WiperWashProxy StartFindService() Success";
                    SubscribeWiperLevel();
                    SubscribeWiperInterval();
                }

                // for (int i = 0; i < 20; i++)
                // {
                //     if (this->mServiceFound)
                //     {
                //         LOG_INFO() << "Zone4WiperProxy Start Find Service Success\n";
                //         SubscribeEvent();
                //         SubscribeField();
                //         return true;
                //     }

                //     std::this_thread::sleep_for(std::chrono::milliseconds(20));
                // }

                return true;
            }

            void
            WiperProxyImpl::getWiperRecv()
            {
                switch (ServiceCreator::wiperRecv.wipingLevel)
                {
                case BCM_WipingLevel::HIGH:
                    mLogger.LogInfo() << "wiperRecv: [HIGH, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::LOW:
                    mLogger.LogInfo() << "wiperRecv: [LOW, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::MEDIUM:
                    mLogger.LogInfo() << "wiperRecv: [MEDIUM, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::STOP:
                    mLogger.LogInfo() << "wiperRecv: [STOP, " << ServiceCreator::wiperRecv.wipingInterval << "]";
                    break;
                default:
                    break;
                }
            }

            void
            WiperProxyImpl::getWiperSend()
            {
                switch (ServiceCreator::wiperSend.wipingLevel)
                {
                case BCM_WipingLevel::HIGH:
                    mLogger.LogInfo() << "wiperSend: [HIGH, " << ServiceCreator::wiperSend.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::LOW:
                    mLogger.LogInfo() << "wiperSend: [LOW, " << ServiceCreator::wiperSend.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::MEDIUM:
                    mLogger.LogInfo() << "wiperSend: [MEDIUM, " << ServiceCreator::wiperSend.wipingInterval << "]";
                    break;
                case BCM_WipingLevel::STOP:
                    mLogger.LogInfo() << "wiperSend: [STOP, " << ServiceCreator::wiperSend.wipingInterval << "]";
                    break;
                default:
                    break;
                }
            }

            eevp::simulation::BCM_ReturnCode
            WiperProxyImpl::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
            {
                mLogger.LogInfo() << __func__;

                if (mProxy == nullptr)
                {
                    return BCM_ReturnCode::SUCCESS;
                }

                auto future = mProxy->setWipingLevel(wipingLevel);
                return BCM_ReturnCode::SUCCESS;
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
                mLogger.LogInfo() << __func__;
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
                    if (listener != nullptr) {
                        listener->getWipingLevel();
                    } });
            }

            void
            WiperProxyImpl::cbWiperInterval()
            {
                mLogger.LogInfo() << __func__;

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
        if (listener != nullptr) {
            listener->getWipingInterval();
        } });
            }
        }
    }
}
