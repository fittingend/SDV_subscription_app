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
/// GENERATED FILE NAME               : tms_ac_skeleton.h
/// SERVICE INTERFACE NAME            : TMS_AC
/// GENERATED DATE                    : 2024-10-29 13:55:04
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_TMS_AC_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_TMS_AC_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "tms_ac_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class TMS_ACSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class TMS_ACSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct getAirOutletTempOutput
    {
        std::int16_t outletTemp;
    };
    struct getTargetTempOutput
    {
        std::int16_t targetTemp;
    };
    struct isRunningOutput
    {
        bool status;
    };
    struct setTargetTempOutput
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
    TMS_ACSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
    {
        mInterface->SetMethodCallHandler(kgetAirOutletTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetAirOutletTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetTargetTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetTargetTemp(data, token);
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
    virtual ~TMS_ACSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    TMS_ACSkeleton(const TMS_ACSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    TMS_ACSkeleton& operator=(const TMS_ACSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    TMS_ACSkeleton(TMS_ACSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
    {
        mInterface->SetMethodCallHandler(kgetAirOutletTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetAirOutletTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetTargetTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetTargetTemp(data, token);
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
    TMS_ACSkeleton& operator=(TMS_ACSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        mInterface->SetMethodCallHandler(kgetAirOutletTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetAirOutletTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kgetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlegetTargetTemp(data, token);
        });
        mInterface->SetMethodCallHandler(kisRunningCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleisRunning(data, token);
        });
        mInterface->SetMethodCallHandler(ksetTargetTempCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlesetTargetTemp(data, token);
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
    /// @brief Method, getAirOutletTemp
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<getAirOutletTempOutput> getAirOutletTemp(const std::uint8_t& outletId) = 0;
    /// @brief Method, getTargetTemp
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<getTargetTempOutput> getTargetTemp(const std::uint8_t& zoneId) = 0;
    /// @brief Method, isRunning
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<isRunningOutput> isRunning() = 0;
    /// @brief Method, setTargetTemp
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<setTargetTempOutput> setTargetTemp(const std::uint8_t& zoneId, const std::int16_t& targetTemp) = 0;
    /// @brief Method, turnOff
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOffOutput> turnOff() = 0;
    /// @brief Method, turnOn
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<turnOnOutput> turnOn() = 0;
    
private:
    void HandlegetAirOutletTemp(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint8_t _outletId_;
        deserializer.read(_outletId_);
        auto future = getAirOutletTemp(_outletId_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            getAirOutletTempOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.outletTemp);
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
        mInterface->ReturnMethod(kgetAirOutletTempCallSign, retResult, retData, token);
    }
    void HandlegetTargetTemp(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint8_t _zoneId_;
        deserializer.read(_zoneId_);
        auto future = getTargetTemp(_zoneId_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            getTargetTempOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.targetTemp);
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
        mInterface->ReturnMethod(kgetTargetTempCallSign, retResult, retData, token);
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
    void HandlesetTargetTemp(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint8_t _zoneId_;
        std::int16_t _targetTemp_;
        deserializer.read(_zoneId_);
        deserializer.read(_targetTemp_);
        auto future = setTargetTemp(_zoneId_, _targetTemp_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            setTargetTempOutput output = result.Value();
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
        mInterface->ReturnMethod(ksetTargetTempCallSign, retResult, retData, token);
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
    const std::string kgetAirOutletTempCallSign{"getAirOutletTemp"};
    const std::string kgetTargetTempCallSign{"getTargetTemp"};
    const std::string kisRunningCallSign{"isRunning"};
    const std::string ksetTargetTempCallSign{"setTargetTemp"};
    const std::string kturnOffCallSign{"turnOff"};
    const std::string kturnOnCallSign{"turnOn"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_TMS_AC_SKELETON_H