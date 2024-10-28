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
/// GENERATED FILE NAME               : impl_type_vcs_vehspd.h
/// IMPLEMENTATION DATA TYPE NAME     : VCS_VehSpd
/// GENERATED DATE                    : 2024-10-24 11:01:44
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VCS_VEHSPD_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VCS_VEHSPD_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>

#include "eevp/simulation/impl_type_directionveh.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
struct VCS_VehSpd
{
    std::int32_t absoluteValue;
    std::int32_t actualValue;
    eevp::simulation::DirectionVeh direction;
    bool directionValid;
    bool valid;
    PARA_STRUCTURE(VCS_VehSpd, absoluteValue, actualValue, direction, directionValid, valid);
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VCS_VEHSPD_H