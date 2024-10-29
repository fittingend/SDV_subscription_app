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
/// GENERATED FILE NAME               : msginfosrv_common.h
/// SERVICE INTERFACE NAME            : MsgInfoSrv
/// GENERATED DATE                    : 2024-10-29 13:55:03
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_COM_GEN_SERVICE_INTERFACE_MSGINFOSRV_COMMON_H
#define PARA_COM_GEN_SERVICE_INTERFACE_MSGINFOSRV_COMMON_H
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
#include "eevp/simulation/impl_type_ems_msginfo.h"
#include "eevp/simulation/impl_type_t_msginfo.h"
/// @uptrace{SWS_CM_01005}
namespace eevp
{
namespace simulation
{
/// @uptrace{SWS_CM_01010}, {SWS_CM_01012}
class MsgInfoSrv
{
public:
    std::uint32_t serviceContractVersionMajor = 1;
    std::uint32_t serviceContractVersionMinor = 0;
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_COM_GEN_SERVICE_INTERFACE_MSGINFOSRV_COMMON_H