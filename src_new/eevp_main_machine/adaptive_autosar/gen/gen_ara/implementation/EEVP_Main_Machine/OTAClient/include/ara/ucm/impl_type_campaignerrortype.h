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
/// GENERATED FILE NAME               : impl_type_campaignerrortype.h
/// IMPLEMENTATION DATA TYPE NAME     : CampaignErrorType
/// GENERATED DATE                    : 2024-07-19 07:35:28
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CAMPAIGNERRORTYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CAMPAIGNERRORTYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>
#include "ara/ucm/impl_type_campaignfailuretype.h"
#include "ara/ucm/impl_type_ucmsteperrortype.h"
/// @uptrace{SWS_CM_10375}
namespace ara
{
namespace ucm
{
struct CampaignErrorType
{
    ara::ucm::CampaignFailureType CampaignFailure;
    ara::ucm::UCMStepErrorType UCMStepError;
    PARA_STRUCTURE(CampaignErrorType, CampaignFailure, UCMStepError);
};
} /// namespace ucm
} /// namespace ara
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CAMPAIGNERRORTYPE_H