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
/// GENERATED FILE NAME               : impl_type_tms_envzonetempst.h
/// IMPLEMENTATION DATA TYPE NAME     : TMS_EnvZoneTempSt
/// GENERATED DATE                    : 2024-10-24 11:01:44
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_TMS_ENVZONETEMPST_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_TMS_ENVZONETEMPST_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/simulation/impl_type_tms_envzone.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
struct TMS_EnvZoneTempSt
{
    eevp::simulation::TMS_EnvZone ZoneId;
    std::int16_t temp;
    PARA_STRUCTURE(TMS_EnvZoneTempSt, ZoneId, temp);
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_TMS_ENVZONETEMPST_H