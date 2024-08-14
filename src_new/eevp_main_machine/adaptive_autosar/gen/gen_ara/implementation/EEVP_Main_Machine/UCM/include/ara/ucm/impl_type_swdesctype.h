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
/// GENERATED FILE NAME               : impl_type_swdesctype.h
/// IMPLEMENTATION DATA TYPE NAME     : SwDescType
/// GENERATED DATE                    : 2024-07-19 07:35:32
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWDESCTYPE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWDESCTYPE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "ara/ucm/impl_type_licensestring.h"
#include "ara/ucm/impl_type_releasenotesstring.h"
#include "ara/ucm/impl_type_strongrevisionlabelstring.h"
#include "ara/ucm/impl_type_swnametype.h"
#include "ara/ucm/impl_type_typeapprovalstring.h"
/// @uptrace{SWS_CM_10375}
namespace ara
{
namespace ucm
{
struct SwDescType
{
    ara::ucm::SwNameType Name;
    ara::ucm::StrongRevisionLabelString Version;
    ara::ucm::TypeApprovalString TypeApproval;
    ara::ucm::LicenseString License;
    ara::ucm::ReleaseNotesString ReleaseNotes;
    std::uint64_t Size;
    PARA_STRUCTURE(SwDescType, Name, Version, TypeApproval, License, ReleaseNotes, Size);
};
} /// namespace ucm
} /// namespace ara
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_SWDESCTYPE_H