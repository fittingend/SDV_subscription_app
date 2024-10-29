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
/// GENERATED FILE NAME               : pport_vcs_accrpedal.cpp
/// SOFTWARE COMPONENT NAME           : PPort_VCS_AccrPedal
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/pport_vcs_accrpedal.h"
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
PPort_VCS_AccrPedalSkeletonImpl::PPort_VCS_AccrPedalSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : VCS_AccrPedalSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
ara::core::Future<VCS_AccrPedalSkeleton::nofityStatusOutput> PPort_VCS_AccrPedalSkeletonImpl::nofityStatus()
{
    nofityStatusOutput response;
    ara::core::Promise<nofityStatusOutput> promise;
    
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
 
PPort_VCS_AccrPedal::PPort_VCS_AccrPedal()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
PPort_VCS_AccrPedal::~PPort_VCS_AccrPedal()
{
}
 
void PPort_VCS_AccrPedal::Start()
{
    m_logger.LogVerbose() << "PPort_VCS_AccrPedal::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/PPort_VCS_AccrPedal"};
    m_interface = std::make_shared<eevp::simulation::skeleton::VCS_AccrPedalSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "PPort_VCS_AccrPedal::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "PPort_VCS_AccrPedal::Start::OfferService::" << offer.Error().Message();
    }
}
 
void PPort_VCS_AccrPedal::Terminate()
{
    m_logger.LogVerbose() << "PPort_VCS_AccrPedal::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "PPort_VCS_AccrPedal::Terminate::StopOfferService";
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF