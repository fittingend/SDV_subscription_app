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
/// GENERATED FILE NAME               : rport_tms_ac.h
/// SOFTWARE COMPONENT NAME           : RPort_TMS_AC
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SERVICECREATOR_AA_RPORT_TMS_AC_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SERVICECREATOR_AA_RPORT_TMS_AC_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "eevp/simulation/tms_ac_proxy.h"
 
#include "ara/log/logger.h"
 
#include <mutex>
#include <thread>
 
namespace servicecreator
{
namespace aa
{
namespace port
{
 
class RPort_TMS_AC
{
public:
    /// @brief Constructor
    RPort_TMS_AC();
    
    /// @brief Destructor
    ~RPort_TMS_AC();
    
    /// @brief Start port
    void Start();
    
    /// @brief Terminate port
    void Terminate();
    
    
private:
    /// @brief Callback for find service
    void Find(ara::com::ServiceHandleContainer<eevp::simulation::proxy::TMS_ACProxy::HandleType> handles,
              ara::com::FindServiceHandle findHandle);
    
    
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
    /// @brief Flag of port status
    bool m_running;
    
    /// @brief Flag of find service status
    bool m_found;
    
    /// @brief Mutex for this port
    std::mutex m_mutex; 
    
    /// @brief AUTOSAR Port Interface
    std::shared_ptr<eevp::simulation::proxy::TMS_ACProxy> m_interface;
    
    /// @brief Find service handle
    std::shared_ptr<ara::com::FindServiceHandle> m_findHandle;
};
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SERVICECREATOR_AA_RPORT_TMS_AC_H