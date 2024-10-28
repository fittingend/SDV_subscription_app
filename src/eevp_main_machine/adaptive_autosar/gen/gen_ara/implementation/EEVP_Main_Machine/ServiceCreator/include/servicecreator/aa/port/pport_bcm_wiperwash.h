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
/// GENERATED FILE NAME               : pport_bcm_wiperwash.h
/// SOFTWARE COMPONENT NAME           : PPort_BCM_WiperWash
/// GENERATED DATE                    : 2024-10-17 15:32:20
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_BCM_WIPERWASH_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_BCM_WIPERWASH_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "eevp/simulation/bcm_wiperwash_skeleton.h"
 
#include "ara/log/logger.h"
 
#include <mutex>
#include <thread>
 
namespace eevp
{
namespace simulation
{
namespace skeleton
{
 
class PPort_BCM_WiperWashSkeletonImpl : public BCM_WiperWashSkeleton
{
public:
    /// @brief Constructor
    PPort_BCM_WiperWashSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);
    
    /// @brief Request with Response method, getWipingInterval
    ara::core::Future<BCM_WiperWashSkeleton::getWipingIntervalOutput> getWipingInterval() override;
    
    /// @brief Request with Response method, getWipingLevel
    ara::core::Future<BCM_WiperWashSkeleton::getWipingLevelOutput> getWipingLevel() override;
    
    /// @brief Request with Response method, isWiping
    ara::core::Future<BCM_WiperWashSkeleton::isWipingOutput> isWiping() override;
    
    /// @brief Request with Response method, notifyWipingStatus
    ara::core::Future<BCM_WiperWashSkeleton::notifyWipingStatusOutput> notifyWipingStatus() override;
    
    /// @brief Request with Response method, setWipingInterval
    ara::core::Future<BCM_WiperWashSkeleton::setWipingIntervalOutput> setWipingInterval(const std::uint16_t& wipingInterval) override;
    
    /// @brief Request with Response method, setWipingLevel
    ara::core::Future<BCM_WiperWashSkeleton::setWipingLevelOutput> setWipingLevel(const eevp::simulation::BCM_WipingLevel& wipingLevel) override;
    
    /// @brief Request with Response method, setWipingLevelImme
    ara::core::Future<BCM_WiperWashSkeleton::setWipingLevelImmeOutput> setWipingLevelImme(const eevp::simulation::BCM_WipingLevel& wipingLevel) override;
    
    /// @brief Request with Response method, startWiping
    ara::core::Future<BCM_WiperWashSkeleton::startWipingOutput> startWiping() override;
    
    /// @brief Request with Response method, stopWiping
    ara::core::Future<BCM_WiperWashSkeleton::stopWipingOutput> stopWiping() override;
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
 
class PPort_BCM_WiperWash
{
public:
    /// @brief Constructor
    PPort_BCM_WiperWash();
    
    /// @brief Destructor
    ~PPort_BCM_WiperWash();
    
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
    std::shared_ptr<eevp::simulation::skeleton::BCM_WiperWashSkeletonImpl> m_interface;
    
};
 
} /// namespace port
} /// namespace aa
} /// namespace servicecreator
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_PPORT_SERVICECREATOR_AA_PPORT_BCM_WIPERWASH_H