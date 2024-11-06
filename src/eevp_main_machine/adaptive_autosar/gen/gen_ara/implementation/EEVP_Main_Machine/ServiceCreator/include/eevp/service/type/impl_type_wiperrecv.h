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
/// GENERATED FILE NAME               : impl_type_wiperrecv.h
/// IMPLEMENTATION DATA TYPE NAME     : wiperRecv
/// GENERATED DATE                    : 2024-11-05 15:24:01
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_WIPERRECV_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_WIPERRECV_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/simulation/impl_type_bcm_wipinglevel.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace service
{
namespace type
{
struct wiperRecv
{
    eevp::simulation::BCM_WipingLevel wipingLevel;
    std::uint16_t wipingInterval;
    PARA_STRUCTURE(wiperRecv, wipingLevel, wipingInterval);
};
} /// namespace type
} /// namespace service
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_WIPERRECV_H