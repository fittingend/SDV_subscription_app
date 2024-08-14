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
/// GENERATED FILE NAME               : impl_type_soapwrzone1curr.h
/// IMPLEMENTATION DATA TYPE NAME     : SoaPwrZone1Curr
/// GENERATED DATE                    : 2024-07-19 07:35:30
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1CURR_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1CURR_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace control
{
struct SoaPwrZone1Curr
{
    std::uint16_t mlmCurrentValue;
    std::uint16_t drvseatCurrentValue;
    std::uint16_t mfswCurrentValue;
    PARA_STRUCTURE(SoaPwrZone1Curr, mlmCurrentValue, drvseatCurrentValue, mfswCurrentValue);
};
} /// namespace control
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAPWRZONE1CURR_H