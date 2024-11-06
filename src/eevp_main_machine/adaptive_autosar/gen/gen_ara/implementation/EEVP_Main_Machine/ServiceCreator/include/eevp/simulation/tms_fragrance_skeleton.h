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
/// GENERATED FILE NAME               : tms_fragrance_skeleton.h
/// SERVICE INTERFACE NAME            : TMS_Fragrance
/// GENERATED DATE                    : 2024-11-05 15:23:58
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_TMS_FRAGRANCE_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_TMS_FRAGRANCE_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "tms_fragrance_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class TMS_FragranceSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class TMS_FragranceSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct getConcentrationOutput
    {
        std::uint16_t concentration;
    };
    struct getTypeOutput
    {
        eevp::simulation::TMS_FragranceType TMS_FragranceType;
    };
    struct isRunningOutput
    {
        bool state;
    };
    struct setConcentrationOutput
    {
        eevp::simulation::TMS_ReturnCode TMS_ReturnCode;
    };
    struct setTypeOutput
    {
        eevp::simulation::TMS_ReturnCode TMS_ReturnCode;
    };
    struct turnOffOutput
    {
        eevp::simulation::TMS_ReturnCode TMS_ReturnCode;
    };
    struct turnOnOutput
    {
        eevp::simulation::TMS_ReturnCode TMS_ReturnCode;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    TMS_FragranceSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kgetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetType(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetType(data, token);
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
    virtual ~TMS_FragranceSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    TMS_FragranceSkeleton(const TMS_FragranceSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    TMS_FragranceSkeleton& operator=(const TMS_FragranceSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    TMS_FragranceSkeleton(TMS_FragranceSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kgetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetType(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetType(data, token);
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
    TMS_FragranceSkeleton& operator=(TMS_FragranceSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kgetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetType(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetConcentrationCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetConcentration(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTypeCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetType(data, token);
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
    /// @brief Method, getConcentration
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<getConcentrationOutput> getConcentration() = 0;
    /// @brief Method, getType
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<getTypeOutput> getType() = 0;
    /// @brief Method, isRunning
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<isRunningOutput> isRunning() = 0;
    /// @brief Method, setConcentration
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<setConcentrationOutput> setConcentration(const std::uint16_t& concentration) = 0;
    /// @brief Method, setType
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<setTypeOutput> setType(const eevp::simulation::TMS_FragranceType& type) = 0;
    /// @brief Method, turnOff
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOffOutput> turnOff() = 0;
    /// @brief Method, turnOn
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOnOutput> turnOn() = 0;
    
private:
    void HandlegetConcentration(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = getConcentration();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            getConcentrationOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.concentration);
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
        mInterface->ReturnMethod(kgetConcentrationCallSign, retResult, retData, token);
    }
    void HandlegetType(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = getType();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            getTypeOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.TMS_FragranceType);
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
        mInterface->ReturnMethod(kgetTypeCallSign, retResult, retData, token);
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
            serializer.write(output.state);
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
    void HandlesetConcentration(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint16_t _concentration_;
        deserializer.read(_concentration_);
        auto future = setConcentration(_concentration_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            setConcentrationOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.TMS_ReturnCode);
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
        mInterface->ReturnMethod(ksetConcentrationCallSign, retResult, retData, token);
    }
    void HandlesetType(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        eevp::simulation::TMS_FragranceType _type_;
        deserializer.read(_type_);
        auto future = setType(_type_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            setTypeOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.TMS_ReturnCode);
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
        mInterface->ReturnMethod(ksetTypeCallSign, retResult, retData, token);
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
            serializer.write(output.TMS_ReturnCode);
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
            serializer.write(output.TMS_ReturnCode);
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
    const std::string kgetConcentrationCallSign{"getConcentration"};
    const std::string kgetTypeCallSign{"getType"};
    const std::string kisRunningCallSign{"isRunning"};
    const std::string ksetConcentrationCallSign{"setConcentration"};
    const std::string ksetTypeCallSign{"setType"};
    const std::string kturnOffCallSign{"turnOff"};
    const std::string kturnOnCallSign{"turnOn"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_TMS_FRAGRANCE_SKELETON_H