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
/// GENERATED FILE NAME               : impl_type_distancelevel.h
/// IMPLEMENTATION DATA TYPE NAME     : DistanceLevel
/// GENERATED DATE                    : 2024-07-19 07:35:29
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_DISTANCELEVEL_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_DISTANCELEVEL_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/pdw/type/impl_type_direction.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace pdw
{
namespace type
{
struct DistanceLevel
{
    std::uint8_t Left;
    std::uint8_t Right;
    std::uint8_t Center;
    eevp::pdw::type::Direction SensorDirection;
    PARA_STRUCTURE(DistanceLevel, Left, Right, Center, SensorDirection);
};
} /// namespace type
} /// namespace pdw
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_DISTANCELEVEL_H