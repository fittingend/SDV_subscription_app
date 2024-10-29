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
/// GENERATED FILE NAME               : eevpcontrolsoamlm_skeleton.h
/// SERVICE INTERFACE NAME            : EevpControlSoaMlm
/// GENERATED DATE                    : 2024-10-29 13:55:04
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_EEVPCONTROLSOAMLM_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_EEVPCONTROLSOAMLM_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "eevpcontrolsoamlm_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class EevpControlSoaMlmSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class EevpControlSoaMlmSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct RequestMlmSetBrightnessOutput
    {
    };
    struct RequestMlmSetRGBColorOutput
    {
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    EevpControlSoaMlmSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kRequestMlmSetBrightnessCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetBrightness(data, token);
        });
        mInterface->SetMethodCallHandler(kRequestMlmSetRGBColorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetRGBColor(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~EevpControlSoaMlmSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    EevpControlSoaMlmSkeleton(const EevpControlSoaMlmSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    EevpControlSoaMlmSkeleton& operator=(const EevpControlSoaMlmSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    EevpControlSoaMlmSkeleton(EevpControlSoaMlmSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kRequestMlmSetBrightnessCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetBrightness(data, token);
        });
        mInterface->SetMethodCallHandler(kRequestMlmSetRGBColorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetRGBColor(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    EevpControlSoaMlmSkeleton& operator=(EevpControlSoaMlmSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kRequestMlmSetBrightnessCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetBrightness(data, token);
        });
        mInterface->SetMethodCallHandler(kRequestMlmSetRGBColorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleRequestMlmSetRGBColor(data, token);
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
    /// @brief Method, RequestMlmSetBrightness
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<RequestMlmSetBrightnessOutput> RequestMlmSetBrightness(const std::uint16_t& Brightness) = 0;
    /// @brief Method, RequestMlmSetRGBColor
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<RequestMlmSetRGBColorOutput> RequestMlmSetRGBColor(const std::uint8_t& ColorIndex) = 0;
    
private:
    void HandleRequestMlmSetBrightness(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint16_t _Brightness_;
        deserializer.read(_Brightness_);
        auto future = RequestMlmSetBrightness(_Brightness_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
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
        mInterface->ReturnMethod(kRequestMlmSetBrightnessCallSign, retResult, retData, token);
    }
    void HandleRequestMlmSetRGBColor(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint8_t _ColorIndex_;
        deserializer.read(_ColorIndex_);
        auto future = RequestMlmSetRGBColor(_ColorIndex_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
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
        mInterface->ReturnMethod(kRequestMlmSetRGBColorCallSign, retResult, retData, token);
    }
    const std::string kRequestMlmSetBrightnessCallSign{"RequestMlmSetBrightness"};
    const std::string kRequestMlmSetRGBColorCallSign{"RequestMlmSetRGBColor"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_EEVPCONTROLSOAMLM_SKELETON_H