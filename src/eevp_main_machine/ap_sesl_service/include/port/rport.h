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
/// GENERATED FILE NAME               : rport.h
/// SOFTWARE COMPONENT NAME           : RPort
/// GENERATED DATE                    : 2024-11-15 21:01:32
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SESL_EXECUTABLE_ROOTSWCOMPONENT_RPORT_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SESL_EXECUTABLE_ROOTSWCOMPONENT_RPORT_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ara/com/sesl_serviceinterface_proxy.h"

#include "ara/log/logger.h"

#include <mutex>
#include <thread>

using namespace ara::com;

namespace sesl_executable
{
    namespace rootswcomponent
    {
        namespace port
        {

            class RPort
            {
            public:
                /// @brief Constructor
                RPort();

                /// @brief Destructor
                ~RPort();

                /// @brief Start port
                bool Initialize();

                bool Start();

                void Run();

                /// @brief Terminate port
                void Terminate();

                /// @brief Request with Response method using by software component, SESL_Method
                void RequestSESL_Receive();

                void RequestSESL_Send(const ara::SESL::Vehicle_Data &Send_Argument);

                void SESL_Logic();

                ara::SESL::Vehicle_Data receive_Data;
                ara::SESL::Vehicle_Data send_Data;

            private:
                /// @brief Callback for find service
                void FindServiceCallback(ara::com::ServiceHandleContainer<ara::com::proxy::SESL_ServiceInterfaceProxy::HandleType> container,
                                         ara::com::FindServiceHandle findHandle);

                /// @brief Logger for this port
                ara::log::Logger &mLogger;

                /// @brief Mutex for this port
                std::mutex mHandle;

                /// @brief AUTOSAR Port Interface
                std::shared_ptr<ara::com::proxy::SESL_ServiceInterfaceProxy> mProxy;

                /// @brief Find service handle
                std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

                std::condition_variable cvHandle;
            };

        } /// namespace port
    } /// namespace rootswcomponent
} /// namespace sesl_executable

#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_SESL_EXECUTABLE_ROOTSWCOMPONENT_RPORT_H