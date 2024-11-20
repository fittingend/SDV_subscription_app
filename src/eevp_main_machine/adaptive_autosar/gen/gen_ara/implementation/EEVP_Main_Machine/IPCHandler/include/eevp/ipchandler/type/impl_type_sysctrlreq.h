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
/// GENERATED FILE NAME               : impl_type_sysctrlreq.h
/// IMPLEMENTATION DATA TYPE NAME     : SysCtrlReq
/// GENERATED DATE                    : 2024-11-05 15:23:49
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SYSCTRLREQ_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SYSCTRLREQ_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace ipchandler
{
namespace type
{
enum class SysCtrlReq : std::uint32_t
{
    NORMAL = 0U,
    BOOTING = 1U,
    ACC_ON = 2U,
    DELAY = 3U,
    SHUTDOWN = 4U,
    RESET = 5U
};
} /// namespace type
} /// namespace ipchandler
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SYSCTRLREQ_H