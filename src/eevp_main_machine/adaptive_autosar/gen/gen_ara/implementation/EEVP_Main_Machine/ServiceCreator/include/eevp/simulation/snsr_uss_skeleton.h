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
/// GENERATED FILE NAME               : snsr_uss_skeleton.h
/// SERVICE INTERFACE NAME            : Snsr_USS
/// GENERATED DATE                    : 2024-11-05 15:23:59
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "snsr_uss_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class Snsr_USSSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class Snsr_USSSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct ntfFltStOutput
    {
        std::uint8_t ntfFltSt;
    };
    struct ntfSonarInfoOutput
    {
        eevp::simulation::USSSonarInfo UssSonarinfo;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    Snsr_USSSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kntfFltStCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfFltSt(data, token);
        });
        mInterface->SetMethodCallHandler(kntfSonarInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfSonarInfo(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~Snsr_USSSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    Snsr_USSSkeleton(const Snsr_USSSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    Snsr_USSSkeleton& operator=(const Snsr_USSSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    Snsr_USSSkeleton(Snsr_USSSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kntfFltStCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfFltSt(data, token);
        });
        mInterface->SetMethodCallHandler(kntfSonarInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfSonarInfo(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    Snsr_USSSkeleton& operator=(Snsr_USSSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kntfFltStCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfFltSt(data, token);
        });
        mInterface->SetMethodCallHandler(kntfSonarInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlentfSonarInfo(data, token);
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
    /// @brief Method, ntfFltSt
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<ntfFltStOutput> ntfFltSt() = 0;
    /// @brief Method, ntfSonarInfo
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<ntfSonarInfoOutput> ntfSonarInfo() = 0;
    
private:
    void HandlentfFltSt(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = ntfFltSt();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            ntfFltStOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.ntfFltSt);
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
        mInterface->ReturnMethod(kntfFltStCallSign, retResult, retData, token);
    }
    void HandlentfSonarInfo(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = ntfSonarInfo();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            ntfSonarInfoOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.UssSonarinfo);
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
        mInterface->ReturnMethod(kntfSonarInfoCallSign, retResult, retData, token);
    }
    const std::string kntfFltStCallSign{"ntfFltSt"};
    const std::string kntfSonarInfoCallSign{"ntfSonarInfo"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_SKELETON_H