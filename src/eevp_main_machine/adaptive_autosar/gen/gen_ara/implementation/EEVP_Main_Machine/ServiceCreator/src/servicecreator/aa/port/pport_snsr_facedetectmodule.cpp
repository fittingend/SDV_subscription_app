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
/// GENERATED FILE NAME               : pport_snsr_facedetectmodule.cpp
/// SOFTWARE COMPONENT NAME           : PPort_Snsr_FaceDetectModule
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/pport_snsr_facedetectmodule.h"
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
PPort_Snsr_FaceDetectModuleSkeletonImpl::PPort_Snsr_FaceDetectModuleSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : Snsr_FaceDetectModuleSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
ara::core::Future<Snsr_FaceDetectModuleSkeleton::getEmotionOutput> PPort_Snsr_FaceDetectModuleSkeletonImpl::getEmotion()
{
    getEmotionOutput response;
    ara::core::Promise<getEmotionOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Snsr_FaceDetectModuleSkeleton::isRunningOutput> PPort_Snsr_FaceDetectModuleSkeletonImpl::isRunning()
{
    isRunningOutput response;
    ara::core::Promise<isRunningOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Snsr_FaceDetectModuleSkeleton::turnOffOutput> PPort_Snsr_FaceDetectModuleSkeletonImpl::turnOff()
{
    turnOffOutput response;
    ara::core::Promise<turnOffOutput> promise;
    
    // put your logic
    
    promise.set_value(response);
    return promise.get_future();
}
 
ara::core::Future<Snsr_FaceDetectModuleSkeleton::turnOnOutput> PPort_Snsr_FaceDetectModuleSkeletonImpl::turnOn()
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
 
PPort_Snsr_FaceDetectModule::PPort_Snsr_FaceDetectModule()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
PPort_Snsr_FaceDetectModule::~PPort_Snsr_FaceDetectModule()
{
}
 
void PPort_Snsr_FaceDetectModule::Start()
{
    m_logger.LogVerbose() << "PPort_Snsr_FaceDetectModule::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/PPort_Snsr_FaceDetectModule"};
    m_interface = std::make_shared<eevp::simulation::skeleton::Snsr_FaceDetectModuleSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "PPort_Snsr_FaceDetectModule::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "PPort_Snsr_FaceDetectModule::Start::OfferService::" << offer.Error().Message();
    }
}
 
void PPort_Snsr_FaceDetectModule::Terminate()
{
    m_logger.LogVerbose() << "PPort_Snsr_FaceDetectModule::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "PPort_Snsr_FaceDetectModule::Terminate::StopOfferService";
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF