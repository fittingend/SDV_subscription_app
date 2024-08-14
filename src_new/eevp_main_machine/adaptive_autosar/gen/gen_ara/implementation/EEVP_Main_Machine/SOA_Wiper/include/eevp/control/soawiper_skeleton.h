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
/// GENERATED FILE NAME               : soawiper_skeleton.h
/// SERVICE INTERFACE NAME            : SoaWiper
/// GENERATED DATE                    : 2024-07-19 07:35:32
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SOAWIPER_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SOAWIPER_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "soawiper_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace control
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class SoaWiperSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class soaWiperDeviceNormal
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = eevp::control::SoaDeviceIsNormal;
    /// @brief Constructor
    explicit soaWiperDeviceNormal(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~soaWiperDeviceNormal() = default;
    /// @brief Delete copy constructor
    soaWiperDeviceNormal(const soaWiperDeviceNormal& other) = delete;
    /// @brief Delete copy assignment
    soaWiperDeviceNormal& operator=(const soaWiperDeviceNormal& other) = delete;
    /// @brief Move constructor
    soaWiperDeviceNormal(soaWiperDeviceNormal&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    soaWiperDeviceNormal& operator=(soaWiperDeviceNormal&& other) noexcept
    {
        mInterface = other.mInterface;
        RegisterGetHandler(std::move(other.mGetHandler));
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
    para::com::SkeletonInterface* mInterface;
    std::function<ara::core::Future<FieldType>()> mGetHandler{nullptr};
    const std::string kGetterCallSign = {"soaWiperDeviceNormalGetter"};
    const std::string kNotifierCallSign = {"soaWiperDeviceNormalNotifier"};
};
/// @uptrace{SWS_CM_00007}
class soaWiperStatus
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = eevp::control::SoaWiperStatus;
    /// @brief Constructor
    explicit soaWiperStatus(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~soaWiperStatus() = default;
    /// @brief Delete copy constructor
    soaWiperStatus(const soaWiperStatus& other) = delete;
    /// @brief Delete copy assignment
    soaWiperStatus& operator=(const soaWiperStatus& other) = delete;
    /// @brief Move constructor
    soaWiperStatus(soaWiperStatus&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    soaWiperStatus& operator=(soaWiperStatus&& other) noexcept
    {
        mInterface = other.mInterface;
        RegisterGetHandler(std::move(other.mGetHandler));
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
    para::com::SkeletonInterface* mInterface;
    std::function<ara::core::Future<FieldType>()> mGetHandler{nullptr};
    const std::string kGetterCallSign = {"soaWiperStatusGetter"};
    const std::string kNotifierCallSign = {"soaWiperStatusNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class SoaWiperSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    SoaWiperSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , soaWiperDeviceNormal(mInterface.get())
        , soaWiperStatus(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kRequestWiperOperationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleRequestWiperOperation(data);
        });
        mInterface->SetMethodCallHandler(kSetWiperAutoSpeedCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleSetWiperAutoSpeed(data);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~SoaWiperSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    SoaWiperSkeleton(const SoaWiperSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    SoaWiperSkeleton& operator=(const SoaWiperSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    SoaWiperSkeleton(SoaWiperSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , soaWiperDeviceNormal(std::move(other.soaWiperDeviceNormal))
        , soaWiperStatus(std::move(other.soaWiperStatus))
    {
        mInterface->SetMethodCallHandler(kRequestWiperOperationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleRequestWiperOperation(data);
        });
        mInterface->SetMethodCallHandler(kSetWiperAutoSpeedCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleSetWiperAutoSpeed(data);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    SoaWiperSkeleton& operator=(SoaWiperSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        soaWiperDeviceNormal = std::move(other.soaWiperDeviceNormal);
        soaWiperStatus = std::move(other.soaWiperStatus);
        mInterface->SetMethodCallHandler(kRequestWiperOperationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleRequestWiperOperation(data);
        });
        mInterface->SetMethodCallHandler(kSetWiperAutoSpeedCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandleSetWiperAutoSpeed(data);
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
    /// @brief Field, isDeviceNormal
    fields::soaWiperDeviceNormal soaWiperDeviceNormal;
    /// @brief Field, soaWiperStatus
    fields::soaWiperStatus soaWiperStatus;
    /// @brief Method, RequestWiperOperation
    /// @uptrace{SWS_CM_90434}
    virtual void RequestWiperOperation(const eevp::control::SoaWiperMode& mode) = 0;
    /// @brief Method, SetWiperAutoSpeed
    /// @uptrace{SWS_CM_90434}
    virtual void SetWiperAutoSpeed(const bool& isAutoSpeed) = 0;
    
private:
    void HandleRequestWiperOperation(const std::vector<std::uint8_t>& data)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        eevp::control::SoaWiperMode _mode_;
        deserializer.read(_mode_);
        RequestWiperOperation(_mode_);
    }
    void HandleSetWiperAutoSpeed(const std::vector<std::uint8_t>& data)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        bool _isAutoSpeed_;
        deserializer.read(_isAutoSpeed_);
        SetWiperAutoSpeed(_isAutoSpeed_);
    }
    const std::string kRequestWiperOperationCallSign{"RequestWiperOperation"};
    const std::string kSetWiperAutoSpeedCallSign{"SetWiperAutoSpeed"};
};
} /// namespace skeleton
} /// namespace control
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SOAWIPER_SKELETON_H