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
/// GENERATED FILE NAME               : snsr_facedetectmodule_skeleton.h
/// SERVICE INTERFACE NAME            : Snsr_FaceDetectModule
/// GENERATED DATE                    : 2024-11-01 14:56:47
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SNSR_FACEDETECTMODULE_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SNSR_FACEDETECTMODULE_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "snsr_facedetectmodule_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class Snsr_FaceDetectModuleSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class Snsr_FaceDetectModuleSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct getEmotionOutput
    {
        eevp::simulation::FDM_EmotionType FDM_EmotionType;
    };
    struct isRunningOutput
    {
        bool status;
    };
    struct turnOffOutput
    {
        eevp::simulation::FDM_ReturnCode FDM_ReturnCode;
    };
    struct turnOnOutput
    {
        eevp::simulation::FDM_ReturnCode FDM_ReturnCode;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    Snsr_FaceDetectModuleSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kgetEmotionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetEmotion(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOffCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOff(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOnCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOn(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~Snsr_FaceDetectModuleSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    Snsr_FaceDetectModuleSkeleton(const Snsr_FaceDetectModuleSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    Snsr_FaceDetectModuleSkeleton& operator=(const Snsr_FaceDetectModuleSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    Snsr_FaceDetectModuleSkeleton(Snsr_FaceDetectModuleSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kgetEmotionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetEmotion(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOffCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOff(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOnCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOn(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    Snsr_FaceDetectModuleSkeleton& operator=(Snsr_FaceDetectModuleSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kgetEmotionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetEmotion(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOffCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOff(data, token);
        });
        mInterface->SetMethodCallHandler(kturnOnCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleturnOn(data, token);
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
    /// @brief Method, getEmotion
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<getEmotionOutput> getEmotion() = 0;
    /// @brief Method, isRunning
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<isRunningOutput> isRunning() = 0;
    /// @brief Method, turnOff
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOffOutput> turnOff() = 0;
    /// @brief Method, turnOn
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOnOutput> turnOn() = 0;
    
private:
    void HandlegetEmotion(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = getEmotion();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            getEmotionOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.FDM_EmotionType);
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
        mInterface->ReturnMethod(kgetEmotionCallSign, retResult, retData, token);
    }
    void HandleisRunning(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = isRunning();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            isRunningOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.status);
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
        mInterface->ReturnMethod(kisRunningCallSign, retResult, retData, token);
    }
    void HandleturnOff(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = turnOff();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            turnOffOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.FDM_ReturnCode);
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
        mInterface->ReturnMethod(kturnOffCallSign, retResult, retData, token);
    }
    void HandleturnOn(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = turnOn();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            turnOnOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.FDM_ReturnCode);
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
        mInterface->ReturnMethod(kturnOnCallSign, retResult, retData, token);
    }
    const std::string kgetEmotionCallSign{"getEmotion"};
    const std::string kisRunningCallSign{"isRunning"};
    const std::string kturnOffCallSign{"turnOff"};
    const std::string kturnOnCallSign{"turnOn"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SNSR_FACEDETECTMODULE_SKELETON_H