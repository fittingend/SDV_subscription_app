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
/// GENERATED FILE NAME               : dummytest_skeleton.h
/// SERVICE INTERFACE NAME            : DummyTest
/// GENERATED DATE                    : 2024-07-19 07:35:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "dummytest_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace test
{
namespace dummy
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class DummyTestSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
/// @uptrace{SWS_CM_00003}
class DeviceEvent
{
public:
    /// @brief Type alias for type of event data
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using SampleType = test::dummy::DeviceInfo;
    /// @brief Constructor
    explicit DeviceEvent(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~DeviceEvent() = default;
    /// @brief Delete copy constructor
    DeviceEvent(const DeviceEvent& other) = delete;
    /// @brief Delete copy assignment
    DeviceEvent& operator=(const DeviceEvent& other) = delete;
    /// @brief Move constructor
    DeviceEvent(DeviceEvent&& other) noexcept : mInterface(other.mInterface)
    {
    }
    /// @brief Move assignment
    DeviceEvent& operator=(DeviceEvent&& other) noexcept
    {
        mInterface = other.mInterface;
        return *this;
    }
    /// @brief Send event with data to subscribing service consumers
    /// @uptrace{SWS_CM_90437}
    ara::core::Result<void> Send(const SampleType& data)
    {
        para::serializer::Serializer serializer{};
        serializer.write(data);
        auto payload = serializer.ensure();
        return mInterface->SendEvent(kCallSign, payload);
    }
    /// @brief Returns unique pointer about SampleType
    /// @uptrace{SWS_CM_90438}
    ara::core::Result<ara::com::SampleAllocateePtr<SampleType>> Allocate()
    {
        return std::make_unique<SampleType>();
    }
    
private:
    para::com::SkeletonInterface* mInterface;
    const std::string kCallSign = {"DeviceEvent"};
};
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class DeviceField
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = test::dummy::DeviceInfo;
    /// @brief Constructor
    explicit DeviceField(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~DeviceField() = default;
    /// @brief Delete copy constructor
    DeviceField(const DeviceField& other) = delete;
    /// @brief Delete copy assignment
    DeviceField& operator=(const DeviceField& other) = delete;
    /// @brief Move constructor
    DeviceField(DeviceField&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
        RegisterSetHandler(std::move(other.mSetHandler));
    }
    /// @brief Move assignment
    DeviceField& operator=(DeviceField&& other) noexcept
    {
        mInterface = other.mInterface;
        RegisterGetHandler(std::move(other.mGetHandler));
        RegisterSetHandler(std::move(other.mSetHandler));
        return *this;
    }
    /// @brief Register callback for getter method
    /// @uptrace{SWS_CM_00114}
    ara::core::Result<void> RegisterGetHandler(std::function<ara::core::Future<FieldType>()> getHandler)
    {
        ara::core::Result<void> result{};
        if (getHandler != nullptr)
        {
            mGetHandler = std::move(getHandler);
            mInterface->SetMethodCallHandler(kGetterCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
                HandleGet(token);
            });
        }
        return result;
    }
    /// @brief Register callback for setter method
    /// @uptrace{SWS_CM_00116}
    ara::core::Result<void> RegisterSetHandler(std::function<ara::core::Future<FieldType>(const FieldType& value)> setHandler)
    {
        ara::core::Result<void> result;
        if (setHandler != nullptr)
        {
            mSetHandler = std::move(setHandler);
            mInterface->SetMethodCallHandler(kSetterCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
                HandleSet(data, token);
            });
        }
        return result;
    }
    /// @brief Send notification with value to subscribing service consumers
    /// @uptrace{SWS_CM_90437}
    ara::core::Result<void> Update(const FieldType& value)
    {
        para::serializer::Serializer serializer{};
        serializer.write(value);
        auto payload = serializer.ensure();
        return mInterface->SendEvent(kNotifierCallSign, payload);
    }
    
private:
    void HandleGet(const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = mGetHandler();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            FieldType value = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(value);
            retData = serializer.ensure();
            retResult = 0;
        }
        else
        {
            ara::core::ErrorDomain::IdType domainId = result.Error().Domain().Id();
            ara::core::ErrorDomain::CodeType errorCode = result.Error().Value();
            para::serializer::Serializer serializer{};
            serializer.write(0, true, 0, domainId);
            serializer.write(0, true, 0, errorCode);
            retData = serializer.ensure();
            retResult = 1;
        }
        mInterface->ReturnMethod(kGetterCallSign, retResult, retData, token);
    }
    void HandleSet(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        fields::DeviceField::FieldType _value_;
        deserializer.read(_value_);
        auto future = mSetHandler(_value_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            FieldType value = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(value);
            retData = serializer.ensure();
            retResult = 0;
        }
        else
        {
            ara::core::ErrorDomain::IdType domainId = result.Error().Domain().Id();
            ara::core::ErrorDomain::CodeType errorCode = result.Error().Value();
            para::serializer::Serializer serializer{};
            serializer.write(0, true, 0, domainId);
            serializer.write(0, true, 0, errorCode);
            retResult = 1;
        }
        mInterface->ReturnMethod(kSetterCallSign, retResult, retData, token);
    }
    para::com::SkeletonInterface* mInterface;
    std::function<ara::core::Future<FieldType>()> mGetHandler{nullptr};
    const std::string kGetterCallSign = {"DeviceFieldGetter"};
    std::function<ara::core::Future<FieldType>(const FieldType& value)> mSetHandler{nullptr};
    const std::string kSetterCallSign = {"DeviceFieldSetter"};
    const std::string kNotifierCallSign = {"DeviceFieldNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class DummyTestSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct DeviceMethodOutput
    {
        bool DeviceState;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    DummyTestSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , DeviceEvent(mInterface.get())
        , DeviceField(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kDeviceMethodCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeviceMethod(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~DummyTestSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    DummyTestSkeleton(const DummyTestSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    DummyTestSkeleton& operator=(const DummyTestSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    DummyTestSkeleton(DummyTestSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , DeviceEvent(std::move(other.DeviceEvent))
        , DeviceField(std::move(other.DeviceField))
    {
        mInterface->SetMethodCallHandler(kDeviceMethodCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeviceMethod(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    DummyTestSkeleton& operator=(DummyTestSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        DeviceEvent = std::move(other.DeviceEvent);
        DeviceField = std::move(other.DeviceField);
        mInterface->SetMethodCallHandler(kDeviceMethodCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeviceMethod(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
        return *this;
    }
    /// @brief Send "OfferService" message to Communication Management
    /// @uptrace{SWS_CM_00101}
    ara::core::Result<void> OfferService()
    {
        return mInterface->OfferService();
    }
    /// @brief Send "StopOfferService" message to Communication Management
    /// @uptrace{SWS_CM_00111}
    void StopOfferService()
    {
        mInterface->StopOfferService();
    }
    /// @brief Allows the implementation providing the service method to trigger the execution of the next service consumer method call at a specific point of time
    ///        if the processing mode is set to kPoll.
    /// @note This function requires that ara::com::MethodCallProcessingMode is configured as kPoll by constructor
    /// @uptrace{SWS_CM_00199}
    ara::core::Future<bool> ProcessNextMethodCall()
    {
        ara::core::Promise<bool> promise{};
        auto ret = mInterface->ProcessNextMethodCall();
        if (ret.HasValue())
        {
            promise.set_value(ret.Value());
        }
        else
        {
            promise.SetError(ret.Error());
        }
        return promise.get_future();
    }
    /// @brief In case the call to E2E_check indicated a failed E2E check of the request message, the server application can get notified via an E2E error handler.
    /// @uptrace{SWS_CM_10470}
    virtual void E2EErrorHandler(const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter)
    {
    }
    
private:
    std::unique_ptr<para::com::SkeletonInterface> mInterface;
    
public:
    /// @brief Event, DeviceEvent
    events::DeviceEvent DeviceEvent;
    /// @brief Field, DeviceField
    fields::DeviceField DeviceField;
    /// @brief Method, DeviceMethod
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<DeviceMethodOutput> DeviceMethod(const std::int16_t& DeviceNumber) = 0;
    
private:
    void HandleDeviceMethod(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::int16_t _DeviceNumber_;
        deserializer.read(_DeviceNumber_);
        auto future = DeviceMethod(_DeviceNumber_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            DeviceMethodOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.DeviceState);
            retData = serializer.ensure();
            retResult = 0;
        }
        else
        {
            ara::core::ErrorDomain::IdType domainId = result.Error().Domain().Id();
            ara::core::ErrorDomain::CodeType errorCode = result.Error().Value();
            para::serializer::Serializer serializer{};
            serializer.write(0, true, 0, domainId);
            serializer.write(0, true, 0, errorCode);
            retData = serializer.ensure();
            retResult = 1;
        }
        mInterface->ReturnMethod(kDeviceMethodCallSign, retResult, retData, token);
    }
    const std::string kDeviceMethodCallSign{"DeviceMethod"};
};
} /// namespace skeleton
} /// namespace dummy
} /// namespace test
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_H