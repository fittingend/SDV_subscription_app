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
/// GENERATED FILE NAME               : rport_tms_fragrance.cpp
/// SOFTWARE COMPONENT NAME           : RPort_TMS_Fragrance
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/rport_tms_fragrance.h"
 
namespace servicecreator
{
namespace aa
{
namespace port
{
 
RPort_TMS_Fragrance::RPort_TMS_Fragrance()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
    , m_found{false}
{
}
 
RPort_TMS_Fragrance::~RPort_TMS_Fragrance()
{
}
 
void RPort_TMS_Fragrance::Start()
{
    m_logger.LogVerbose() << "RPort_TMS_Fragrance::Start";
    
    // regist callback
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/RPort_TMS_Fragrance"};
    auto handler = [this](ara::com::ServiceHandleContainer<eevp::simulation::proxy::TMS_FragranceProxy::HandleType> handles,
                          ara::com::FindServiceHandle findHandle) {
        this->Find(handles, findHandle);
    };
    
    // find service
    auto find = eevp::simulation::proxy::TMS_FragranceProxy::StartFindService(handler, specifier);
    if (find.HasValue())
    {
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Start::StartFindService";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Start::StartFindService::" << find.Error().Message();
    }
    
    // run port
    m_running = true;
}
 
void RPort_TMS_Fragrance::Terminate()
{
    m_logger.LogVerbose() << "RPort_TMS_Fragrance::Terminate";
    
    // stop port
    m_running = false;
    
    // clear consumer
    if (m_interface)
    {
        // stop find service
        m_interface->StopFindService(*m_findHandle);
        m_found = false;
        
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Terminate::StopFindService";
    }
}
 
void RPort_TMS_Fragrance::Find(ara::com::ServiceHandleContainer<eevp::simulation::proxy::TMS_FragranceProxy::HandleType> handles, ara::com::FindServiceHandle findHandle)
{
    // check finding handles
    if (handles.empty())
    {
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Find::Service Instances not found";
        return;
    }
    else
    {
        for (auto& handle : handles)
        {
            m_logger.LogVerbose() << "RPort_TMS_Fragrance::Find::Searched Instance::ServiceId =" << 
                                     handle.GetServiceHandle().serviceId << 
                                     ", InstanceId =" << 
                                     handle.GetServiceHandle().instanceId;
        }
    }
    
    // create proxy
    if (m_interface)
    {
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Find::Proxy is already running";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_TMS_Fragrance::Find::Using Instance::ServiceId =" << 
                                 handles[0].GetServiceHandle().serviceId << 
                                 ", InstanceId =" << 
                                 handles[0].GetServiceHandle().instanceId;
        m_interface = std::make_shared<eevp::simulation::proxy::TMS_FragranceProxy>(handles[0]);
        m_findHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
        m_found = true;
    }
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF