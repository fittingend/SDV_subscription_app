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
/// GENERATED FILE NAME               : impl_type_swpackageinfotype.h
/// IMPLEMENTATION DATA TYPE NAME     : SwPackageInfoType
/// GENERATED DATE                    : 2024-07-19 07:35:34
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGEINFOTYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGEINFOTYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "ara/ucm/impl_type_strongrevisionlabelstring.h"
#include "ara/ucm/impl_type_swnametype.h"
#include "ara/ucm/impl_type_swpackagestatetype.h"
#include "ara/ucm/impl_type_transferidtype.h"
/// @uptrace{SWS_CM_10375}
namespace ara
{
namespace ucm
{
struct SwPackageInfoType
{
    ara::ucm::SwNameType Name;
    ara::ucm::StrongRevisionLabelString Version;
    ara::ucm::TransferIdType TransferID;
    std::uint64_t ConsecutiveBytesReceived;
    std::uint64_t ConsecutiveBlocksReceived;
    ara::ucm::SwPackageStateType State;
    PARA_STRUCTURE(SwPackageInfoType, Name, Version, TransferID, ConsecutiveBytesReceived, ConsecutiveBlocksReceived, State);
};
} /// namespace ucm
} /// namespace ara
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWPACKAGEINFOTYPE_H