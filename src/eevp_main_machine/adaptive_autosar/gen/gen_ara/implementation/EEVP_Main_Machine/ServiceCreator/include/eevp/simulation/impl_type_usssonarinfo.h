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
/// GENERATED FILE NAME               : impl_type_usssonarinfo.h
/// IMPLEMENTATION DATA TYPE NAME     : USSSonarInfo
/// GENERATED DATE                    : 2024-11-01 14:56:50
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_USSSONARINFO_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_USSSONARINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
struct USSSonarInfo
{
    std::uint16_t pasSonarEchoTof1;
    std::uint16_t pasSonarEchoWidth1;
    std::uint16_t pasSonarEchoPeak1;
    std::uint16_t pasSonarEchoTof2;
    std::uint16_t pasSonarEchoWidth2;
    std::uint16_t pasSonarEchoPeak2;
    std::uint8_t pasSonarEmit;
    std::uint16_t sonarRingingTimer;
    PARA_STRUCTURE(USSSonarInfo, pasSonarEchoTof1, pasSonarEchoWidth1, pasSonarEchoPeak1, pasSonarEchoTof2, pasSonarEchoWidth2, pasSonarEchoPeak2, pasSonarEmit, sonarRingingTimer);
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_USSSONARINFO_H