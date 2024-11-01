#include "WiperProxyImpl.h"
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
                                    mLogger(ara::log::CreateLogger("INTW", "WIPR", ara::log::LogLevel::kInfo))
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
    if (!result.HasValue()) {
        mLogger.LogInfo() << "SoaRoaProxy StartFindService() Failed";
        return false;
    }

    return true;
}

bool 
WiperProxyImpl::getBCM_WipingLevel(eevp::simulation::BCM_WipingLevel& wipinglevel)
{
    mLogger.LogInfo() << __func__;
    if (mProxy == nullptr) {
        return false;
    }
    auto future = mProxy->wiperLevel.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
			wipinglevel = static_cast<eevp::simulation::BCM_WipingLevel>(result.Value());
            return true;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call BCM_WipingLevel's Getter";
    }

    return false;
}

eevp::simulation::BCM_ReturnCode WiperProxyImpl::startWiping()
{
    mLogger.LogInfo() << __func__;
    if (mProxy == nullptr) {
        return eevp::simulation::BCM_ReturnCode::FAIL_OTHERS;
    }

    auto future = mProxy->startWiping();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready) {
        auto result = future.GetResult();
        if (result.HasValue()) {
            auto value = result.Value();
            return eevp::simulation::BCM_ReturnCode::SUCCESS;
        } else {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    } else {
        mLogger.LogError() << "Timeout to call RequestRearCurtainOperation";
    }

    return eevp::simulation::BCM_ReturnCode::FAIL_TIMEOUT;
}

/*
eevp::simulation::BCM_ReturnCode WiperProxyImpl::getWipingInterval()
{
    mLogger.LogInfo() << __func__;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::uint16_t wipingInterval;
    auto future = mProxy->wiperInterval.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready)
    {
        auto result = future.GetResult();
        if (result.HasValue())
        {
            wipingInterval = static_cast<std::uint16_t>(result.Value());
        }
        else
        {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    }
    else
    {
        mLogger.LogError() << "Timeout to call soaWiperStatus's Getter";
    }
    ServiceCreator::wiperSend.wipingInterval = wipingInterval;
    mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingInterval) << ")";

    return BCM_ReturnCode::SUCCESS;
}

eevp::simulation::BCM_WipingLevel WiperProxyImpl::getWipingLevel()
{
    mLogger.LogInfo() << __func__;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    eevp::simulation::BCM_WipingLevel wipingLevel;
    auto future = mProxy->wiperLevel.Get();
    auto status = future.wait_for(std::chrono::milliseconds(10));
    if (status == future_status::ready)
    {
        auto result = future.GetResult();
        if (result.HasValue())
        {
            wipingLevel = static_cast<eevp::simulation::BCM_WipingLevel>(result.Value());
        }
        else
        {
            mLogger.LogError() << __func__ << ": Return error with " << result.Error().Message();
        }
    }
    else
    {
        mLogger.LogError() << "Timeout to call soaWiperStatus's Getter";
    }
    ServiceCreator::wiperSend.wipingLevel = wipingLevel;
    mLogger.LogInfo() << __func__ << "(" << static_cast<uint8_t>(wipingLevel) << ")";

    return wipingLevel;
}

eevp::simulation::BCM_ReturnCode
WiperProxyImpl::setWipingLevel(const eevp::simulation::BCM_WipingLevel &wipingLevel)
{
    mLogger.LogInfo() << __func__;

    if (mProxy == nullptr)
    {
        mLogger.LogInfo() << "setWipingLevel: mProxy is nullptr";
        return BCM_ReturnCode::SUCCESS;
    }

    auto future = mProxy->setWipingLevel(wipingLevel);
    return BCM_ReturnCode::SUCCESS;
}
*/
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

}
}
