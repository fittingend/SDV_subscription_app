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
/// GENERATED FILE NAME               : vehicledriverapplication_skeleton.h
/// SERVICE INTERFACE NAME            : VehicleDriverApplication
/// GENERATED DATE                    : 2024-11-05 15:23:57
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEDRIVERAPPLICATION_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEDRIVERAPPLICATION_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "vehicledriverapplication_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace ara
{
namespace vucm
{
namespace driver
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class VehicleDriverApplicationSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class ApprovalRequired
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = bool;
    /// @brief Constructor
    explicit ApprovalRequired(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~ApprovalRequired() = default;
    /// @brief Delete copy constructor
    ApprovalRequired(const ApprovalRequired& other) = delete;
    /// @brief Delete copy assignment
    ApprovalRequired& operator=(const ApprovalRequired& other) = delete;
    /// @brief Move constructor
    ApprovalRequired(ApprovalRequired&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    ApprovalRequired& operator=(ApprovalRequired&& other) noexcept
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
    const std::string kGetterCallSign = {"ApprovalRequiredGetter"};
    const std::string kNotifierCallSign = {"ApprovalRequiredNotifier"};
};
/// @uptrace{SWS_CM_00007}
class CampaignState
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::ucm::CampaignStateType;
    /// @brief Constructor
    explicit CampaignState(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~CampaignState() = default;
    /// @brief Delete copy constructor
    CampaignState(const CampaignState& other) = delete;
    /// @brief Delete copy assignment
    CampaignState& operator=(const CampaignState& other) = delete;
    /// @brief Move constructor
    CampaignState(CampaignState&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    CampaignState& operator=(CampaignState&& other) noexcept
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
    const std::string kGetterCallSign = {"CampaignStateGetter"};
    const std::string kNotifierCallSign = {"CampaignStateNotifier"};
};
/// @uptrace{SWS_CM_00007}
class SafetyPolicy
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::ucm::SafetyPolicyType;
    /// @brief Constructor
    explicit SafetyPolicy(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~SafetyPolicy() = default;
    /// @brief Delete copy constructor
    SafetyPolicy(const SafetyPolicy& other) = delete;
    /// @brief Delete copy assignment
    SafetyPolicy& operator=(const SafetyPolicy& other) = delete;
    /// @brief Move constructor
    SafetyPolicy(SafetyPolicy&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    SafetyPolicy& operator=(SafetyPolicy&& other) noexcept
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
    const std::string kGetterCallSign = {"SafetyPolicyGetter"};
    const std::string kNotifierCallSign = {"SafetyPolicyNotifier"};
};
/// @uptrace{SWS_CM_00007}
class SafetyState
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = bool;
    /// @brief Constructor
    explicit SafetyState(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~SafetyState() = default;
    /// @brief Delete copy constructor
    SafetyState(const SafetyState& other) = delete;
    /// @brief Delete copy assignment
    SafetyState& operator=(const SafetyState& other) = delete;
    /// @brief Move constructor
    SafetyState(SafetyState&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    SafetyState& operator=(SafetyState&& other) noexcept
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
    const std::string kGetterCallSign = {"SafetyStateGetter"};
    const std::string kNotifierCallSign = {"SafetyStateNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class VehicleDriverApplicationSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct AllowCampaignOutput
    {
    };
    struct CancelCampaignOutput
    {
    };
    struct DriverApprovalOutput
    {
    };
    struct GetCampaignHistoryOutput
    {
        ara::ucm::CampaignHistoryType history;
    };
    struct GetSwClusterDescriptionOutput
    {
        ara::ucm::SwDescVectorType SoftwareClusterDescriptions;
    };
    struct GetSwPackageDescriptionOutput
    {
        ara::ucm::SwDescVectorType Packages;
    };
    struct GetSwProcessProgressOutput
    {
        std::uint8_t progress;
    };
    struct GetSwTransferProgressOutput
    {
        std::uint8_t progress;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    VehicleDriverApplicationSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , ApprovalRequired(mInterface.get())
        , CampaignState(mInterface.get())
        , SafetyPolicy(mInterface.get())
        , SafetyState(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDriverApprovalCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDriverApproval(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackageDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackageDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwProcessProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwProcessProgress(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwTransferProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwTransferProgress(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~VehicleDriverApplicationSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    VehicleDriverApplicationSkeleton(const VehicleDriverApplicationSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    VehicleDriverApplicationSkeleton& operator=(const VehicleDriverApplicationSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    VehicleDriverApplicationSkeleton(VehicleDriverApplicationSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , ApprovalRequired(std::move(other.ApprovalRequired))
        , CampaignState(std::move(other.CampaignState))
        , SafetyPolicy(std::move(other.SafetyPolicy))
        , SafetyState(std::move(other.SafetyState))
    {
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDriverApprovalCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDriverApproval(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackageDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackageDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwProcessProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwProcessProgress(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwTransferProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwTransferProgress(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    VehicleDriverApplicationSkeleton& operator=(VehicleDriverApplicationSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        ApprovalRequired = std::move(other.ApprovalRequired);
        CampaignState = std::move(other.CampaignState);
        SafetyPolicy = std::move(other.SafetyPolicy);
        SafetyState = std::move(other.SafetyState);
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDriverApprovalCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDriverApproval(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackageDescriptionCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackageDescription(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwProcessProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwProcessProgress(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwTransferProgressCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwTransferProgress(data, token);
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
    /// @brief Field, ApprovalRequired
    fields::ApprovalRequired ApprovalRequired;
    /// @brief Field, CampaignState
    fields::CampaignState CampaignState;
    /// @brief Field, SafetyPolicy
    fields::SafetyPolicy SafetyPolicy;
    /// @brief Field, SafetyState
    fields::SafetyState SafetyState;
    /// @brief Method, AllowCampaign
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<AllowCampaignOutput> AllowCampaign() = 0;
    /// @brief Method, CancelCampaign
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<CancelCampaignOutput> CancelCampaign(const bool& DisableCampaign) = 0;
    /// @brief Method, DriverApproval
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<DriverApprovalOutput> DriverApproval(const bool& Approval, const ara::ucm::SafetyPolicyType& SafetyPolicy) = 0;
    /// @brief Method, GetCampaignHistory
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetCampaignHistoryOutput> GetCampaignHistory(const std::uint64_t& timestampGE, const std::uint64_t& timestampLT) = 0;
    /// @brief Method, GetSwClusterDescription
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwClusterDescriptionOutput> GetSwClusterDescription() = 0;
    /// @brief Method, GetSwPackageDescription
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwPackageDescriptionOutput> GetSwPackageDescription() = 0;
    /// @brief Method, GetSwProcessProgress
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwProcessProgressOutput> GetSwProcessProgress() = 0;
    /// @brief Method, GetSwTransferProgress
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwTransferProgressOutput> GetSwTransferProgress() = 0;
    
private:
    void HandleAllowCampaign(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = AllowCampaign();
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
        mInterface->ReturnMethod(kAllowCampaignCallSign, retResult, retData, token);
    }
    void HandleCancelCampaign(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        bool _DisableCampaign_;
        deserializer.read(_DisableCampaign_);
        auto future = CancelCampaign(_DisableCampaign_);
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
        mInterface->ReturnMethod(kCancelCampaignCallSign, retResult, retData, token);
    }
    void HandleDriverApproval(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        bool _Approval_;
        ara::ucm::SafetyPolicyType _SafetyPolicy_;
        deserializer.read(_Approval_);
        deserializer.read(_SafetyPolicy_);
        auto future = DriverApproval(_Approval_, _SafetyPolicy_);
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
        mInterface->ReturnMethod(kDriverApprovalCallSign, retResult, retData, token);
    }
    void HandleGetCampaignHistory(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint64_t _timestampGE_;
        std::uint64_t _timestampLT_;
        deserializer.read(_timestampGE_);
        deserializer.read(_timestampLT_);
        auto future = GetCampaignHistory(_timestampGE_, _timestampLT_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetCampaignHistoryOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.history);
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
        mInterface->ReturnMethod(kGetCampaignHistoryCallSign, retResult, retData, token);
    }
    void HandleGetSwClusterDescription(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwClusterDescription();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwClusterDescriptionOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.SoftwareClusterDescriptions);
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
        mInterface->ReturnMethod(kGetSwClusterDescriptionCallSign, retResult, retData, token);
    }
    void HandleGetSwPackageDescription(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwPackageDescription();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwPackageDescriptionOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.Packages);
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
        mInterface->ReturnMethod(kGetSwPackageDescriptionCallSign, retResult, retData, token);
    }
    void HandleGetSwProcessProgress(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwProcessProgress();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwProcessProgressOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.progress);
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
        mInterface->ReturnMethod(kGetSwProcessProgressCallSign, retResult, retData, token);
    }
    void HandleGetSwTransferProgress(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwTransferProgress();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwTransferProgressOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.progress);
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
        mInterface->ReturnMethod(kGetSwTransferProgressCallSign, retResult, retData, token);
    }
    const std::string kAllowCampaignCallSign{"AllowCampaign"};
    const std::string kCancelCampaignCallSign{"CancelCampaign"};
    const std::string kDriverApprovalCallSign{"DriverApproval"};
    const std::string kGetCampaignHistoryCallSign{"GetCampaignHistory"};
    const std::string kGetSwClusterDescriptionCallSign{"GetSwClusterDescription"};
    const std::string kGetSwPackageDescriptionCallSign{"GetSwPackageDescription"};
    const std::string kGetSwProcessProgressCallSign{"GetSwProcessProgress"};
    const std::string kGetSwTransferProgressCallSign{"GetSwTransferProgress"};
};
} /// namespace skeleton
} /// namespace driver
} /// namespace vucm
} /// namespace ara
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEDRIVERAPPLICATION_SKELETON_H