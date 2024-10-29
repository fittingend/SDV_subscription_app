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
/// GENERATED FILE NAME               : snsr_uss_proxy.h
/// SERVICE INTERFACE NAME            : Snsr_USS
/// GENERATED DATE                    : 2024-10-29 13:55:02
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_PROXY_H
#define PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_PROXY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_01004}
#include "snsr_uss_common.h"
#include "para/com/proxy/proxy_interface.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01007}
namespace proxy
{
/// @uptrace{SWS_CM_01009}
namespace events
{
} /// namespace events
/// @uptrace{SWS_CM_01031}
namespace fields
{
} /// namespace fields
/// @uptrace{SWS_CM_01015}
namespace methods
{
/// @uptrace{SWS_CM_00006}
class ntfFltSt
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
        std::uint8_t ntfFltSt;
    };
    /// @brief Constructor
    explicit ntfFltSt(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~ntfFltSt() = default;
    /// @brief
    ntfFltSt(const ntfFltSt& other) = delete;
    ntfFltSt& operator=(const ntfFltSt& other) = delete;
    /// @brief Move constructor
    ntfFltSt(ntfFltSt&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    ntfFltSt& operator=(ntfFltSt&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()()
    {
        para::serializer::Serializer __serializer__{};
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<ntfFltSt::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            ntfFltSt::Output output;
            deserializer.read(output.ntfFltSt);
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<ntfFltSt::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"ntfFltSt"};
};
/// @uptrace{SWS_CM_00006}
class ntfSonarInfo
{
public:
    /// @brief Container for OUT arguments
    /// @uptrace{SWS_CM_00196}
    struct Output
    {
        eevp::simulation::USSSonarInfo UssSonarinfo;
    };
    /// @brief Constructor
    explicit ntfSonarInfo(para::com::ProxyInterface* interface) : mInterface(interface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Destructor
    virtual ~ntfSonarInfo() = default;
    /// @brief
    ntfSonarInfo(const ntfSonarInfo& other) = delete;
    ntfSonarInfo& operator=(const ntfSonarInfo& other) = delete;
    /// @brief Move constructor
    ntfSonarInfo(ntfSonarInfo&& other) noexcept : mInterface(other.mInterface)
    {
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
    }
    /// @brief Move assignment
    ntfSonarInfo& operator=(ntfSonarInfo&& other) noexcept
    {
        mInterface = other.mInterface;
        mInterface->SetMethodReturnHandler(kCallSign, [](std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData) {
            HandleMethodReturn(result, data, userData);
        });
        return *this;
    }
    /// @brief Function call operator
    /// @uptrace{SWS_CM_00196}
    ara::core::Future<Output> operator()()
    {
        para::serializer::Serializer __serializer__{};
        auto __data__ = __serializer__.ensure();
        auto* __promise__ = new ara::core::Promise<Output>();
        auto __future__ = __promise__->get_future();
        mInterface->CallMethod(kCallSign, __data__, __promise__);
        return __future__;
    }
    /// @brief This method provides access to the global SMState of the this Method class,
    ///        which was determined by the last run of E2E_check function invoked during the last reception of the method response.
    /// @uptrace{SWS_CM_90483}
    /// @uptrace{SWS_CM_90484}
    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return mInterface->GetE2EStateMachineState(kCallSign);
    }
    
private:
    static void HandleMethodReturn(std::uint8_t result, const std::vector<std::uint8_t>& data, void* userData)
    {
        auto* promise = static_cast<ara::core::Promise<ntfSonarInfo::Output>*>(userData);
        if (result == 0)
        {
            para::serializer::Deserializer deserializer{data};
            ntfSonarInfo::Output output;
            deserializer.read(output.UssSonarinfo);
            promise->set_value(output);
        }
        else
        {
            para::serializer::Deserializer deserializer{data};
            ara::core::ErrorDomain::IdType domainId{};
            ara::core::ErrorDomain::CodeType errorCode{};
            deserializer.read(0, true, 0, domainId);
            deserializer.read(0, true, 0, errorCode);
            switch (domainId)
            {
                default:
                {
                    promise->SetError(ara::com::ComErrc::kUnsetFailure);
                    break;
                }
            }
        }
        delete static_cast<ara::core::Promise<ntfSonarInfo::Output>*>(userData);
    }
    para::com::ProxyInterface* mInterface;
    const std::string kCallSign{"ntfSonarInfo"};
};
} /// namespace methods
/// @uptrace{SWS_CM_00004}
class Snsr_USSProxy
{
public: 
    /// @uptrace{SWS_CM_00312}
    class HandleType
    {
    public:
        HandleType() = default;
        HandleType(ara::core::InstanceSpecifier instanceSpecifier, para::com::ServiceHandle service)
            : mInstanceSpecifier(std::move(instanceSpecifier)), mServiceHandle(service)
        {
        }
        ~HandleType() = default;
        /// @uptrace{SWS_CM_00317}
        HandleType(const HandleType& other) = default;
        HandleType& operator=(const HandleType& other) = default;
        /// @uptrace{SWS_CM_00318}
        HandleType(HandleType&& other) = default;
        HandleType& operator=(HandleType&& other) = default;
        /// @brief Return instance specifier
        ara::core::InstanceSpecifier GetInstanceSpecifier()
        {
            return mInstanceSpecifier;
        }
        /// @brief Return handle for bound service
        para::com::ServiceHandle GetServiceHandle()
        {
            return mServiceHandle;
        }
        /// @brief Is equal to operator
        inline bool operator==(const HandleType& other) const
        {
            return mInstanceSpecifier == other.mInstanceSpecifier && mServiceHandle == other.mServiceHandle;
        }
        /// @brief Less than operator
        inline bool operator<(const HandleType& other) const
        {
            return mServiceHandle.version < other.mServiceHandle.version;
        }
        
    private:
        ara::core::InstanceSpecifier mInstanceSpecifier{"undefined"};
        para::com::ServiceHandle mServiceHandle;
    };
    /// @brief Requests "FindService" message to Communication Management with callback
    /// @uptrace{SWS_CM_00623}
    static ara::core::Result<ara::com::FindServiceHandle> StartFindService(ara::com::FindServiceHandler<Snsr_USSProxy::HandleType> handler, ara::core::InstanceSpecifier instanceSpec)
    {
        ara::com::FindServiceHandle findHandle = para::com::ProxyInterface::GetFindServiceHandle(instanceSpec);
        auto findCallback = [&, handler, findHandle, instanceSpec](std::vector<para::com::ServiceHandle> services) {
            ara::com::ServiceHandleContainer<Snsr_USSProxy::HandleType> handleContainer;
            for (auto& service : services)
            {
                handleContainer.emplace_back(instanceSpec, service);
            }
            handler(handleContainer, findHandle);
        };
        return para::com::ProxyInterface::StartFindService(instanceSpec, findCallback);
    }
    /// @brief Send "FindService" message to Communication Management at once
    /// @uptrace{SWS_CM_00622}
    static ara::core::Result<ara::com::ServiceHandleContainer<Snsr_USSProxy::HandleType>> FindService(ara::core::InstanceSpecifier instanceSpec)
    {
        auto result = para::com::ProxyInterface::FindService(instanceSpec);
        if (!result.HasValue())
        {
            return ara::core::Result<ara::com::ServiceHandleContainer<Snsr_USSProxy::HandleType>>::FromError(result.Error());
        }
        ara::com::ServiceHandleContainer<Snsr_USSProxy::HandleType> handleContainer;
        const auto& services = result.Value();
        for (auto& service : services)
        {
            handleContainer.emplace_back(instanceSpec, service);
        }
        return handleContainer;
    }
    /// @brief Constructor
    /// @note This function shall be called after processing of FindService/StartFindService was completed
    /// @uptrace{SWS_CM_00004, SWS_CM_00131}
    explicit Snsr_USSProxy(HandleType& handle)
        : mHandle(handle)
        , mInterface(std::make_unique<para::com::ProxyInterface>(handle.GetInstanceSpecifier(), handle.GetServiceHandle()))
        , ntfFltSt(mInterface.get())
        , ntfSonarInfo(mInterface.get())
    {
    }
    /// @brief Destructor
    /// @uptrace{SWS_CM_10446}
    ~Snsr_USSProxy() = default;
    /// @brief Delete copy constructor
    /// @uptrace{SWS_CM_00136}
    Snsr_USSProxy(Snsr_USSProxy& other) = delete;
    /// @brief Delete copy assignment
    /// @uptrace{SWS_CM_00136}
    Snsr_USSProxy& operator=(const Snsr_USSProxy& other) = delete;
    /// @brief Move constructor
    /// @uptrace{SWS_CM_00137}
    Snsr_USSProxy(Snsr_USSProxy&& other) noexcept
        : mHandle(std::move(other.mHandle))
        , mInterface(std::move(other.mInterface))
        , ntfFltSt(std::move(other.ntfFltSt))
        , ntfSonarInfo(std::move(other.ntfSonarInfo))
    {
        mInterface->StopFindService();
        other.mInterface.reset();
    }
    /// @brief Move assignment
    /// @uptrace{SWS_CM_00137}
    Snsr_USSProxy& operator=(Snsr_USSProxy&& other) noexcept
    {
        mHandle = std::move(other.mHandle);
        mInterface = std::move(other.mInterface);
        mInterface->StopFindService();
        ntfFltSt = std::move(other.ntfFltSt);
        ntfSonarInfo = std::move(other.ntfSonarInfo);
        other.mInterface.reset();
        return *this;
    }
    /// @brief Stop the running StartFindService
    /// @uptrace{SWS_CM_00125}
    void StopFindService(ara::com::FindServiceHandle /*handle*/)
    {
        mInterface->StopFindService();
    }
    /// @brief Return handle that is connected with service provider currently
    /// @uptrace{SWS_CM_10383}
    HandleType GetHandle() const
    {
        return mHandle;
    }
    
private:
    HandleType mHandle;
    std::unique_ptr<para::com::ProxyInterface> mInterface;
    
public:
    /// @brief - method, ntfFltSt
    methods::ntfFltSt ntfFltSt;
    /// @brief - method, ntfSonarInfo
    methods::ntfSonarInfo ntfSonarInfo;
};
} /// namespace proxy
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_SNSR_USS_PROXY_H