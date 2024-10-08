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
/// GENERATED FILE NAME               : impl_type_soapwrzone1power.h
/// IMPLEMENTATION DATA TYPE NAME     : SoaPwrZone1Power
/// GENERATED DATE                    : 2024-07-19 07:35:31
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1POWER_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1POWER_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>
#include "eevp/control/impl_type_soapowerstate.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace control
{
struct SoaPwrZone1Power
{
    eevp::control::SoaPowerState mlmPowerState;
    eevp::control::SoaPowerState drvseatPowerState;
    eevp::control::SoaPowerState mfswPowerState;
    PARA_STRUCTURE(SoaPwrZone1Power, mlmPowerState, drvseatPowerState, mfswPowerState);
};
} /// namespace control
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1POWER_H