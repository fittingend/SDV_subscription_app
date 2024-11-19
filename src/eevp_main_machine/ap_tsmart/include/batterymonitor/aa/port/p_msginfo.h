///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, Adaptive Application Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : p_msginfo.h
/// SOFTWARE COMPONENT NAME           : P_MsgInfo
/// GENERATED DATE                    : 2024-08-28 09:41:38
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_BATTERYMONITOR_AA_P_MSGINFO_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_BATTERYMONITOR_AA_P_MSGINFO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "batt/msginfo/msginfosrv_skeleton.h"
 
#include "ara/log/logger.h"
 
#include <mutex>
#include <thread>
#include <batterymonitor/aa/globalvariable_batterymonitor.h>
#include <chrono>
#include <iomanip>
#include <ctime>
 
namespace batt
{
namespace msginfo
{
namespace skeleton
{
 
class P_MsgInfoSkeletonImpl : public MsgInfoSrvSkeleton
{
public:
    /// @brief Constructor
    P_MsgInfoSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);
    
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
};
 
} /// namespace skeleton
} /// namespace msginfo
} /// namespace batt

namespace batterymonitor
{
namespace aa
{
namespace port
{
 
class P_MsgInfo
{
public:
    /// @brief Constructor
    P_MsgInfo();
    
    /// @brief Destructor
    ~P_MsgInfo();
    
    /// @brief Start port
    void Start();
    
    /// @brief Terminate port
    void Terminate();
    
    /// @brief Write event data to buffer, ems_MsgInfo
    void WriteDataems_MsgInfo(const batt::msginfo::skeleton::events::ems_MsgInfo::SampleType& data);
     
    /// @brief Send event cyclic from buffer data, ems_MsgInfo
    void SendEventems_MsgInfoCyclic();
     
    /// @brief Send event directly from buffer data, ems_MsgInfo
    void SendEventems_MsgInfoTriggered();
     
    /// @brief Send event directly with argument, ems_MsgInfo
    void SendEventems_MsgInfoTriggered(const batt::msginfo::skeleton::events::ems_MsgInfo::SampleType& data);
     
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
    /// @brief Flag of port status
    bool m_running;
    
    /// @brief Mutex for this port
    std::mutex m_mutex;
    
    /// @brief AUTOSAR Port Interface
    std::shared_ptr<batt::msginfo::skeleton::MsgInfoSrvSkeleton> m_interface;
    
    /// @brief Data for event, ems_MsgInfo
    batt::msginfo::skeleton::events::ems_MsgInfo::SampleType m_ems_MsgInfoData;
};
 
} /// namespace port
} /// namespace aa
} /// namespace batterymonitor
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_BATTERYMONITOR_AA_P_MSGINFO_H