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
/// GENERATED FILE NAME               : main_ota_test_skeleton.h
/// SERVICE INTERFACE NAME            : Main_OTA_Test
/// GENERATED DATE                    : 2024-08-14 14:33:42
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_MAIN_OTA_TEST_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_MAIN_OTA_TEST_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "main_ota_test_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace otatest
{
namespace service
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class Main_OTA_TestSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
/// @uptrace{SWS_CM_00003}
class Event0
{
public:
    /// @brief Type alias for type of event data
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using SampleType = std::int32_t;
    /// @brief Constructor
    explicit Event0(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~Event0() = default;
    /// @brief Delete copy constructor
    Event0(const Event0& other) = delete;
    /// @brief Delete copy assignment
    Event0& operator=(const Event0& other) = delete;
    /// @brief Move constructor
    Event0(Event0&& other) noexcept : mInterface(other.mInterface)
    {
    }
    /// @brief Move assignment
    Event0& operator=(Event0&& other) noexcept
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
    const std::string kCallSign = {"Event0"};
};
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class Field0
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = std::int32_t;
    /// @brief Constructor
    explicit Field0(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~Field0() = default;
    /// @brief Delete copy constructor
    Field0(const Field0& other) = delete;
    /// @brief Delete copy assignment
    Field0& operator=(const Field0& other) = delete;
    /// @brief Move constructor
    Field0(Field0&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
        RegisterSetHandler(std::move(other.mSetHandler));
    }
    /// @brief Move assignment
    Field0& operator=(Field0&& other) noexcept
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
        fields::Field0::FieldType _value_;
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
    const std::string kGetterCallSign = {"Field0Getter"};
    std::function<ara::core::Future<FieldType>(const FieldType& value)> mSetHandler{nullptr};
    const std::string kSetterCallSign = {"Field0Setter"};
    const std::string kNotifierCallSign = {"Field0Notifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class Main_OTA_TestSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct Method0Output
    {
        eevp::type::String Arg1;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    Main_OTA_TestSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , Event0(mInterface.get())
        , Field0(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kMethod0CallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleMethod0(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~Main_OTA_TestSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    Main_OTA_TestSkeleton(const Main_OTA_TestSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    Main_OTA_TestSkeleton& operator=(const Main_OTA_TestSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    Main_OTA_TestSkeleton(Main_OTA_TestSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , Event0(std::move(other.Event0))
        , Field0(std::move(other.Field0))
    {
        mInterface->SetMethodCallHandler(kMethod0CallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleMethod0(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    Main_OTA_TestSkeleton& operator=(Main_OTA_TestSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        Event0 = std::move(other.Event0);
        Field0 = std::move(other.Field0);
        mInterface->SetMethodCallHandler(kMethod0CallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleMethod0(data, token);
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
    /// @brief Event, Event0
    events::Event0 Event0;
    /// @brief Field, Field0
    fields::Field0 Field0;
    /// @brief Method, Method0
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<Method0Output> Method0(const std::int32_t& Arg0) = 0;
    
private:
    void HandleMethod0(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::int32_t _Arg0_;
        deserializer.read(_Arg0_);
        auto future = Method0(_Arg0_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            Method0Output output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.Arg1);
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
        mInterface->ReturnMethod(kMethod0CallSign, retResult, retData, token);
    }
    const std::string kMethod0CallSign{"Method0"};
};
} /// namespace skeleton
} /// namespace service
} /// namespace otatest
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_MAIN_OTA_TEST_SKELETON_H