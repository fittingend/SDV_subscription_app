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
/// GENERATED FILE NAME               : impl_type_brakepedalrecv.h
/// IMPLEMENTATION DATA TYPE NAME     : BrakePedalRecv
/// GENERATED DATE                    : 2024-11-01 14:56:49
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_BRAKEPEDALRECV_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_BRAKEPEDALRECV_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>
#include "eevp/simulation/impl_type_vcs_brakeposn.h"
#include "eevp/simulation/impl_type_vcs_brakeswitch.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace service
{
namespace type
{
struct BrakePedalRecv
{
    eevp::simulation::VCS_BrakePosn brakePosn;
    eevp::simulation::VCS_BrakeSwitch brakeSwitch;
    PARA_STRUCTURE(BrakePedalRecv, brakePosn, brakeSwitch);
};
} /// namespace type
} /// namespace service
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_BRAKEPEDALRECV_H