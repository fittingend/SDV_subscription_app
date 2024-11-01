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
/// GENERATED FILE NAME               : pport_tms_envmonitor.cpp
/// SOFTWARE COMPONENT NAME           : PPort_TMS_EnvMonitor
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/pport_tms_envmonitor.h"
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
PPort_TMS_EnvMonitorSkeletonImpl::PPort_TMS_EnvMonitorSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : TMS_EnvMonitorSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::getHumidityOutput> PPort_TMS_EnvMonitorSkeletonImpl::getHumidity(const eevp::simulation::TMS_EnvZone& zoneId)
{
    getHumidityOutput response;
    ara::core::Promise<getHumidityOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::getLightIntensityOutput> PPort_TMS_EnvMonitorSkeletonImpl::getLightIntensity(const eevp::simulation::TMS_EnvZone& zoneId)
{
    getLightIntensityOutput response;
    ara::core::Promise<getLightIntensityOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::getTempOutput> PPort_TMS_EnvMonitorSkeletonImpl::getTemp(const eevp::simulation::TMS_EnvZone& zoneId)
{
    getTempOutput response;
    ara::core::Promise<getTempOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::notifyHumidityOutput> PPort_TMS_EnvMonitorSkeletonImpl::notifyHumidity()
{
    notifyHumidityOutput response;
    ara::core::Promise<notifyHumidityOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::notifyLightIntensityOutput> PPort_TMS_EnvMonitorSkeletonImpl::notifyLightIntensity()
{
    notifyLightIntensityOutput response;
    ara::core::Promise<notifyLightIntensityOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<TMS_EnvMonitorSkeleton::notifyTempOutput> PPort_TMS_EnvMonitorSkeletonImpl::notifyTemp()
{
    notifyTempOutput response;
    ara::core::Promise<notifyTempOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
} /// namespace skeleton
} /// namespace simulation
} /// namespace eevp

namespace servicecreator
{
namespace aa
{
namespace port
{
 
PPort_TMS_EnvMonitor::PPort_TMS_EnvMonitor()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
PPort_TMS_EnvMonitor::~PPort_TMS_EnvMonitor()
{
}
 
void PPort_TMS_EnvMonitor::Start()
{
    m_logger.LogVerbose() << "PPort_TMS_EnvMonitor::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/PPort_TMS_EnvMonitor"};
    m_interface = std::make_shared<eevp::simulation::skeleton::TMS_EnvMonitorSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "PPort_TMS_EnvMonitor::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "PPort_TMS_EnvMonitor::Start::OfferService::" << offer.Error().Message();
    }
}
 
void PPort_TMS_EnvMonitor::Terminate()
{
    m_logger.LogVerbose() << "PPort_TMS_EnvMonitor::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "PPort_TMS_EnvMonitor::Terminate::StopOfferService";
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF