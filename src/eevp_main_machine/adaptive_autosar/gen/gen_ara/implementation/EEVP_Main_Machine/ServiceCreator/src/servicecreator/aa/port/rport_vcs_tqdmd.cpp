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
/// GENERATED FILE NAME               : rport_vcs_tqdmd.cpp
/// SOFTWARE COMPONENT NAME           : RPort_VCS_TqDmd
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/rport_vcs_tqdmd.h"
 
namespace servicecreator
{
namespace aa
{
namespace port
{
 
RPort_VCS_TqDmd::RPort_VCS_TqDmd()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
    , m_found{false}
{
}
 
RPort_VCS_TqDmd::~RPort_VCS_TqDmd()
{
}
 
void RPort_VCS_TqDmd::Start()
{
    m_logger.LogVerbose() << "RPort_VCS_TqDmd::Start";
    
    // regist callback
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/RPort_VCS_TqDmd"};
    auto handler = [this](ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_TqDmdProxy::HandleType> handles,
                          ara::com::FindServiceHandle findHandle) {
        this->Find(handles, findHandle);
    };
    
    // find service
    auto find = eevp::simulation::proxy::VCS_TqDmdProxy::StartFindService(handler, specifier);
    if (find.HasValue())
    {
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Start::StartFindService";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Start::StartFindService::" << find.Error().Message();
    }
    
    // run port
    m_running = true;
}
 
void RPort_VCS_TqDmd::Terminate()
{
    m_logger.LogVerbose() << "RPort_VCS_TqDmd::Terminate";
    
    // stop port
    m_running = false;
    
    // clear consumer
    if (m_interface)
    {
        // stop find service
        m_interface->StopFindService(*m_findHandle);
        m_found = false;
        
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Terminate::StopFindService";
    }
}
 
void RPort_VCS_TqDmd::Find(ara::com::ServiceHandleContainer<eevp::simulation::proxy::VCS_TqDmdProxy::HandleType> handles, ara::com::FindServiceHandle findHandle)
{
    // check finding handles
    if (handles.empty())
    {
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Find::Service Instances not found";
        return;
    }
    else
    {
        for (auto& handle : handles)
        {
            m_logger.LogVerbose() << "RPort_VCS_TqDmd::Find::Searched Instance::ServiceId =" << 
                                     handle.GetServiceHandle().serviceId << 
                                     ", InstanceId =" << 
                                     handle.GetServiceHandle().instanceId;
        }
    }
    
    // create proxy
    if (m_interface)
    {
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Find::Proxy is already running";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_VCS_TqDmd::Find::Using Instance::ServiceId =" << 
                                 handles[0].GetServiceHandle().serviceId << 
                                 ", InstanceId =" << 
                                 handles[0].GetServiceHandle().instanceId;
        m_interface = std::make_shared<eevp::simulation::proxy::VCS_TqDmdProxy>(handles[0]);
        m_findHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
        m_found = true;
    }
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF