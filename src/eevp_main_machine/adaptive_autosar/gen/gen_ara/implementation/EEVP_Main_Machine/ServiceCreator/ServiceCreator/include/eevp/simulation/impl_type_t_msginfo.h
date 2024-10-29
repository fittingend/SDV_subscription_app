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
/// GENERATED FILE NAME               : impl_type_t_msginfo.h
/// IMPLEMENTATION DATA TYPE NAME     : T_MSGINFO
/// GENERATED DATE                    : 2024-10-29 13:55:05
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_T_MSGINFO_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_T_MSGINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/simulation/impl_type_maxdata.h"
#include "eevp/simulation/impl_type_mindata.h"
#include "eevp/simulation/impl_type_rcdata.h"
#include "eevp/simulation/impl_type_ydata.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
struct T_MSGINFO
{
    std::uint8_t tRslt;
    std::uint8_t XaxisScale;
    std::uint8_t YaxisValidCnt;
    eevp::simulation::Ydata Ydata;
    std::uint8_t RCValidCnt;
    eevp::simulation::RCdata RCdata;
    eevp::simulation::MAXdata MAXdata;
    eevp::simulation::MINdata MINdata;
    PARA_STRUCTURE(T_MSGINFO, tRslt, XaxisScale, YaxisValidCnt, Ydata, RCValidCnt, RCdata, MAXdata, MINdata);
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_T_MSGINFO_H