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
/// GENERATED FILE NAME               : pport_ctrl_moodlamp.cpp
/// SOFTWARE COMPONENT NAME           : PPort_Ctrl_MoodLamp
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/pport_ctrl_moodlamp.h"
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
PPort_Ctrl_MoodLampSkeletonImpl::PPort_Ctrl_MoodLampSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : Ctrl_MoodLampSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::getBrightnessOutput> PPort_Ctrl_MoodLampSkeletonImpl::getBrightness()
{
    getBrightnessOutput response;
    ara::core::Promise<getBrightnessOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::getColorOutput> PPort_Ctrl_MoodLampSkeletonImpl::getColor()
{
    getColorOutput response;
    ara::core::Promise<getColorOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::getPowerStatusOutput> PPort_Ctrl_MoodLampSkeletonImpl::getPowerStatus()
{
    getPowerStatusOutput response;
    ara::core::Promise<getPowerStatusOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::setBrightnessOutput> PPort_Ctrl_MoodLampSkeletonImpl::setBrightness(const eevp::simulation::brightness& brightness)
{
    setBrightnessOutput response;
    ara::core::Promise<setBrightnessOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::setColorOutput> PPort_Ctrl_MoodLampSkeletonImpl::setColor(const eevp::simulation::color& color)
{
    setColorOutput response;
    ara::core::Promise<setColorOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::setPowerStatusOutput> PPort_Ctrl_MoodLampSkeletonImpl::setPowerStatus(const eevp::simulation::lampStatus& lampStatus)
{
    setPowerStatusOutput response;
    ara::core::Promise<setPowerStatusOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::turnOffOutput> PPort_Ctrl_MoodLampSkeletonImpl::turnOff()
{
    turnOffOutput response;
    ara::core::Promise<turnOffOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Ctrl_MoodLampSkeleton::turnOnOutput> PPort_Ctrl_MoodLampSkeletonImpl::turnOn()
{
    turnOnOutput response;
    ara::core::Promise<turnOnOutput> promise;
    
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
 
PPort_Ctrl_MoodLamp::PPort_Ctrl_MoodLamp()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
PPort_Ctrl_MoodLamp::~PPort_Ctrl_MoodLamp()
{
}
 
void PPort_Ctrl_MoodLamp::Start()
{
    m_logger.LogVerbose() << "PPort_Ctrl_MoodLamp::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/PPort_Ctrl_MoodLamp"};
    m_interface = std::make_shared<eevp::simulation::skeleton::Ctrl_MoodLampSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "PPort_Ctrl_MoodLamp::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "PPort_Ctrl_MoodLamp::Start::OfferService::" << offer.Error().Message();
    }
}
 
void PPort_Ctrl_MoodLamp::Terminate()
{
    m_logger.LogVerbose() << "PPort_Ctrl_MoodLamp::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "PPort_Ctrl_MoodLamp::Terminate::StopOfferService";
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF