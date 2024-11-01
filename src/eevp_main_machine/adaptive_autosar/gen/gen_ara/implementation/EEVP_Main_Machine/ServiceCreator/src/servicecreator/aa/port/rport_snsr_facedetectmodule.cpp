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
/// GENERATED FILE NAME               : rport_snsr_facedetectmodule.cpp
/// SOFTWARE COMPONENT NAME           : RPort_Snsr_FaceDetectModule
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/rport_snsr_facedetectmodule.h"
 
namespace servicecreator
{
namespace aa
{
namespace port
{
 
RPort_Snsr_FaceDetectModule::RPort_Snsr_FaceDetectModule()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
    , m_found{false}
{
}
 
RPort_Snsr_FaceDetectModule::~RPort_Snsr_FaceDetectModule()
{
}
 
void RPort_Snsr_FaceDetectModule::Start()
{
    m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Start";
    
    // regist callback
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/RPort_Snsr_FaceDetectModule"};
    auto handler = [this](ara::com::ServiceHandleContainer<eevp::simulation::proxy::Snsr_FaceDetectModuleProxy::HandleType> handles,
                          ara::com::FindServiceHandle findHandle) {
        this->Find(handles, findHandle);
    };
    
    // find service
    auto find = eevp::simulation::proxy::Snsr_FaceDetectModuleProxy::StartFindService(handler, specifier);
    if (find.HasValue())
    {
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Start::StartFindService";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Start::StartFindService::" << find.Error().Message();
    }
    
    // run port
    m_running = true;
}
 
void RPort_Snsr_FaceDetectModule::Terminate()
{
    m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Terminate";
    
    // stop port
    m_running = false;
    
    // clear consumer
    if (m_interface)
    {
        // stop find service
        m_interface->StopFindService(*m_findHandle);
        m_found = false;
        
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Terminate::StopFindService";
    }
}
 
void RPort_Snsr_FaceDetectModule::Find(ara::com::ServiceHandleContainer<eevp::simulation::proxy::Snsr_FaceDetectModuleProxy::HandleType> handles, ara::com::FindServiceHandle findHandle)
{
    // check finding handles
    if (handles.empty())
    {
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Find::Service Instances not found";
        return;
    }
    else
    {
        for (auto& handle : handles)
        {
            m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Find::Searched Instance::ServiceId =" << 
                                     handle.GetServiceHandle().serviceId << 
                                     ", InstanceId =" << 
                                     handle.GetServiceHandle().instanceId;
        }
    }
    
    // create proxy
    if (m_interface)
    {
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Find::Proxy is already running";
    }
    else
    {
        m_logger.LogVerbose() << "RPort_Snsr_FaceDetectModule::Find::Using Instance::ServiceId =" << 
                                 handles[0].GetServiceHandle().serviceId << 
                                 ", InstanceId =" << 
                                 handles[0].GetServiceHandle().instanceId;
        m_interface = std::make_shared<eevp::simulation::proxy::Snsr_FaceDetectModuleProxy>(handles[0]);
        m_findHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
        m_found = true;
    }
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF