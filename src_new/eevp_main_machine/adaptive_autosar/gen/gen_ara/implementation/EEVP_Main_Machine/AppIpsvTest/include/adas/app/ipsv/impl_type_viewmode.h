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
/// GENERATED FILE NAME               : impl_type_viewmode.h
/// IMPLEMENTATION DATA TYPE NAME     : ViewMode
/// GENERATED DATE                    : 2024-07-19 08:43:04
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VIEWMODE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VIEWMODE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
/// @uptrace{SWS_CM_10375}
namespace adas
{
namespace app
{
namespace ipsv
{
enum class ViewMode : std::uint8_t
{
    OFF = 0x00U,
    TOP_ONLY = 0x01U,
    THREE_DIM = 0x02U,
    FRONT = 0x03U,
    REAR = 0x04U,
    FRONT_SIDES = 0x05U,
    REAR_SIDES = 0x06U
};
} /// namespace ipsv
} /// namespace app
} /// namespace adas
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VIEWMODE_H