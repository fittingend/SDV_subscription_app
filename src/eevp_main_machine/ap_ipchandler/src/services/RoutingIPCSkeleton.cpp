/* Copyright 2024 Hyundai Mobis Co., Ltd. All rights reserved */

#include <cstring>
#include <services/RoutingIPCSkeleton.hpp>
#include <ipc/IPCIntf.hpp>

using namespace ara::com;
using namespace ara::core;
using namespace eevp::ipchandler::type;
using namespace eevp::ipchandler::service;

namespace routingipc {

static InstanceSpecifier kRootSwComponent{"IPCHandler/RootSwComponent/IPCHandler"};

IPCRoutingIPCSkeleton::IPCRoutingIPCSkeleton()
    : Main_IPC_RoutingIPCSkeleton(kRootSwComponent, MethodCallProcessingMode::kEventSingleThread),
    cpLock_{},
    apLock_{},
    sysCtrlReq_{0xff}
{
    memset((void *) &cpInfo_, 0, sizeof(CpInfo));
}

IPCRoutingIPCSkeleton::~IPCRoutingIPCSkeleton()
{
    StopOfferService();
}

Future<skeleton::Main_IPC_RoutingIPCSkeleton::SystemControlResponseOutput>
IPCRoutingIPCSkeleton::SystemControlResponse(const SysCtrlResp& response)
{
    Promise<skeleton::Main_IPC_RoutingIPCSkeleton::SystemControlResponseOutput> p;
    skeleton::Main_IPC_RoutingIPCSkeleton::SystemControlResponseOutput output{};
    p.set_value(output);

    {
        std::lock_guard<std::mutex> lock(apLock_);
        // TBD : SysCtrlReq  and SysCtrlResp will be updated when the scenario is written.
        apInfo_.system_ctrl_resp = static_cast<uint8_t>(response);
        ipc::IPCIntf::getInstance().SendApInfo(apInfo_);
    }
    return p.get_future();
}

Future<skeleton::Main_IPC_RoutingIPCSkeleton::GetOneTimeSystemInfoOutput>
IPCRoutingIPCSkeleton::GetOneTimeSystemInfo()
{
    OneTimeSysInfo sysInfo;
    {
        std::lock_guard<std::mutex> lock(cpLock_);
        std::string hw_version(cpInfo_.hw_version, 3);
        std::string sw_version(cpInfo_.mcu_sw_version, 5);
        VersionInfo version{hw_version, sw_version};
        sysInfo = OneTimeSysInfo{version};
    }

    Promise<skeleton::Main_IPC_RoutingIPCSkeleton::GetOneTimeSystemInfoOutput> p;
    skeleton::Main_IPC_RoutingIPCSkeleton::GetOneTimeSystemInfoOutput output{sysInfo};
    p.set_value(output);

    return p.get_future();
}

Future<skeleton::Main_IPC_RoutingIPCSkeleton::SetAPSystemInfoOutput>
IPCRoutingIPCSkeleton::SetAPSystemInfo(const String& apVersion)
{
    Promise<skeleton::Main_IPC_RoutingIPCSkeleton::SetAPSystemInfoOutput> p;
    skeleton::Main_IPC_RoutingIPCSkeleton::SetAPSystemInfoOutput output{};
    p.set_value(output);

    {
        std::lock_guard<std::mutex> lock(apLock_);
        memset(&apInfo_.ap_sw_version, 0, sizeof(apInfo_.ap_sw_version));
        memcpy(&apInfo_.ap_sw_version, apVersion.c_str(), sizeof(apInfo_.ap_sw_version));
        // TBD: esw_sw_version, not used at the moment

        ipc::IPCIntf::getInstance().SendApInfo(apInfo_);
    }

    return p.get_future();
}

Future<skeleton::Main_IPC_RoutingIPCSkeleton::ASMInfoRequestOutput>
IPCRoutingIPCSkeleton::ASMInfoRequest()
{
    Promise<skeleton::Main_IPC_RoutingIPCSkeleton::ASMInfoRequestOutput> p;
    skeleton::Main_IPC_RoutingIPCSkeleton::ASMInfoRequestOutput output{};
    p.set_value(output);

    {
        std::lock_guard<std::mutex> lock(apLock_);
        ipc::IPCIntf::getInstance().SendApInfo(apInfo_);
    }

    return p.get_future();
}

void IPCRoutingIPCSkeleton::UpdateCpInfo(const CpInfo& newInfo)
{

    std::uint8_t newReq;
    {
        std::lock_guard<std::mutex> lock(cpLock_);
        cpInfo_ = newInfo;

        // TBD : SysCtrlReq  and SysCtrlResp will be updated when the scenario is written.
        newReq = cpInfo_.system_ctrl_req;
    }

    // No need to lock for sysCtrlReq_ since
    //   UpdateCpInfo is called from a thread,
    //   and sysCtrlReq_ is used only in this function.
    // This is to call SystemControlRequest.Send when sysCtrlReq is changed.
    // TBD : Check there is an Event or Field SOME/IP option to send only if the value is differed.
    if (newReq != sysCtrlReq_) {
        sysCtrlReq_ = newReq;
        SysCtrlReq systemSysCtrlReq = static_cast<SysCtrlReq>(sysCtrlReq_);
        SystemControlRequest.Send(systemSysCtrlReq);
    }

    SendPowerState();
}

void IPCRoutingIPCSkeleton::SendPowerState()
{
    PowerState powerState = {false, false, false};
    {
        std::lock_guard<std::mutex> lock(cpLock_);

        if (cpInfo_.acc != 0x00) {
            powerState.accState = true;
        }
        if (cpInfo_.ign1 != 0x00) {
            powerState.ign1State = true;
        }
        if (cpInfo_.ign3 != 0x00) {
            powerState.ign3State = true;
        }
    }

    PeriodicSystemInfo.Send(powerState);
}

ApInfo IPCRoutingIPCSkeleton::GetApInfo()
{
    std::lock_guard<std::mutex> lock(apLock_);
    return apInfo_;
}

CpInfo IPCRoutingIPCSkeleton::GetCpInfo()
{
    std::lock_guard<std::mutex> lock(cpLock_);
    return cpInfo_;
}

#ifdef ENABLE_TEST
void IPCRoutingIPCSkeleton::SetApInfo(const ApInfo &apInfo)
{
    std::lock_guard<std::mutex> lock(apLock_);
    apInfo_ = apInfo;
}
#endif

} // routingipc