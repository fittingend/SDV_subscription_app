///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, ARA::COM Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : main_ipc_routingipc_proxy.h
/// SERVICE INTERFACE NAME            : Main_IPC_RoutingIPC
/// GENERATED DATE                    : 2024-07-19 07:35:29
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_MAIN_IPC_ROUTINGIPC_PROXY_H
#define PARA_COM_GEN_SERVICE_INTERFACE_MAIN_IPC_ROUTINGIPC_PROXY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "main_ipc_routingipc_common.h"
#include "para/com/proxy/proxy_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace ipchandler
{
namespace service
{
/// @uptrace{SWS_CM_01007}
namespace proxy
{
/// @uptrace{SWS_CM_01009}
namespace events
{
/// @uptrace{SWS_CM_00003}
class PeriodicSystemInfo
{
public:
    /// @brief Type alias for type of event data
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using SampleType = eevp::ipchandler::type::PowerState;
    /// @brief Constructor
    explicit PeriodicSystemInfo(para::com::ProxyInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~PeriodicSystemInfo() = default;
    /// @brief Delete copy constructor
    PeriodicSystemInfo(const PeriodicSystemInfo& other) = delete;
    /// @brief Delete copy assignment
    PeriodicSystemInfo& operator=(const PeriodicSystemInfo& other) = delete;
    /// @brief Move constructor
    PeriodicSystemInfo(PeriodicSystemInfo&& other) noexcept : mInterface(other.mInterface)
    {
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Move assignment
    PeriodicSystemInfo& operator=(PeriodicSystemInfo&& other) noexcept
    {
        mInterface = other.mInterface;
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
        return *this;
    }
    /// @brief Requests "Subscribe" message to Communication Management
    /// @uptrace{SWS_CM_00141}
    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        if (mInterface->GetSubscriptionState(kCallSign) == ara::com::SubscriptionState::kSubscribed)
        {
            if ((maxSampleCount != 0) && (maxSampleCount != mMaxSampleCount))
            {
                return ara::core::Result<void>(ara::com::ComErrc::kMaxSampleCountNotRealizable);
            }
        }
        mMaxSampleCount = maxSampleCount;
        return mInterface->SubscribeEvent(kCallSign, mMaxSampleCount);
    }
    /// @brief Requests "StopSubscribe" message to Communication Management
    /// @uptrace{SWS_CM_00151}
    void Unsubscribe()
    {
        mInterface->UnsubscribeEvent(kCallSign);
    }
    /// @brief Return state for current subscription
    /// @uptrace{SWS_CM_00316}
    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return mInterface->GetSubscriptionState(kCallSign);
    }
    /// @brief Register callback to catch changes of subscription state
    /// @uptrace{SWS_CM_00333}
    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        mSubscriptionStateChangeHandler = std::move(handler);
        return mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Unset bound callback by SetSubscriptionStateChangeHandler
    /// @uptrace{SWS_CM_00334}
    void UnsetSubscriptionStateChangeHandler()
    {
        mSubscriptionStateChangeHandler = nullptr;
        mInterface->UnsetSubscriptionStateChangeHandler(kCallSign);
    }
    /// @brief Get received event data from cache
    /// @uptrace{SWS_CM_00701}
    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        auto samples = mInterface->GetNewSamples(kCallSign, maxNumberOfSamples);
        for (const auto& sample : samples)
        {
            para::serializer::Deserializer deserializer{sample};
            SampleType data;
            deserializer.read(data);
            f(ara::com::make_sample_ptr<const SampleType>(data));
        }
        return samples.size();
    }
    /// @brief Register callback to catch that event data is received
    /// @uptrace{SWS_CM_00181}
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        mEventReceiveHandler = std::move(handler);
        return mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler); 
    }
    /// @brief Unset bound callback by SetReceiveHandler
    /// @uptrace{SWS_CM_00183}
    ara::core::Result<void> UnsetReceiveHandler()
    {
        mEventReceiveHandler = nullptr;
        return mInterface->UnsetEventReceiveHandler(kCallSign);
    }
    /// @brief Returns the count of free event cache
    /// @uptrace{SWS_CM_00705}
    ara::core::Result<size_t> GetFreeSampleCount() const noexcept
    {
        auto ret = mInterface->GetFreeSampleCount(kCallSign);
        if (ret < 0)
        {
            return ara::core::Result<size_t>(ara::core::CoreErrc::kInvalidArgument);
        }
        return ret;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_10475}
    /// @uptrace{SWS_CM_90431}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    para::com::ProxyInterface* mInterface;
    size_t mMaxSampleCount{0};
    ara::com::EventReceiveHandler mEventReceiveHandler{nullptr};
    ara::com::SubscriptionStateChangeHandler mSubscriptionStateChangeHandler{nullptr};
    const std::string kCallSign = {"PeriodicSystemInfo"};
};
/// @uptrace{SWS_CM_00003}
class SystemControlRequest
{
public:
    /// @brief Type alias for type of event data
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using SampleType = eevp::ipchandler::type::SysCtrlReq;
    /// @brief Constructor
    explicit SystemControlRequest(para::com::ProxyInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~SystemControlRequest() = default;
    /// @brief Delete copy constructor
    SystemControlRequest(const SystemControlRequest& other) = delete;
    /// @brief Delete copy assignment
    SystemControlRequest& operator=(const SystemControlRequest& other) = delete;
    /// @brief Move constructor
    SystemControlRequest(SystemControlRequest&& other) noexcept : mInterface(other.mInterface)
    {
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Move assignment
    SystemControlRequest& operator=(SystemControlRequest&& other) noexcept
    {
        mInterface = other.mInterface;
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
        return *this;
    }
    /// @brief Requests "Subscribe" message to Communication Management
    /// @uptrace{SWS_CM_00141}
    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        if (mInterface->GetSubscriptionState(kCallSign) == ara::com::SubscriptionState::kSubscribed)
        {
            if ((maxSampleCount != 0) && (maxSampleCount != mMaxSampleCount))
            {
                return ara::core::Result<void>(ara::com::ComErrc::kMaxSampleCountNotRealizable);
            }
        }
        mMaxSampleCount = maxSampleCount;
        return mInterface->SubscribeEvent(kCallSign, mMaxSampleCount);
    }
    /// @brief Requests "StopSubscribe" message to Communication Management
    /// @uptrace{SWS_CM_00151}
    void Unsubscribe()
    {
        mInterface->UnsubscribeEvent(kCallSign);
    }
    /// @brief Return state for current subscription
    /// @uptrace{SWS_CM_00316}
    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return mInterface->GetSubscriptionState(kCallSign);
    }
    /// @brief Register callback to catch changes of subscription state
    /// @uptrace{SWS_CM_00333}
    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        mSubscriptionStateChangeHandler = std::move(handler);
        return mInterface->SetSubscriptionStateChangeHandler(kCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Unset bound callback by SetSubscriptionStateChangeHandler
    /// @uptrace{SWS_CM_00334}
    void UnsetSubscriptionStateChangeHandler()
    {
        mSubscriptionStateChangeHandler = nullptr;
        mInterface->UnsetSubscriptionStateChangeHandler(kCallSign);
    }
    /// @brief Get received event data from cache
    /// @uptrace{SWS_CM_00701}
    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        auto samples = mInterface->GetNewSamples(kCallSign, maxNumberOfSamples);
        for (const auto& sample : samples)
        {
            para::serializer::Deserializer deserializer{sample};
            SampleType data;
            deserializer.read(data);
            f(ara::com::make_sample_ptr<const SampleType>(data));
        }
        return samples.size();
    }
    /// @brief Register callback to catch that event data is received
    /// @uptrace{SWS_CM_00181}
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        mEventReceiveHandler = std::move(handler);
        return mInterface->SetEventReceiveHandler(kCallSign, mEventReceiveHandler); 
    }
    /// @brief Unset bound callback by SetReceiveHandler
    /// @uptrace{SWS_CM_00183}
    ara::core::Result<void> UnsetReceiveHandler()
    {
        mEventReceiveHandler = nullptr;
        return mInterface->UnsetEventReceiveHandler(kCallSign);
    }
    /// @brief Returns the count of free event cache
    /// @uptrace{SWS_CM_00705}
    ara::core::Result<size_t> GetFreeSampleCount() const noexcept
    {
        auto ret = mInterface->GetFreeSampleCount(kCallSign);
        if (ret < 0)
        {
            return ara::core::Result<size_t>(ara::core::CoreErrc::kInvalidArgument);
        }
        return ret;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_10475}
    /// @uptrace{SWS_CM_90431}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    para::com::ProxyInterface* mInterface;
    size_t mMaxSampleCount{0};
    ara::com::EventReceiveHandler mEventReceiveHandler{nullptr};
    ara::com::SubscriptionStateChangeHandler mSubscriptionStateChangeHandler{nullptr};
    const std::string kCallSign = {"SystemControlRequest"};
};
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_01015}
namespace methods
{
/// @uptrace{SWS_CM_00006}
class ASMInfoRequest
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
    };
    /// @brief Constructor
    explicit ASMInfoRequest(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~ASMInfoRequest() = default;
    /// @brief
    ASMInfoRequest(const ASMInfoRequest& other) = delete;
    ASMInfoRequest& operator=(const ASMInfoRequest& other) = delete;
    /// @brief Move constructor
    ASMInfoRequest(ASMInfoRequest&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    ASMInfoRequest& operator=(ASMInfoRequest&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()()
    {
        para::serializer::Serializer __serializer__{};
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<ASMInfoRequest::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            ASMInfoRequest::Output output;
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<ASMInfoRequest::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"ASMInfoRequest"};
};
/// @uptrace{SWS_CM_00006}
class GetOneTimeSystemInfo
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
        eevp::ipchandler::type::OneTimeSysInfo info;
    };
    /// @brief Constructor
    explicit GetOneTimeSystemInfo(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~GetOneTimeSystemInfo() = default;
    /// @brief
    GetOneTimeSystemInfo(const GetOneTimeSystemInfo& other) = delete;
    GetOneTimeSystemInfo& operator=(const GetOneTimeSystemInfo& other) = delete;
    /// @brief Move constructor
    GetOneTimeSystemInfo(GetOneTimeSystemInfo&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    GetOneTimeSystemInfo& operator=(GetOneTimeSystemInfo&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()()
    {
        para::serializer::Serializer __serializer__{};
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<GetOneTimeSystemInfo::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            GetOneTimeSystemInfo::Output output;
            deserializer.read(output.info);
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<GetOneTimeSystemInfo::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"GetOneTimeSystemInfo"};
};
/// @uptrace{SWS_CM_00006}
class SetAPSystemInfo
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
    };
    /// @brief Constructor
    explicit SetAPSystemInfo(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~SetAPSystemInfo() = default;
    /// @brief
    SetAPSystemInfo(const SetAPSystemInfo& other) = delete;
    SetAPSystemInfo& operator=(const SetAPSystemInfo& other) = delete;
    /// @brief Move constructor
    SetAPSystemInfo(SetAPSystemInfo&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    SetAPSystemInfo& operator=(SetAPSystemInfo&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()(const eevp::type::String& apVersion)
    {
        para::serializer::Serializer __serializer__{};
        __serializer__.write(apVersion);
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<SetAPSystemInfo::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            SetAPSystemInfo::Output output;
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<SetAPSystemInfo::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"SetAPSystemInfo"};
};
/// @uptrace{SWS_CM_00006}
class SystemControlResponse
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
    };
    /// @brief Constructor
    explicit SystemControlResponse(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~SystemControlResponse() = default;
    /// @brief
    SystemControlResponse(const SystemControlResponse& other) = delete;
    SystemControlResponse& operator=(const SystemControlResponse& other) = delete;
    /// @brief Move constructor
    SystemControlResponse(SystemControlResponse&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    SystemControlResponse& operator=(SystemControlResponse&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()(const eevp::ipchandler::type::SysCtrlResp& response)
    {
        para::serializer::Serializer __serializer__{};
        __serializer__.write(response);
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<SystemControlResponse::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            SystemControlResponse::Output output;
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<SystemControlResponse::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"SystemControlResponse"};
};
} /// namespace methods
/// @uptrace{SWS_CM_00004}
class Main_IPC_RoutingIPCProxy
{
public: 
    /// @uptrace{SWS_CM_00312}
    class HandleType
    {
    public:
        HandleType() = default;
        HandleType(ara::core::InstanceSpecifier instanceSpecifier, para::com::ServiceHandle service)
            : mInstanceSpecifier(std::move(instanceSpecifier)), mServiceHandle(service)
        {
        }
        ~HandleType() = default;
        /// @uptrace{SWS_CM_00317}
        HandleType(const HandleType& other) = default;
        HandleType& operator=(const HandleType& other) = default;
        /// @uptrace{SWS_CM_00318}
        HandleType(HandleType&& other) = default;
        HandleType& operator=(HandleType&& other) = default;
        /// @brief Return instance specifier
        ara::core::InstanceSpecifier GetInstanceSpecifier()
        {
            return mInstanceSpecifier;
        }
        /// @brief Return handle for bound service
        para::com::ServiceHandle GetServiceHandle()
        {
            return mServiceHandle;
        }
        /// @brief Is equal to operator
        inline bool operator==(const HandleType& other) const
        {
            return mInstanceSpecifier == other.mInstanceSpecifier && mServiceHandle == other.mServiceHandle;
        }
        /// @brief Less than operator
        inline bool operator<(const HandleType& other) const
        {
            return mServiceHandle.version < other.mServiceHandle.version;
        }
        
    private:
        ara::core::InstanceSpecifier mInstanceSpecifier{"undefined"};
        para::com::ServiceHandle mServiceHandle;
    };
    /// @brief Requests "FindService" message to Communication Management with callback
    /// @uptrace{SWS_CM_00623}
    static ara::core::Result<ara::com::FindServiceHandle> StartFindService(ara::com::FindServiceHandler<Main_IPC_RoutingIPCProxy::HandleType> handler, ara::core::InstanceSpecifier instanceSpec)
    {
        ara::com::FindServiceHandle findHandle = para::com::ProxyInterface::GetFindServiceHandle(instanceSpec);
        auto findCallback = [&, handler, findHandle, instanceSpec](std::vector<para::com::ServiceHandle> services) {
            ara::com::ServiceHandleContainer<Main_IPC_RoutingIPCProxy::HandleType> handleContainer;
            for (auto& service : services)
            {
                handleContainer.emplace_back(instanceSpec, service);
            }
            handler(handleContainer, findHandle);
        };
        return para::com::ProxyInterface::StartFindService(instanceSpec, findCallback);
    }
    /// @brief Send "FindService" message to Communication Management at once
    /// @uptrace{SWS_CM_00622}
    static ara::core::Result<ara::com::ServiceHandleContainer<Main_IPC_RoutingIPCProxy::HandleType>> FindService(ara::core::InstanceSpecifier instanceSpec)
    {
        auto result = para::com::ProxyInterface::FindService(instanceSpec);
        if (!result.HasValue())
        {
            return ara::core::Result<ara::com::ServiceHandleContainer<Main_IPC_RoutingIPCProxy::HandleType>>::FromError(result.Error());
        }
        ara::com::ServiceHandleContainer<Main_IPC_RoutingIPCProxy::HandleType> handleContainer;
        const auto& services = result.Value();
        for (auto& service : services)
        {
            handleContainer.emplace_back(instanceSpec, service);
        }
        return handleContainer;
    }
    /// @brief Constructor
    /// @note This function shall be called after processing of FindService/StartFindService was completed
    /// @uptrace{SWS_CM_00004, SWS_CM_00131}
    explicit Main_IPC_RoutingIPCProxy(HandleType& handle)
        : mHandle(handle)
        , mInterface(std::make_unique<para::com::ProxyInterface>(handle.GetInstanceSpecifier(), handle.GetServiceHandle()))
        , PeriodicSystemInfo(mInterface.get())
        , SystemControlRequest(mInterface.get())
        , ASMInfoRequest(mInterface.get())
        , GetOneTimeSystemInfo(mInterface.get())
        , SetAPSystemInfo(mInterface.get())
        , SystemControlResponse(mInterface.get())
    {
    }
    /// @brief Destructor
    /// @uptrace{SWS_CM_10446}
    ~Main_IPC_RoutingIPCProxy() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00136}
    Main_IPC_RoutingIPCProxy(Main_IPC_RoutingIPCProxy& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00136}
    Main_IPC_RoutingIPCProxy& operator=(const Main_IPC_RoutingIPCProxy& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00137}
    Main_IPC_RoutingIPCProxy(Main_IPC_RoutingIPCProxy&& other) noexcept
        : mHandle(std::move(other.mHandle))
        , mInterface(std::move(other.mInterface))
        , PeriodicSystemInfo(std::move(other.PeriodicSystemInfo))
        , SystemControlRequest(std::move(other.SystemControlRequest))
        , ASMInfoRequest(std::move(other.ASMInfoRequest))
        , GetOneTimeSystemInfo(std::move(other.GetOneTimeSystemInfo))
        , SetAPSystemInfo(std::move(other.SetAPSystemInfo))
        , SystemControlResponse(std::move(other.SystemControlResponse))
    {
        mInterface->StopFindService();
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00137}
    Main_IPC_RoutingIPCProxy& operator=(Main_IPC_RoutingIPCProxy&& other) noexcept
    {
        mHandle = std::move(other.mHandle);
        mInterface = std::move(other.mInterface);
        mInterface->StopFindService();
        PeriodicSystemInfo = std::move(other.PeriodicSystemInfo);
        SystemControlRequest = std::move(other.SystemControlRequest);
        ASMInfoRequest = std::move(other.ASMInfoRequest);
        GetOneTimeSystemInfo = std::move(other.GetOneTimeSystemInfo);
        SetAPSystemInfo = std::move(other.SetAPSystemInfo);
        SystemControlResponse = std::move(other.SystemControlResponse);
        other.mInterface.reset();
        return *this;
    }
    /// @brief Stop the running StartFindService
    /// @uptrace{SWS_CM_00125}
    void StopFindService(ara::com::FindServiceHandle /*handle*/)
    {
        mInterface->StopFindService();
    }
    /// @brief Return handle that is connected with service provider currently
    /// @uptrace{SWS_CM_10383}
    HandleType GetHandle() const
    {
        return mHandle;
    }
    
private:
    HandleType mHandle;
    std::unique_ptr<para::com::ProxyInterface> mInterface;
    
public:
    /// @brief - event, PeriodicSystemInfo
    events::PeriodicSystemInfo PeriodicSystemInfo;
    /// @brief - event, SystemControlRequest
    events::SystemControlRequest SystemControlRequest;
    /// @brief - method, ASMInfoRequest
    methods::ASMInfoRequest ASMInfoRequest;
    /// @brief - method, GetOneTimeSystemInfo
    methods::GetOneTimeSystemInfo GetOneTimeSystemInfo;
    /// @brief - method, SetAPSystemInfo
    methods::SetAPSystemInfo SetAPSystemInfo;
    /// @brief - method, SystemControlResponse
    methods::SystemControlResponse SystemControlResponse;
};
} /// namespace proxy
} /// namespace service
} /// namespace ipchandler
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_MAIN_IPC_ROUTINGIPC_PROXY_H