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
/// GENERATED FILE NAME               : impl_type_ems_msginfo.h
/// IMPLEMENTATION DATA TYPE NAME     : ems_MsgInfo
/// GENERATED DATE                    : 2024-11-05 15:24:01
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_EMS_MSGINFO_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_EMS_MSGINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <cstdint>
#include <ara/core/structure.h>
#include "eevp/simulation/impl_type_appver.h"
#include "eevp/simulation/impl_type_completetime.h"
#include "eevp/simulation/impl_type_date.h"
#include "eevp/simulation/impl_type_elapsedtime.h"
#include "eevp/simulation/impl_type_finishedtime.h"
#include "eevp/simulation/impl_type_t_msginfo.h"
/// @uptrace{SWS_CM_10375}
namespace eevp
{
namespace simulation
{
struct ems_MsgInfo
{
    std::uint32_t InterfaceIDforDbg;
    std::uint32_t VehicleUniqueSnr;
    eevp::simulation::AppVer AppVer;
    std::uint8_t ChargeStatus;
    std::uint8_t EMS_ConnectionStatus;
    eevp::simulation::Date Date;
    std::uint16_t BattSOC;
    std::uint16_t DTE;
    std::uint16_t BatteryStatus;
    std::uint16_t SOH;
    std::uint16_t SOE;
    std::uint8_t TargetSOC;
    eevp::simulation::CompleteTime CompleteTime;
    eevp::simulation::FinishedTime FinishedTime;
    std::uint32_t GetCount;
    std::uint32_t MissedCount;
    std::uint16_t ChargeResult;
    std::uint16_t ChargedSOE;
    std::uint16_t ChargedSOC;
    eevp::simulation::T_MSGINFO Current;
    eevp::simulation::T_MSGINFO Voltage;
    eevp::simulation::T_MSGINFO SOC;
    eevp::simulation::T_MSGINFO Temp;
    eevp::simulation::ElapsedTime ElapsedTime;
    std::uint32_t ChargeStopReason;
    PARA_STRUCTURE(ems_MsgInfo, InterfaceIDforDbg, VehicleUniqueSnr, AppVer, ChargeStatus, EMS_ConnectionStatus, Date, BattSOC, DTE, BatteryStatus, SOH, SOE, TargetSOC, CompleteTime, FinishedTime, GetCount, MissedCount, ChargeResult, ChargedSOE, ChargedSOC, Current, Voltage, SOC, Temp, ElapsedTime, ChargeStopReason);
};
} /// namespace simulation
} /// namespace eevp
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_EMS_MSGINFO_H