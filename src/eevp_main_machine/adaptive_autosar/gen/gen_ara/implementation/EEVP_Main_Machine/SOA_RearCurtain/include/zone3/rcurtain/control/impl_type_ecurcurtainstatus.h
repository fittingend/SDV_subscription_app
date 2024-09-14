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
/// GENERATED FILE NAME               : impl_type_ecurcurtainstatus.h
/// IMPLEMENTATION DATA TYPE NAME     : EcuRcurtainStatus
/// GENERATED DATE                    : 2024-08-21 14:57:52
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECURCURTAINSTATUS_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECURCURTAINSTATUS_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace zone3
{
namespace rcurtain
{
namespace control
{
struct EcuRcurtainStatus
{
    std::uint8_t curMotorDir;
    std::uint8_t curMotorLimit;
    std::uint16_t motorCurrent;
    std::uint8_t isNormal;
    PARA_STRUCTURE(EcuRcurtainStatus, curMotorDir, curMotorLimit, motorCurrent, isNormal);
};
} /// namespace control
} /// namespace rcurtain
} /// namespace zone3
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECURCURTAINSTATUS_H