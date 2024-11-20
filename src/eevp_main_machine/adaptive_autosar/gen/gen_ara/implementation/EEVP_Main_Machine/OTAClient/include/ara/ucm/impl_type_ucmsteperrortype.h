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
/// GENERATED FILE NAME               : impl_type_ucmsteperrortype.h
/// IMPLEMENTATION DATA TYPE NAME     : UCMStepErrorType
/// GENERATED DATE                    : 2024-11-05 15:23:52
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_UCMSTEPERRORTYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_UCMSTEPERRORTYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "ara/ucm/impl_type_softwarepackagesteptype.h"
#include "ara/ucm/impl_type_ucmidentifiertype.h"
/// @uptrace{SWS_CM_10375}
namespace ara
{
namespace ucm
{
struct UCMStepErrorType
{
    ara::ucm::UCMIdentifierType id;
    ara::ucm::SoftwarePackageStepType SoftwarePackageStep;
    std::uint64_t ReturnedError;
    PARA_STRUCTURE(UCMStepErrorType, id, SoftwarePackageStep, ReturnedError);
};
} /// namespace ucm
} /// namespace ara
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_UCMSTEPERRORTYPE_H