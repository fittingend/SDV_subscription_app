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
/// GENERATED FILE NAME               : pport_dms_func.h
/// SOFTWARE COMPONENT NAME           : PPort_DMS_Func
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_DMS_FUNC_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_DMS_FUNC_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "eevp/simulation/dms_func_skeleton.h"
 
#include "ara/log/logger.h"
 
#include <mutex>
#include <thread>
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
class PPort_DMS_FuncSkeletonImpl : public DMS_FuncSkeleton
{
public:
    /// @brief Constructor
    PPort_DMS_FuncSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);
    
    /// @brief Request with Response method, isDetectDrowsy
    ara::core::Future<DMS_FuncSkeleton::isDetectDrowsyOutput> isDetectDrowsy() override;
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
};
 
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp

namespace servicecreator
{
namespace aa
{
namespace port
{
 
class PPort_DMS_Func
{
public:
    /// @brief Constructor
    PPort_DMS_Func();
    
    /// @brief Destructor
    ~PPort_DMS_Func();
    
    /// @brief Start port
    void Start();
    
    /// @brief Terminate port
    void Terminate();
    
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
    /// @brief Flag of port status
    bool m_running;
    
    /// @brief Mutex for this port
    std::mutex m_mutex;
    
    /// @brief AUTOSAR Port Interface
    std::shared_ptr<eevp::simulation::skeleton::DMS_FuncSkeletonImpl> m_interface;
    
};
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_DMS_FUNC_H