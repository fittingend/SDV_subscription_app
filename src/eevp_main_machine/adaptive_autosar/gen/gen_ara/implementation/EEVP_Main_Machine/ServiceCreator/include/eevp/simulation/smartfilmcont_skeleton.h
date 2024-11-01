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
/// GENERATED FILE NAME               : smartfilmcont_skeleton.h
/// SERVICE INTERFACE NAME            : SmartFilmCont
/// GENERATED DATE                    : 2024-11-01 14:56:46
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SMARTFILMCONT_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SMARTFILMCONT_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "smartfilmcont_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class SmartFilmContSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class SmartFilmContSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct SmartFilmControlOutput
    {
    };
    struct SmartFilmStatusOutput
    {
        eevp::simulation::SmartFilmStatus smartFilmStatus;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    SmartFilmContSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kSmartFilmControlCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmControl(data, token);
        });
        mInterface->SetMethodCallHandler(kSmartFilmStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmStatus(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~SmartFilmContSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    SmartFilmContSkeleton(const SmartFilmContSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    SmartFilmContSkeleton& operator=(const SmartFilmContSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    SmartFilmContSkeleton(SmartFilmContSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kSmartFilmControlCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmControl(data, token);
        });
        mInterface->SetMethodCallHandler(kSmartFilmStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmStatus(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    SmartFilmContSkeleton& operator=(SmartFilmContSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kSmartFilmControlCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmControl(data, token);
        });
        mInterface->SetMethodCallHandler(kSmartFilmStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSmartFilmStatus(data, token);
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
    /// @brief Method, SmartFilmControl
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<SmartFilmControlOutput> SmartFilmControl(const std::int32_t& WindowLocTransparence) = 0;
    /// @brief Method, SmartFilmStatus
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<SmartFilmStatusOutput> SmartFilmStatus() = 0;
    
private:
    void HandleSmartFilmControl(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::int32_t _WindowLocTransparence_;
        deserializer.read(_WindowLocTransparence_);
        auto future = SmartFilmControl(_WindowLocTransparence_);
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
        mInterface->ReturnMethod(kSmartFilmControlCallSign, retResult, retData, token);
    }
    void HandleSmartFilmStatus(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = SmartFilmStatus();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            SmartFilmStatusOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.smartFilmStatus);
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
        mInterface->ReturnMethod(kSmartFilmStatusCallSign, retResult, retData, token);
    }
    const std::string kSmartFilmControlCallSign{"SmartFilmControl"};
    const std::string kSmartFilmStatusCallSign{"SmartFilmStatus"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SMARTFILMCONT_SKELETON_H