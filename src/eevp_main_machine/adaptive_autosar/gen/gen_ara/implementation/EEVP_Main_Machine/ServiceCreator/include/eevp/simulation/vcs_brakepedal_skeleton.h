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
/// GENERATED FILE NAME               : vcs_brakepedal_skeleton.h
/// SERVICE INTERFACE NAME            : VCS_BrakePedal
/// GENERATED DATE                    : 2024-10-29 13:55:04
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_VCS_BRAKEPEDAL_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_VCS_BRAKEPEDAL_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "vcs_brakepedal_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class VCS_BrakePedalSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class vcs_BrakeSwtich
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = eevp::simulation::VCS_BrakePosn;
    /// @brief Constructor
    explicit vcs_BrakeSwtich(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~vcs_BrakeSwtich() = default;
    /// @brief Delete copy constructor
    vcs_BrakeSwtich(const vcs_BrakeSwtich& other) = delete;
    /// @brief Delete copy assignment
    vcs_BrakeSwtich& operator=(const vcs_BrakeSwtich& other) = delete;
    /// @brief Move constructor
    vcs_BrakeSwtich(vcs_BrakeSwtich&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    vcs_BrakeSwtich& operator=(vcs_BrakeSwtich&& other) noexcept
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
    const std::string kGetterCallSign = {"vcs_BrakeSwtichGetter"};
    const std::string kNotifierCallSign = {"vcs_BrakeSwtichNotifier"};
};
/// @uptrace{SWS_CM_00007}
class vcs_BrakePosn
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = eevp::simulation::VCS_BrakeSwitch;
    /// @brief Constructor
    explicit vcs_BrakePosn(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~vcs_BrakePosn() = default;
    /// @brief Delete copy constructor
    vcs_BrakePosn(const vcs_BrakePosn& other) = delete;
    /// @brief Delete copy assignment
    vcs_BrakePosn& operator=(const vcs_BrakePosn& other) = delete;
    /// @brief Move constructor
    vcs_BrakePosn(vcs_BrakePosn&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    vcs_BrakePosn& operator=(vcs_BrakePosn&& other) noexcept
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
    const std::string kGetterCallSign = {"vcs_BrakePosnGetter"};
    const std::string kNotifierCallSign = {"vcs_BrakePosnNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class VCS_BrakePedalSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct nofitySwitchOutput
    {
        eevp::simulation::VCS_BrakeSwitch VCS_BrakeSwitch;
    };
    struct notifyStatusOutput
    {
        eevp::simulation::VCS_BrakePosn VCS_BrakePosn;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    VCS_BrakePedalSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , vcs_BrakeSwtich(mInterface.get())
        , vcs_BrakePosn(mInterface.get())
    {
        mInterface->SetMethodCallHandler(knofitySwitchCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenofitySwitch(data, token);
        });
        mInterface->SetMethodCallHandler(knotifyStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenotifyStatus(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~VCS_BrakePedalSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    VCS_BrakePedalSkeleton(const VCS_BrakePedalSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    VCS_BrakePedalSkeleton& operator=(const VCS_BrakePedalSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    VCS_BrakePedalSkeleton(VCS_BrakePedalSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , vcs_BrakeSwtich(std::move(other.vcs_BrakeSwtich))
        , vcs_BrakePosn(std::move(other.vcs_BrakePosn))
    {
        mInterface->SetMethodCallHandler(knofitySwitchCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenofitySwitch(data, token);
        });
        mInterface->SetMethodCallHandler(knotifyStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenotifyStatus(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    VCS_BrakePedalSkeleton& operator=(VCS_BrakePedalSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        vcs_BrakeSwtich = std::move(other.vcs_BrakeSwtich);
        vcs_BrakePosn = std::move(other.vcs_BrakePosn);
        mInterface->SetMethodCallHandler(knofitySwitchCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenofitySwitch(data, token);
        });
        mInterface->SetMethodCallHandler(knotifyStatusCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandlenotifyStatus(data, token);
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
    /// @brief Field, vcs_BrakeSwtich
    fields::vcs_BrakeSwtich vcs_BrakeSwtich;
    /// @brief Field, vcs_BrakePosn
    fields::vcs_BrakePosn vcs_BrakePosn;
    /// @brief Method, nofitySwitch
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<nofitySwitchOutput> nofitySwitch() = 0;
    /// @brief Method, notifyStatus
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<notifyStatusOutput> notifyStatus() = 0;
    
private:
    void HandlenofitySwitch(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = nofitySwitch();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            nofitySwitchOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.VCS_BrakeSwitch);
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
        mInterface->ReturnMethod(knofitySwitchCallSign, retResult, retData, token);
    }
    void HandlenotifyStatus(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = notifyStatus();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            notifyStatusOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.VCS_BrakePosn);
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
        mInterface->ReturnMethod(knotifyStatusCallSign, retResult, retData, token);
    }
    const std::string knofitySwitchCallSign{"nofitySwitch"};
    const std::string knotifyStatusCallSign{"notifyStatus"};
};
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_VCS_BRAKEPEDAL_SKELETON_H