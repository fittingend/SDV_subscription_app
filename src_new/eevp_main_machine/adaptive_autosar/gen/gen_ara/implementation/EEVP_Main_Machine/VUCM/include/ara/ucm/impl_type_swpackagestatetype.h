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
/// GENERATED FILE NAME               : impl_type_swpackagestatetype.h
/// IMPLEMENTATION DATA TYPE NAME     : SwPackageStateType
/// GENERATED DATE                    : 2024-07-19 07:35:34
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGESTATETYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGESTATETYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
/// @uptrace{SWS_CM_10375}
namespace ara
{
namespace ucm
{
enum class SwPackageStateType : std::uint8_t
{
    kTransferring = 0x00U,
    kTransferred = 0x01U,
    kProcessing = 0x02U,
    kProcessed = 0x03U,
    kProcessingStream = 0x04U
};
} /// namespace ucm
} /// namespace ara
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGESTATETYPE_H