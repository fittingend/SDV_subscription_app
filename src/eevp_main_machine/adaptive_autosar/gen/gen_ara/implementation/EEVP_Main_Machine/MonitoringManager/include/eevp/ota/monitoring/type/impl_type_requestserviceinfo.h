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
/// GENERATED FILE NAME               : impl_type_requestserviceinfo.h
/// IMPLEMENTATION DATA TYPE NAME     : RequestServiceInfo
/// GENERATED DATE                    : 2024-08-14 14:33:40
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFO_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/type/impl_type_string.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace ota
{
namespace monitoring
{
namespace type
{
struct RequestServiceInfo
{
    eevp::type::String serviceName;
    eevp::type::String version;
    std::uint64_t lastUpdateTime;
    eevp::type::String actionType;
    PARA_STRUCTURE(RequestServiceInfo, serviceName, version, lastUpdateTime, actionType);
};
} /// namespace type
} /// namespace monitoring
} /// namespace ota
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFO_H