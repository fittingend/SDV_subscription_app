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
/// GENERATED FILE NAME               : soarcurtain_proxy.h
/// SERVICE INTERFACE NAME            : SoaRcurtain
/// GENERATED DATE                    : 2024-11-05 15:23:55
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SOARCURTAIN_PROXY_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SOARCURTAIN_PROXY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "soarcurtain_common.h"
#include "para/com/proxy/proxy_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace control
{
/// @uptrace{SWS_CM_01007}
namespace proxy
{
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00008}
class soaRctnStatus
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = eevp::control::SoaRctnStatus;
    /// @brief Constructor
    explicit soaRctnStatus(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~soaRctnStatus() = default;
    /// @brief Delete copy constructor
    soaRctnStatus(const soaRctnStatus& other) = delete;
    /// @brief Delete copy assignment
    soaRctnStatus& operator=(const soaRctnStatus& other) = delete;
    /// @brief Move constructor
    soaRctnStatus(soaRctnStatus&& other) noexcept : mInterface(other.mInterface)
    {
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    soaRctnStatus& operator=(soaRctnStatus&& other) noexcept
    {
        mInterface = other.mInterface;
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Requests getter method to Communication Management
    /// @uptrace{SWS_CM_00112}
    ara::core::Future<FieldType> Get()
    {
        std::vector<std::uint8_t> data{};
        auto* promise = new ara::core::Promise<FieldType>();
        auto future = promise->get_future();
        mInterface->CallMethod(kGetterCallSign, data, promise);
        return future;
    }
    /// @brief Requests "Subscribe" message to Communication Management
    /// @uptrace{SWS_CM_00141}
    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        if (mInterface->GetSubscriptionState(kNotifierCallSign) == ara::com::SubscriptionState::kSubscribed)
        {
            if ((maxSampleCount != 0) && (maxSampleCount != mMaxSampleCount))
            {
                return ara::core::Result<void>(ara::com::ComErrc::kMaxSampleCountNotRealizable);
            }
        }
        mMaxSampleCount = maxSampleCount;
        return mInterface->SubscribeEvent(kNotifierCallSign, mMaxSampleCount);
    }
    /// @brief Requests "StopSubscribe" message to Communication Management
    /// @uptrace{SWS_CM_00151}
    void Unsubscribe()
    {
        mInterface->UnsubscribeEvent(kNotifierCallSign);
    }
    /// @brief Return state for current subscription
    /// @uptrace{SWS_CM_00316}
    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return mInterface->GetSubscriptionState(kNotifierCallSign);
    }
    /// @brief Register callback to catch changes of subscription state
    /// @uptrace{SWS_CM_00333}
    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        mSubscriptionStateChangeHandler = std::move(handler);
        return mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Unset bound callback by SetSubscriptionStateChangeHandler
    /// @uptrace{SWS_CM_00334}
    void UnsetSubscriptionStateChangeHandler()
    {
        mSubscriptionStateChangeHandler = nullptr;
        mInterface->UnsetSubscriptionStateChangeHandler(kNotifierCallSign);
    }
    /// @brief Get received notification value from cache
    /// @uptrace{SWS_CM_00701}
    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        auto samples = mInterface->GetNewSamples(kNotifierCallSign, maxNumberOfSamples);
        for (const auto& sample : samples)
        {
            para::serializer::Deserializer deserializer{sample};
            FieldType value;
            deserializer.read(value);
            f(ara::com::make_sample_ptr<const FieldType>(value));
        }
        return samples.size();
    }
    /// @brief Register callback to catch that notification value is received
    /// @uptrace{SWS_CM_00181}
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        mEventReceiveHandler = std::move(handler);
        return mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
    }
    /// @brief Unset bound callback by SetReceiveHandler
    /// @uptrace{SWS_CM_00183}
    ara::core::Result<void> UnsetReceiveHandler()
    {
        mEventReceiveHandler = nullptr;
        return mInterface->UnsetEventReceiveHandler(kNotifierCallSign);
    }
    /// @brief Returns the count of free notification cache
    /// @uptrace{SWS_CM_00705}
    ara::core::Result<size_t> GetFreeSampleCount() const noexcept
    {
        auto ret = mInterface->GetFreeSampleCount(kNotifierCallSign);
        if (ret < 0)
        {
            return ara::core::Result<size_t>(ara::core::CoreErrc::kInvalidArgument);
        }
        return ret;
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<FieldType>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            FieldType value;
            deserializer.read(value);
            promise->set_value(value);
        }
        else
        {
            promise->SetError(ara::core::CoreErrc::kInvalidArgument);
        }
        delete promise;
    }
    size_t mMaxSampleCount{0};
    ara::com::EventReceiveHandler mEventReceiveHandler{nullptr};
    ara::com::SubscriptionStateChangeHandler mSubscriptionStateChangeHandler{nullptr};
    para::com::ProxyInterface* mInterface;
    const std::string kGetterCallSign = {"soaRctnStatusGetter"};
    const std::string kNotifierCallSign = {"soaRctnStatusNotifier"};
};
/// @uptrace{SWS_CM_00008}
class soaRctnSwVersion
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = std::uint8_t;
    /// @brief Constructor
    explicit soaRctnSwVersion(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~soaRctnSwVersion() = default;
    /// @brief Delete copy constructor
    soaRctnSwVersion(const soaRctnSwVersion& other) = delete;
    /// @brief Delete copy assignment
    soaRctnSwVersion& operator=(const soaRctnSwVersion& other) = delete;
    /// @brief Move constructor
    soaRctnSwVersion(soaRctnSwVersion&& other) noexcept : mInterface(other.mInterface)
    {
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    soaRctnSwVersion& operator=(soaRctnSwVersion&& other) noexcept
    {
        mInterface = other.mInterface;
        mMaxSampleCount = other.mMaxSampleCount;
        mEventReceiveHandler = other.mEventReceiveHandler;
        mSubscriptionStateChangeHandler = other.mSubscriptionStateChangeHandler;
        mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
        mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
        mInterface->SetMethodReturnHandler(kGetterCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Requests getter method to Communication Management
    /// @uptrace{SWS_CM_00112}
    ara::core::Future<FieldType> Get()
    {
        std::vector<std::uint8_t> data{};
        auto* promise = new ara::core::Promise<FieldType>();
        auto future = promise->get_future();
        mInterface->CallMethod(kGetterCallSign, data, promise);
        return future;
    }
    /// @brief Requests "Subscribe" message to Communication Management
    /// @uptrace{SWS_CM_00141}
    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        if (mInterface->GetSubscriptionState(kNotifierCallSign) == ara::com::SubscriptionState::kSubscribed)
        {
            if ((maxSampleCount != 0) && (maxSampleCount != mMaxSampleCount))
            {
                return ara::core::Result<void>(ara::com::ComErrc::kMaxSampleCountNotRealizable);
            }
        }
        mMaxSampleCount = maxSampleCount;
        return mInterface->SubscribeEvent(kNotifierCallSign, mMaxSampleCount);
    }
    /// @brief Requests "StopSubscribe" message to Communication Management
    /// @uptrace{SWS_CM_00151}
    void Unsubscribe()
    {
        mInterface->UnsubscribeEvent(kNotifierCallSign);
    }
    /// @brief Return state for current subscription
    /// @uptrace{SWS_CM_00316}
    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return mInterface->GetSubscriptionState(kNotifierCallSign);
    }
    /// @brief Register callback to catch changes of subscription state
    /// @uptrace{SWS_CM_00333}
    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        mSubscriptionStateChangeHandler = std::move(handler);
        return mInterface->SetSubscriptionStateChangeHandler(kNotifierCallSign, mSubscriptionStateChangeHandler);
    }
    /// @brief Unset bound callback by SetSubscriptionStateChangeHandler
    /// @uptrace{SWS_CM_00334}
    void UnsetSubscriptionStateChangeHandler()
    {
        mSubscriptionStateChangeHandler = nullptr;
        mInterface->UnsetSubscriptionStateChangeHandler(kNotifierCallSign);
    }
    /// @brief Get received notification value from cache
    /// @uptrace{SWS_CM_00701}
    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        auto samples = mInterface->GetNewSamples(kNotifierCallSign, maxNumberOfSamples);
        for (const auto& sample : samples)
        {
            para::serializer::Deserializer deserializer{sample};
            FieldType value;
            deserializer.read(value);
            f(ara::com::make_sample_ptr<const FieldType>(value));
        }
        return samples.size();
    }
    /// @brief Register callback to catch that notification value is received
    /// @uptrace{SWS_CM_00181}
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        mEventReceiveHandler = std::move(handler);
        return mInterface->SetEventReceiveHandler(kNotifierCallSign, mEventReceiveHandler);
    }
    /// @brief Unset bound callback by SetReceiveHandler
    /// @uptrace{SWS_CM_00183}
    ara::core::Result<void> UnsetReceiveHandler()
    {
        mEventReceiveHandler = nullptr;
        return mInterface->UnsetEventReceiveHandler(kNotifierCallSign);
    }
    /// @brief Returns the count of free notification cache
    /// @uptrace{SWS_CM_00705}
    ara::core::Result<size_t> GetFreeSampleCount() const noexcept
    {
        auto ret = mInterface->GetFreeSampleCount(kNotifierCallSign);
        if (ret < 0)
        {
            return ara::core::Result<size_t>(ara::core::CoreErrc::kInvalidArgument);
        }
        return ret;
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<FieldType>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            FieldType value;
            deserializer.read(value);
            promise->set_value(value);
        }
        else
        {
            promise->SetError(ara::core::CoreErrc::kInvalidArgument);
        }
        delete promise;
    }
    size_t mMaxSampleCount{0};
    ara::com::EventReceiveHandler mEventReceiveHandler{nullptr};
    ara::com::SubscriptionStateChangeHandler mSubscriptionStateChangeHandler{nullptr};
    para::com::ProxyInterface* mInterface;
    const std::string kGetterCallSign = {"soaRctnSwVersionGetter"};
    const std::string kNotifierCallSign = {"soaRctnSwVersionNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_01015}
namespace methods
{
/// @uptrace{SWS_CM_00006}
class RequestRearCurtainOperation
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
        eevp::control::SoaErrorState err;
    };
    /// @brief Constructor
    explicit RequestRearCurtainOperation(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~RequestRearCurtainOperation() = default;
    /// @brief
    RequestRearCurtainOperation(const RequestRearCurtainOperation& other) = delete;
    RequestRearCurtainOperation& operator=(const RequestRearCurtainOperation& other) = delete;
    /// @brief Move constructor
    RequestRearCurtainOperation(RequestRearCurtainOperation&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    RequestRearCurtainOperation& operator=(RequestRearCurtainOperation&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()(const eevp::control::SoaRctnMotorDir& motorDir)
    {
        para::serializer::Serializer __serializer__{};
        __serializer__.write(motorDir);
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
        auto* promise = static_cast<ara::core::Promise<RequestRearCurtainOperation::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            RequestRearCurtainOperation::Output output;
            deserializer.read(output.err);
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
        delete static_cast<ara::core::Promise<RequestRearCurtainOperation::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"RequestRearCurtainOperation"};
};
/// @uptrace{SWS_CM_00006}
class RequestRearCurtainPosition
{
public:
    /// @brief Constructor
    explicit RequestRearCurtainPosition(para::com::ProxyInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~RequestRearCurtainPosition() = default;
    /// @brief
    RequestRearCurtainPosition(const RequestRearCurtainPosition& other) = delete;
    RequestRearCurtainPosition& operator=(const RequestRearCurtainPosition& other) = delete;
    /// @brief Move constructor
    RequestRearCurtainPosition(RequestRearCurtainPosition&& other) noexcept : mInterface(other.mInterface)
    {
    }
    /// @brief Move assignment
    RequestRearCurtainPosition& operator=(RequestRearCurtainPosition&& other) noexcept
    {
        mInterface = other.mInterface;
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_90435}
    void operator()(const std::uint8_t& posPercentage)
    {
        para::serializer::Serializer __serializer__{};
        __serializer__.write(posPercentage);
        auto __data__ = __serializer__.ensure();
        mInterface->CallMethodNoReturn(kCallSign, __data__);
    }
    
private:
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"RequestRearCurtainPosition"};
};
} /// namespace methods
/// @uptrace{SWS_CM_00004}
class SoaRcurtainProxy
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
    static ara::core::Result<ara::com::FindServiceHandle> StartFindService(ara::com::FindServiceHandler<SoaRcurtainProxy::HandleType> handler, ara::core::InstanceSpecifier instanceSpec)
    {
        ara::com::FindServiceHandle findHandle = para::com::ProxyInterface::GetFindServiceHandle(instanceSpec);
        auto findCallback = [&, handler, findHandle, instanceSpec](std::vector<para::com::ServiceHandle> services) {
            ara::com::ServiceHandleContainer<SoaRcurtainProxy::HandleType> handleContainer;
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
    static ara::core::Result<ara::com::ServiceHandleContainer<SoaRcurtainProxy::HandleType>> FindService(ara::core::InstanceSpecifier instanceSpec)
    {
        auto result = para::com::ProxyInterface::FindService(instanceSpec);
        if (!result.HasValue())
        {
            return ara::core::Result<ara::com::ServiceHandleContainer<SoaRcurtainProxy::HandleType>>::FromError(result.Error());
        }
        ara::com::ServiceHandleContainer<SoaRcurtainProxy::HandleType> handleContainer;
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
    explicit SoaRcurtainProxy(HandleType& handle)
        : mHandle(handle)
        , mInterface(std::make_unique<para::com::ProxyInterface>(handle.GetInstanceSpecifier(), handle.GetServiceHandle()))
        , soaRctnStatus(mInterface.get())
        , soaRctnSwVersion(mInterface.get())
        , RequestRearCurtainOperation(mInterface.get())
        , RequestRearCurtainPosition(mInterface.get())
    {
    }
    /// @brief Destructor
    /// @uptrace{SWS_CM_10446}
    ~SoaRcurtainProxy() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00136}
    SoaRcurtainProxy(SoaRcurtainProxy& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00136}
    SoaRcurtainProxy& operator=(const SoaRcurtainProxy& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00137}
    SoaRcurtainProxy(SoaRcurtainProxy&& other) noexcept
        : mHandle(std::move(other.mHandle))
        , mInterface(std::move(other.mInterface))
        , soaRctnStatus(std::move(other.soaRctnStatus))
        , soaRctnSwVersion(std::move(other.soaRctnSwVersion))
        , RequestRearCurtainOperation(std::move(other.RequestRearCurtainOperation))
        , RequestRearCurtainPosition(std::move(other.RequestRearCurtainPosition))
    {
        mInterface->StopFindService();
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00137}
    SoaRcurtainProxy& operator=(SoaRcurtainProxy&& other) noexcept
    {
        mHandle = std::move(other.mHandle);
        mInterface = std::move(other.mInterface);
        mInterface->StopFindService();
        soaRctnStatus = std::move(other.soaRctnStatus);
        soaRctnSwVersion = std::move(other.soaRctnSwVersion);
        RequestRearCurtainOperation = std::move(other.RequestRearCurtainOperation);
        RequestRearCurtainPosition = std::move(other.RequestRearCurtainPosition);
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
    /// @brief - field, soaRctnStatus
    fields::soaRctnStatus soaRctnStatus;
    /// @brief - field, soaRctnSwVersion
    fields::soaRctnSwVersion soaRctnSwVersion;
    /// @brief - method, RequestRearCurtainOperation
    methods::RequestRearCurtainOperation RequestRearCurtainOperation;
    /// @brief - method, RequestRearCurtainPosition
    methods::RequestRearCurtainPosition RequestRearCurtainPosition;
};
} /// namespace proxy
} /// namespace control
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SOARCURTAIN_PROXY_H