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
/// GENERATED FILE NAME               : zone1drvseat_skeleton.h
/// SERVICE INTERFACE NAME            : Zone1DrvSeat
/// GENERATED DATE                    : 2024-08-21 14:57:44
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_ZONE1DRVSEAT_SKELETON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_ZONE1DRVSEAT_SKELETON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "zone1drvseat_common.h"
#include "para/com/skeleton/skeleton_interface.h"
/// @uptrace{SWS_CM_01005}
namespace zone1
{
namespace drvseat
{
namespace control
{
/// @uptrace{SWS_CM_01006}
namespace skeleton
{
class Zone1DrvSeatSkeleton;
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
/// @uptrace{SWS_CM_00007}
class zone1DrvSeatMotorDir
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = zone1::drvseat::control::EcuDrvSeatMotorDirection;
    /// @brief Constructor
    explicit zone1DrvSeatMotorDir(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~zone1DrvSeatMotorDir() = default;
    /// @brief Delete copy constructor
    zone1DrvSeatMotorDir(const zone1DrvSeatMotorDir& other) = delete;
    /// @brief Delete copy assignment
    zone1DrvSeatMotorDir& operator=(const zone1DrvSeatMotorDir& other) = delete;
    /// @brief Move constructor
    zone1DrvSeatMotorDir(zone1DrvSeatMotorDir&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    zone1DrvSeatMotorDir& operator=(zone1DrvSeatMotorDir&& other) noexcept
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
    const std::string kGetterCallSign = {"zone1DrvSeatMotorDirGetter"};
    const std::string kNotifierCallSign = {"zone1DrvSeatMotorDirNotifier"};
};
/// @uptrace{SWS_CM_00007}
class zone1DrvSeatMotorPos
{
public:
    /// @brief Type alias for type of field value
    /// @uptrace{SWS_CM_00162, SWS_CM_90437}
    using FieldType = zone1::drvseat::control::EcuDrvseatMotorPosition;
    /// @brief Constructor
    explicit zone1DrvSeatMotorPos(para::com::SkeletonInterface* interface) : mInterface(interface)
    {
    }
    /// @brief Destructor
    virtual ~zone1DrvSeatMotorPos() = default;
    /// @brief Delete copy constructor
    zone1DrvSeatMotorPos(const zone1DrvSeatMotorPos& other) = delete;
    /// @brief Delete copy assignment
    zone1DrvSeatMotorPos& operator=(const zone1DrvSeatMotorPos& other) = delete;
    /// @brief Move constructor
    zone1DrvSeatMotorPos(zone1DrvSeatMotorPos&& other) noexcept : mInterface(other.mInterface)
    {
        RegisterGetHandler(std::move(other.mGetHandler));
    }
    /// @brief Move assignment
    zone1DrvSeatMotorPos& operator=(zone1DrvSeatMotorPos&& other) noexcept
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
    const std::string kGetterCallSign = {"zone1DrvSeatMotorPosGetter"};
    const std::string kNotifierCallSign = {"zone1DrvSeatMotorPosNotifier"};
};
} /// namespace fields
/// @uptrace{SWS_CM_00002}
class Zone1DrvSeatSkeleton
{
public:
    /// @uptrace{SWS_CM_00191}
    /// @brief Constructor
    /// @uptrace{SWS_CM_00002, SWS_CM_00152}
    Zone1DrvSeatSkeleton(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
        : mInterface(std::make_unique<para::com::SkeletonInterface>(instanceSpec, mode))
        , zone1DrvSeatMotorDir(mInterface.get())
        , zone1DrvSeatMotorPos(mInterface.get())
    {
        mInterface->SetMethodCallHandler(kcontrolMotorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandlecontrolMotor(data);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
    }
    /// @brief Destructor
    virtual ~Zone1DrvSeatSkeleton() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00134}
    Zone1DrvSeatSkeleton(const Zone1DrvSeatSkeleton& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00134}
    Zone1DrvSeatSkeleton& operator=(const Zone1DrvSeatSkeleton& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00135}
    Zone1DrvSeatSkeleton(Zone1DrvSeatSkeleton&& other) noexcept
        : mInterface(std::move(other.mInterface))
        , zone1DrvSeatMotorDir(std::move(other.zone1DrvSeatMotorDir))
        , zone1DrvSeatMotorPos(std::move(other.zone1DrvSeatMotorPos))
    {
        mInterface->SetMethodCallHandler(kcontrolMotorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandlecontrolMotor(data);
        });
        mInterface->SetE2EErrorHandler([this](const ara::com::e2e::E2EErrorDomain& errorCode, ara::com::e2e::DataID dataID, ara::com::e2e::MessageCounter messageCounter) {
            E2EErrorHandler(errorCode, dataID, messageCounter);
        });
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00135}
    Zone1DrvSeatSkeleton& operator=(Zone1DrvSeatSkeleton&& other) noexcept
    {
        mInterface = std::move(other.mInterface);
        zone1DrvSeatMotorDir = std::move(other.zone1DrvSeatMotorDir);
        zone1DrvSeatMotorPos = std::move(other.zone1DrvSeatMotorPos);
        mInterface->SetMethodCallHandler(kcontrolMotorCallSign, [this](const std::vector<std::uint8_t>& data, const para::com::MethodToken /*token*/) {
            HandlecontrolMotor(data);
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
    /// @brief Field, zone1DrvSeatMotorDir
    fields::zone1DrvSeatMotorDir zone1DrvSeatMotorDir;
    /// @brief Field, zone1DrvSeatMotorPos
    fields::zone1DrvSeatMotorPos zone1DrvSeatMotorPos;
    /// @brief Method, controlMotor
    /// @uptrace{SWS_CM_90434}
    virtual void controlMotor(const zone1::drvseat::control::EcuDrvSeatMotorInst& inst) = 0;
    
private:
    void HandlecontrolMotor(const std::vector<std::uint8_t>& data)
    {
        std::uint8_t retResult{1};
        std::vector<std::uint8_t> retData{};
        para::serializer::Deserializer deserializer{data};
        zone1::drvseat::control::EcuDrvSeatMotorInst _inst_;
        deserializer.read(_inst_);
        controlMotor(_inst_);
    }
    const std::string kcontrolMotorCallSign{"controlMotor"};
};
} /// namespace skeleton
} /// namespace control
} /// namespace drvseat
} /// namespace zone1
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_ZONE1DRVSEAT_SKELETON_H