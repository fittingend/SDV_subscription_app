#include "proxy/MsgInfoProxyImpl.h"

using namespace batt::msginfo;

namespace eevp
{
    namespace simulation
    {

        MsgInfoProxyImpl::MsgInfoProxyImpl() : mProxy{nullptr},
                                               mFindHandle{nullptr},
                                               mHandle{},
                                               cvHandle{},
                                               mLogger(ara::log::CreateLogger("MSGI", "MSGI", ara::log::LogLevel::kInfo))
        {
            mLogger.LogInfo() << __func__;
        }

        MsgInfoProxyImpl::~MsgInfoProxyImpl()
        {
            if (mProxy)
            {
                mProxy->StopFindService(*mFindHandle);
                mProxy.reset();
            }
        }

        void
        MsgInfoProxyImpl::setEventListener(std::shared_ptr<IMsgInfoListener> _listener)
        {
            listener = _listener;
        }

        bool
        MsgInfoProxyImpl::init()
        {
            mLogger.LogInfo() << __func__;

            ara::core::InstanceSpecifier specifier("ServiceCreator/AA/RPort_MsgInfo");

            auto callback = [&](auto container, auto findHandle)
            {
                FindServiceCallback(container, findHandle);
            };

            std::unique_lock<std::mutex> lock(mHandle);

            // bms::output::OutputData data;
            // data.InterfaceIDforDbg = 0; // 제외하고 기록할 예정이므로 일단 0으로 설정
            // data.VehicleUniqueSnr = rand();
            // data.ChargeStatus = rand() % 256;
            // data.EMS_ConnectionStatus = rand() % 256;
            // data.BattSOC = rand() % 65536;
            // data.DTE = rand() % 65536;
            // data.BatteryStatus = rand() % 65536;
            // data.SOH = rand() % 65536;
            // data.SOE = rand() % 65536;
            // data.TargetSOC = rand() % 256;
            // data.GetCount = rand();
            // data.MissedCount = rand();
            // data.ChargeResult = rand() % 65536;
            // data.ChargedSOE = rand() % 65536;
            // data.ChargedSOC = rand() % 65536;
            // data.ChargeStopReason = rand();

            // // T_MSGINFO 구조체의 필드 채우기
            // for (int i = 0; i < 4; ++i)
            // {
            //     data.Current.tRslt = rand() % 256;
            //     data.Current.XaxisScale = rand() % 256;
            //     data.Current.YaxisValidCnt = rand() % 256;
            //     for (auto &val : data.Current.Ydata)
            //         val = rand() % 256;
            //     data.Current.RCValidCnt = rand() % 256;
            //     for (auto &val : data.Current.RCdata)
            //         val = rand() % 256;
            //     data.Current.MAXdata[0] = rand() % 256;
            //     data.Current.MAXdata[1] = rand() % 256;
            //     data.Current.MINdata[0] = rand() % 256;
            //     data.Current.MINdata[1] = rand() % 256;

            //     // 동일하게 다른 T_MSGINFO 필드도 채우기
            //     data.Voltage = data.Current;
            //     data.SOC = data.Current;
            //     data.Temp = data.Current;
            // }
            // listener->notifyMsgInfo(data);

            auto result = proxy::MsgInfoSrvProxy::StartFindService(callback, specifier);

            if (cvHandle.wait_for(lock, std::chrono::milliseconds(2000)) == std::cv_status::timeout)
            {
                mLogger.LogInfo() << "cbhandle is empty";
                return false;
            }

            if (!result.HasValue())
            {
                mLogger.LogInfo() << "MsgInfoProxy StartFindService() Failed";
                return false;
            }
            else
            {
                mLogger.LogInfo() << "MsgInfo StartFindService() Success";
            }

            return true;
        }

        void
        MsgInfoProxyImpl::FindServiceCallback(
            ara::com::ServiceHandleContainer<batt::msginfo::proxy::MsgInfoSrvProxy::HandleType> container,
            ara::com::FindServiceHandle findHandle)
        {
            mLogger.LogInfo() << __func__;

            std::lock_guard<std::mutex> lock(mHandle);

            int size = container.size();
            mLogger.LogInfo() << "msginfo container size = " << size;

            if (mProxy != nullptr)
            {
                UnsubscribeEvent();

                mFindHandle = nullptr;
                mProxy = nullptr;
            }

            if (container.empty())
            {
                mLogger.LogWarn() << __func__ << "container empty";
                mProxy = nullptr;
                return;
            }

            mFindHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
            mProxy = std::make_shared<batt::msginfo::proxy::MsgInfoSrvProxy>(container.at(0));

            SubscribeEvent();

            cvHandle.notify_one();
            mLogger.LogInfo() << "Find Service complete";
        }

        void
        MsgInfoProxyImpl::SubscribeEvent()
        {
            mLogger.LogInfo() << __func__;

            if (mProxy == nullptr)
            {
                return;
            }

            if (mProxy->ems_MsgInfo.GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed)
            {
                return;
            }

            auto result = mProxy->ems_MsgInfo.SetReceiveHandler(std::bind(&MsgInfoProxyImpl::cbEms_MsgInfo, this));
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to SetReceiveHandler for ems_MsgInfo with " << result.Error().Message();
            }

            mProxy->ems_MsgInfo.Subscribe(10);
            if (!result.HasValue())
            {
                mLogger.LogWarn() << "Failed to Subscribe for ems_MsgInfo with " << result.Error().Message();
            }
        }

        void
        MsgInfoProxyImpl::UnsubscribeEvent()
        {
            if (mProxy == nullptr)
            {
                return;
            }

            mProxy->ems_MsgInfo.Unsubscribe();
        }

        void MsgInfoProxyImpl::cbEms_MsgInfo()
        {
            mLogger.LogInfo() << __func__;

            if (mProxy == nullptr)
            {
                return;
            }

            if (mProxy->ems_MsgInfo.GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed)
            {
                return;
            }

            mProxy->ems_MsgInfo.GetNewSamples([&](auto msg)
                                              {
        bms::output::OutputData outputData = static_cast<bms::output::OutputData>(*msg);
        if (listener != nullptr) {
            listener->notifyMsgInfo(outputData);
        } });
        }

    } // namespace simulation
} // namespace eevp