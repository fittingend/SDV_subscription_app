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
/// GENERATED FILE NAME               : impl_type_vehicleinfo.h
/// IMPLEMENTATION DATA TYPE NAME     : VehicleInfo
/// GENERATED DATE                    : 2024-07-19 07:35:29
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VEHICLEINFO_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VEHICLEINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace zone
{
namespace input
{
namespace type
{
struct VehicleInfo
{
    std::uint16_t VehicleSpeed;
    std::uint8_t GearState;
    std::uint8_t ACC_In;
    std::uint8_t IGN1_In;
    std::uint8_t IGN2_In;
    PARA_STRUCTURE(VehicleInfo, VehicleSpeed, GearState, ACC_In, IGN1_In, IGN2_In);
};
} /// namespace type
} /// namespace input
} /// namespace zone
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_VEHICLEINFO_H