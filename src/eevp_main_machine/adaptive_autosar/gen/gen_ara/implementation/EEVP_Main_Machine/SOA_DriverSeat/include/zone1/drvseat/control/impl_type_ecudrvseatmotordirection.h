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
/// GENERATED FILE NAME               : impl_type_ecudrvseatmotordirection.h
/// IMPLEMENTATION DATA TYPE NAME     : EcuDrvSeatMotorDirection
/// GENERATED DATE                    : 2024-08-21 14:57:45
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUDRVSEATMOTORDIRECTION_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUDRVSEATMOTORDIRECTION_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace zone1
{
namespace drvseat
{
namespace control
{
struct EcuDrvSeatMotorDirection
{
    std::uint8_t slide;
    std::uint8_t recline;
    std::uint8_t height;
    std::uint8_t rlxTilt;
    std::uint8_t isNormal;
    PARA_STRUCTURE(EcuDrvSeatMotorDirection, slide, recline, height, rlxTilt, isNormal);
};
} /// namespace control
} /// namespace drvseat
} /// namespace zone1
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUDRVSEATMOTORDIRECTION_H