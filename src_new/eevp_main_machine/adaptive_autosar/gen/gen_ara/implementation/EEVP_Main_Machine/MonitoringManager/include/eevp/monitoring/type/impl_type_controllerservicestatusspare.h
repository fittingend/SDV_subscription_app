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
/// GENERATED FILE NAME               : impl_type_controllerservicestatusspare.h
/// IMPLEMENTATION DATA TYPE NAME     : ControllerServiceStatusSpare
/// GENERATED DATE                    : 2024-07-19 07:35:27
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CONTROLLERSERVICESTATUSSPARE_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CONTROLLERSERVICESTATUSSPARE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>
#include "eevp/type/impl_type_string.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace monitoring
{
namespace type
{
struct ControllerServiceStatusSpare
{
    eevp::type::String serviceName;
    eevp::type::String serviceStatus;
    eevp::type::String serviceEnable;
    eevp::type::String serviceControl;
    PARA_STRUCTURE(ControllerServiceStatusSpare, serviceName, serviceStatus, serviceEnable, serviceControl);
};
} /// namespace type
} /// namespace monitoring
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_CONTROLLERSERVICESTATUSSPARE_H