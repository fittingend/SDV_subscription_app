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
/// GENERATED FILE NAME               : pport_dms_func.cpp
/// SOFTWARE COMPONENT NAME           : PPort_DMS_Func
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "servicecreator/aa/port/pport_dms_func.h"
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
PPort_DMS_FuncSkeletonImpl::PPort_DMS_FuncSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : DMS_FuncSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
ara::core::Future<DMS_FuncSkeleton::isDetectDrowsyOutput> PPort_DMS_FuncSkeletonImpl::isDetectDrowsy()
{
    isDetectDrowsyOutput response;
    ara::core::Promise<isDetectDrowsyOutput> promise;
    
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
 
PPort_DMS_Func::PPort_DMS_Func()
    : m_logger(ara::log::CreateLogger("SVCC", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
PPort_DMS_Func::~PPort_DMS_Func()
{
}
 
void PPort_DMS_Func::Start()
{
    m_logger.LogVerbose() << "PPort_DMS_Func::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"ServiceCreator/AA/PPort_DMS_Func"};
    m_interface = std::make_shared<eevp::simulation::skeleton::DMS_FuncSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "PPort_DMS_Func::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "PPort_DMS_Func::Start::OfferService::" << offer.Error().Message();
    }
}
 
void PPort_DMS_Func::Terminate()
{
    m_logger.LogVerbose() << "PPort_DMS_Func::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "PPort_DMS_Func::Terminate::StopOfferService";
}
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
/// EOF