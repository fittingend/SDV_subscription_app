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
/// GENERATED FILE NAME               : impl_type_ecuwiperoperationstatus.h
/// IMPLEMENTATION DATA TYPE NAME     : EcuWiperOperationStatus
/// GENERATED DATE                    : 2024-11-05 15:23:55
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUWIPEROPERATIONSTATUS_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUWIPEROPERATIONSTATUS_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace zone4
{
namespace wiper
{
namespace control
{
struct EcuWiperOperationStatus
{
    std::uint8_t curOperationMode;
    std::uint8_t isNormal;
    PARA_STRUCTURE(EcuWiperOperationStatus, curOperationMode, isNormal);
};
} /// namespace control
} /// namespace wiper
} /// namespace zone4
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_ECUWIPEROPERATIONSTATUS_H