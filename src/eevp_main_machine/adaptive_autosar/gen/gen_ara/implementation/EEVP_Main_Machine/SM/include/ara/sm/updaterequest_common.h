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
/// GENERATED FILE NAME               : updaterequest_common.h
/// SERVICE INTERFACE NAME            : UpdateRequest
/// GENERATED DATE                    : 2024-08-14 14:33:43
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_UPDATEREQUEST_COMMON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_UPDATEREQUEST_COMMON_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "ara/core/result.h"
/// @uptrace{SWS_CM_01001}
#include "ara/com/types.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION OF CPP IMPLEMENTATION DATA TYPE HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_10372}
#include "ara/sm/impl_type_functiongrouplist.h"
/// @uptrace{SWS_CM_01005}
namespace ara
{
namespace sm
{
/// @uptrace{SWS_CM_10370}, {SWS_CM_11266}
enum class SMErrorDomainErrc : ara::core::ErrorDomain::CodeType
{
    kRejected = 5,
    kVerifyFailed = 6,
    kPrepareFailed = 7,
    kRollbackFailed = 8
};
class SMErrorDomainException : public ara::core::Exception
{
public:
    SMErrorDomainException(ara::core::ErrorCode& err) noexcept : ara::core::Exception(err)
    {
    }
};
class SMErrorDomainErrorDomain final : public ara::core::ErrorDomain
{
public:
    using Errc = SMErrorDomainErrc;
    constexpr SMErrorDomainErrorDomain() noexcept : ara::core::ErrorDomain(mDomainId)
    {
    }
    char const* Name() const noexcept override
    {
        return "SMErrorDomain";
    }
    char const* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
        	case Errc::kRejected :
        	    return "k rejected";
        	case Errc::kVerifyFailed :
        	    return "k verify failed";
        	case Errc::kPrepareFailed :
        	    return "k prepare failed";
        	case Errc::kRollbackFailed :
        	    return "k rollback failed";
            default : 
                return "unknown error";
        }
    }
    void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false) override
    {
        ara::core::ThrowOrTerminate<ara::core::Exception>(errorCode);
    }
private:
    constexpr static ara::core::ErrorDomain::IdType mDomainId = 0xC000000000000011ULL;
};
namespace internal
{
    constexpr SMErrorDomainErrorDomain mSMErrorDomainErrorDomain;
} /// namespace internal
inline constexpr ara::core::ErrorDomain const& GetSMErrorDomainErrorDomain() noexcept
{
    return internal::mSMErrorDomainErrorDomain;
}
inline constexpr ara::core::ErrorCode MakeErrorCode(SMErrorDomainErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetSMErrorDomainErrorDomain(), data);
}
/// @uptrace{SWS_CM_01010}, {SWS_CM_01012}
class UpdateRequest
{
public:
    std::uint32_t serviceContractVersionMajor = 1;
    std::uint32_t serviceContractVersionMinor = 0;
};
} /// namespace sm
} /// namespace ara
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_UPDATEREQUEST_COMMON_H