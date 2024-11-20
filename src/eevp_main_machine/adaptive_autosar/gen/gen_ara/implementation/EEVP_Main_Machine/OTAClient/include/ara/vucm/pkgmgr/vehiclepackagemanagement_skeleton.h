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
/// GENERATED FILE NAME               : vehiclepackagemanagement_skeleton.h
/// SERVICE INTERFACE NAME            : VehiclePackageManagement
/// GENERATED DATE                    : 2024-11-05 15:23:51
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEPACKAGEMANAGEMENT_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEPACKAGEMANAGEMENT_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "vehiclepackagemanagement_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace ara
{
namespace vucm
{
namespace pkgmgr
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class VehiclePackageManagementSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class RequestedPackage
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::ucm::SwNameVersionType;
    /// @brief Constructor
    explicit RequestedPackage(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~RequestedPackage() = default;
    /// @brief Delete copy constructor
    RequestedPackage(const RequestedPackage& other) = delete;
    /// @brief Delete copy assignment
    RequestedPackage& operator=(const RequestedPackage& other) = delete;
    /// @brief Move constructor
    RequestedPackage(RequestedPackage&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    RequestedPackage& operator=(RequestedPackage&& other) noexcept
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
    const std::string kGetterCallSign = {"RequestedPackageGetter"};
    const std::string kNotifierCallSign = {"RequestedPackageNotifier"};
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
/// @uptrace{SWS_CM_00007}
class TransferState
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = ara::ucm::TransferStateType;
    /// @brief Constructor
    explicit TransferState(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~TransferState() = default;
    /// @brief Delete copy constructor
    TransferState(const TransferState& other) = delete;
    /// @brief Delete copy assignment
    TransferState& operator=(const TransferState& other) = delete;
    /// @brief Move constructor
    TransferState(TransferState&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    TransferState& operator=(TransferState&& other) noexcept
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
    const std::string kGetterCallSign = {"TransferStateGetter"};
    const std::string kNotifierCallSign = {"TransferStateNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class VehiclePackageManagementSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    struct AllowCampaignOutput
    {
    };
    struct CancelCampaignOutput
    {
    };
    struct DeleteTransferOutput
    {
    };
    struct GetCampaignHistoryOutput
    {
        ara::ucm::CampaignHistoryType CampaignHistory;
    };
    struct GetSwClusterInfoOutput
    {
        ara::ucm::SwClusterInfoVectorType SwInfo;
    };
    struct GetSwPackagesOutput
    {
        ara::ucm::SwPackageInfoVectorType Packages;
    };
    struct SwPackageInventoryOutput
    {
        ara::ucm::SwNameVersionVectorType RequiredSoftwarePackages;
    };
    struct TransferDataOutput
    {
    };
    struct TransferExitOutput
    {
    };
    struct TransferStartOutput
    {
        ara::ucm::TransferIdType id;
        std::uint32_t BlockSize;
    };
    struct TransferVehiclePackageOutput
    {
        ara::ucm::TransferIdType id;
        std::uint32_t BlockSize;
    };
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    VehiclePackageManagementSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , RequestedPackage(mInterface.get())
        , SafetyState(mInterface.get())
        , TransferState(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDeleteTransferCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeleteTransfer(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterInfo(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackagesCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackages(data, token);
        });
        mInterface->SetMethodCallHandler(kSwPackageInventoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSwPackageInventory(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferDataCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferData(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferExitCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferExit(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferStartCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferStart(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferVehiclePackageCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferVehiclePackage(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~VehiclePackageManagementSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    VehiclePackageManagementSkeleton(const VehiclePackageManagementSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    VehiclePackageManagementSkeleton& operator=(const VehiclePackageManagementSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    VehiclePackageManagementSkeleton(VehiclePackageManagementSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , RequestedPackage(std::move(other.RequestedPackage))
        , SafetyState(std::move(other.SafetyState))
        , TransferState(std::move(other.TransferState))
    {
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDeleteTransferCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeleteTransfer(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterInfo(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackagesCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackages(data, token);
        });
        mInterface->SetMethodCallHandler(kSwPackageInventoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSwPackageInventory(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferDataCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferData(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferExitCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferExit(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferStartCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferStart(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferVehiclePackageCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferVehiclePackage(data, token);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    VehiclePackageManagementSkeleton& operator=(VehiclePackageManagementSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        RequestedPackage = std::move(other.RequestedPackage);
        SafetyState = std::move(other.SafetyState);
        TransferState = std::move(other.TransferState);
        mInterface->SetMethodCallHandler(kAllowCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleAllowCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kCancelCampaignCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleCancelCampaign(data, token);
        });
        mInterface->SetMethodCallHandler(kDeleteTransferCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleDeleteTransfer(data, token);
        });
        mInterface->SetMethodCallHandler(kGetCampaignHistoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetCampaignHistory(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwClusterInfoCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwClusterInfo(data, token);
        });
        mInterface->SetMethodCallHandler(kGetSwPackagesCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleGetSwPackages(data, token);
        });
        mInterface->SetMethodCallHandler(kSwPackageInventoryCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleSwPackageInventory(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferDataCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferData(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferExitCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferExit(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferStartCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferStart(data, token);
        });
        mInterface->SetMethodCallHandler(kTransferVehiclePackageCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken token) {
            HandleTransferVehiclePackage(data, token);
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
    /// @brief Field, RequestedPackage
    fields::RequestedPackage RequestedPackage;
    /// @brief Field, SafetyState
    fields::SafetyState SafetyState;
    /// @brief Field, TransferState
    fields::TransferState TransferState;
    /// @brief Method, AllowCampaign
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<AllowCampaignOutput> AllowCampaign() = 0;
    /// @brief Method, CancelCampaign
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<CancelCampaignOutput> CancelCampaign(const bool& DisableCampaign) = 0;
    /// @brief Method, DeleteTransfer
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<DeleteTransferOutput> DeleteTransfer(const ara::ucm::TransferIdType& id) = 0;
    /// @brief Method, GetCampaignHistory
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetCampaignHistoryOutput> GetCampaignHistory(const std::uint64_t& timestampGE, const std::uint64_t& timestampLT) = 0;
    /// @brief Method, GetSwClusterInfo
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwClusterInfoOutput> GetSwClusterInfo() = 0;
    /// @brief Method, GetSwPackages
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<GetSwPackagesOutput> GetSwPackages() = 0;
    /// @brief Method, SwPackageInventory
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<SwPackageInventoryOutput> SwPackageInventory(const ara::ucm::SwNameVersionVectorType& AvailableSoftwarePackages) = 0;
    /// @brief Method, TransferData
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<TransferDataOutput> TransferData(const ara::ucm::TransferIdType& id, const ara::ucm::ByteVectorType& data, const std::uint64_t& blockCounter) = 0;
    /// @brief Method, TransferExit
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<TransferExitOutput> TransferExit(const ara::ucm::TransferIdType& id) = 0;
    /// @brief Method, TransferStart
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<TransferStartOutput> TransferStart(const ara::ucm::SwNameType& SoftwarePackageName, const std::uint64_t& size) = 0;
    /// @brief Method, TransferVehiclePackage
    /// @uptrace{SWS_CM_00191}
    virtual ara::core::Future<TransferVehiclePackageOutput> TransferVehiclePackage(const std::uint64_t& size) = 0;
    
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
    void HandleDeleteTransfer(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        ara::ucm::TransferIdType _id_;
        deserializer.read(_id_);
        auto future = DeleteTransfer(_id_);
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
        mInterface->ReturnMethod(kDeleteTransferCallSign, retResult, retData, token);
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
            serializer.write(output.CampaignHistory);
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
    void HandleGetSwClusterInfo(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwClusterInfo();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwClusterInfoOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.SwInfo);
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
        mInterface->ReturnMethod(kGetSwClusterInfoCallSign, retResult, retData, token);
    }
    void HandleGetSwPackages(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        auto future = GetSwPackages();
        auto result = future.GetResult();
        if (result.HasValue())
        {
            GetSwPackagesOutput output = result.Value();
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
        mInterface->ReturnMethod(kGetSwPackagesCallSign, retResult, retData, token);
    }
    void HandleSwPackageInventory(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        ara::ucm::SwNameVersionVectorType _AvailableSoftwarePackages_;
        deserializer.read(_AvailableSoftwarePackages_);
        auto future = SwPackageInventory(_AvailableSoftwarePackages_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            SwPackageInventoryOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.RequiredSoftwarePackages);
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
        mInterface->ReturnMethod(kSwPackageInventoryCallSign, retResult, retData, token);
    }
    void HandleTransferData(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        ara::ucm::TransferIdType _id_;
        ara::ucm::ByteVectorType _data_;
        std::uint64_t _blockCounter_;
        deserializer.read(_id_);
        deserializer.read(_data_);
        deserializer.read(_blockCounter_);
        auto future = TransferData(_id_, _data_, _blockCounter_);
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
        mInterface->ReturnMethod(kTransferDataCallSign, retResult, retData, token);
    }
    void HandleTransferExit(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        ara::ucm::TransferIdType _id_;
        deserializer.read(_id_);
        auto future = TransferExit(_id_);
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
        mInterface->ReturnMethod(kTransferExitCallSign, retResult, retData, token);
    }
    void HandleTransferStart(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        ara::ucm::SwNameType _SoftwarePackageName_;
        std::uint64_t _size_;
        deserializer.read(_SoftwarePackageName_);
        deserializer.read(_size_);
        auto future = TransferStart(_SoftwarePackageName_, _size_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            TransferStartOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.id);
            serializer.write(output.BlockSize);
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
        mInterface->ReturnMethod(kTransferStartCallSign, retResult, retData, token);
    }
    void HandleTransferVehiclePackage(const std::vector<std::uint8_t>& data, const para::com::MethodToken token)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        std::uint64_t _size_;
        deserializer.read(_size_);
        auto future = TransferVehiclePackage(_size_);
        auto result = future.GetResult();
        if (result.HasValue())
        {
            TransferVehiclePackageOutput output = result.Value();
            para::serializer::Serializer serializer{};
            serializer.write(output.id);
            serializer.write(output.BlockSize);
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
        mInterface->ReturnMethod(kTransferVehiclePackageCallSign, retResult, retData, token);
    }
    const std::string kAllowCampaignCallSign{"AllowCampaign"};
    const std::string kCancelCampaignCallSign{"CancelCampaign"};
    const std::string kDeleteTransferCallSign{"DeleteTransfer"};
    const std::string kGetCampaignHistoryCallSign{"GetCampaignHistory"};
    const std::string kGetSwClusterInfoCallSign{"GetSwClusterInfo"};
    const std::string kGetSwPackagesCallSign{"GetSwPackages"};
    const std::string kSwPackageInventoryCallSign{"SwPackageInventory"};
    const std::string kTransferDataCallSign{"TransferData"};
    const std::string kTransferExitCallSign{"TransferExit"};
    const std::string kTransferStartCallSign{"TransferStart"};
    const std::string kTransferVehiclePackageCallSign{"TransferVehiclePackage"};
};
} /// namespace skeleton
} /// namespace pkgmgr
} /// namespace vucm
} /// namespace ara
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_VEHICLEPACKAGEMANAGEMENT_SKELETON_H