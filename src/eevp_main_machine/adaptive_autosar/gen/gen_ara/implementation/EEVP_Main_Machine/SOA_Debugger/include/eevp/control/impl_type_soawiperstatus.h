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
/// GENERATED FILE NAME               : impl_type_soawiperstatus.h
/// IMPLEMENTATION DATA TYPE NAME     : SoaWiperStatus
/// GENERATED DATE                    : 2024-11-05 15:23:53
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAWIPERSTATUS_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAWIPERSTATUS_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>

#include "eevp/control/impl_type_soawipermode.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace control
{
struct SoaWiperStatus
{
    bool isAutoMode;
    eevp::control::SoaWiperMode mode;
    PARA_STRUCTURE(SoaWiperStatus, isAutoMode, mode);
};
} /// namespace control
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SOAWIPERSTATUS_H