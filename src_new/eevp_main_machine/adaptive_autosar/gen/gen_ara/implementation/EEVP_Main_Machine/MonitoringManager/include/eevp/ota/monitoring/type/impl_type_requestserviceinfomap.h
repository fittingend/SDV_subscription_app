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
/// GENERATED FILE NAME               : impl_type_requestserviceinfomap.h
/// IMPLEMENTATION DATA TYPE NAME     : RequestServiceInfoMap
/// GENERATED DATE                    : 2024-07-19 07:35:27
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFOMAP_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFOMAP_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/map.h>
#include "eevp/ota/monitoring/type/impl_type_requestserviceinfo.h"
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
using RequestServiceInfoMap = ara::core::Map<eevp::type::String, eevp::ota::monitoring::type::RequestServiceInfo>;
} /// namespace type
} /// namespace monitoring
} /// namespace ota
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_REQUESTSERVICEINFOMAP_H