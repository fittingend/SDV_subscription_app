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
/// GENERATED FILE NAME               : impl_type_fdm_emotiontype.h
/// IMPLEMENTATION DATA TYPE NAME     : FDM_EmotionType
/// GENERATED DATE                    : 2024-10-24 11:01:44
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_FDM_EMOTIONTYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_FDM_EMOTIONTYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
enum class FDM_EmotionType : std::uint8_t
{
    EMOTION_NORMAL = 0U,
    EMOTION_ANGRY = 1U,
    EMOTION_HAPPY = 2U,
    EMOTION_SAD = 3U,
    EMOTION_DROWSY = 4U
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_FDM_EMOTIONTYPE_H