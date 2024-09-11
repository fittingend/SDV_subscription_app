#include <CmdMgr.hpp>
#include <CmdLists.hpp>
#include <algorithm>
#include <sstream>
#include <string>
#include <string.h>
#include <Zone3RcurtainProxyImpl.hpp>

static int cmd_driveseat_get_status (std::list<std::string> &argList)
{
    std::stringstream ss;

    auto *inst = zone3::rcurtain::control::Zone3RearCurtainProxyImpl::GetInstance();
    zone3::rcurtain::control::EcuRcurtainStatus status;

    ss << "getterRcurtainStatus (+)";
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");

    bool ret = inst->getterRcurtainStatus(status);

    ss << "getterRcurtainStatus (-) ret=" << (ret == true) ? "TRUE" : "FALSE";
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");

    ss << "curMotorDir = " << (int)status.curMotorDir;
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");
    ss << "curMotorLimit = " << (int)status.curMotorLimit;
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");
    ss << "motorCurrent = " << (int)status.motorCurrent;
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");
    ss << "isNormal = " << (int)status.isNormal;
    CmdMgr::GetInstance()->Println(ss.str());
    ss.str("");

    return 0;
}

static int cmd_driveseat_motor (std::list<std::string> &argList)
{
    std::stringstream ss;

    auto *inst = zone3::rcurtain::control::Zone3RearCurtainProxyImpl::GetInstance();
    if (!inst->isServiceFound())
    {
        ss << "Zone3RearCurtain Service not found" ;
        CmdMgr::GetInstance()->Println(ss.str());
        return 0;
    }

    if (argList.size() <= 0)
    {
        ss << "Usage: ecu motor [slide] [recline] [height] [rlxTilt]" ;
        CmdMgr::GetInstance()->Println(ss.str());
        return 0;
    }
    std::string arg = std::move(argList.front());
    argList.pop_front();

    int num;
    bool valid;
    std::stringstream ss2(arg);
    ss2 >> num;
    if (ss2.fail())
    {
        ss << "Usage: ecu motor [motor_opnum]" ;
        CmdMgr::GetInstance()->Println(ss.str());
        return 0;
    }

    inst->controlMotor((std::uint8_t)num);

    return 0;
};

static int cmd_Ecu(void *item, std::list<std::string> argList)
{
    std::stringstream ss;
    if (argList.size() <= 0)
    {
        return -1;
    }

    std::string cmd = std::move(argList.front());
    argList.pop_front();
    std::for_each(cmd.begin(), cmd.end(), [](auto &c) { c = tolower(c); });

    if (cmd == "motor")
    {
        return cmd_driveseat_motor(argList);
    }
    else if (cmd == "status")
    {
        return cmd_driveseat_get_status(argList);
    }
    else
    {
        ss << "No Sub-Cmd(" << cmd << ") in the CMD [ecu]";
        CmdMgr::GetInstance()->Println(ss.str());
        return -1;
    }

    return 0;
}

class RearCurtainListener : public zone3::rcurtain::control::IZone3RearCurtainListener
{
public:
    void notifyRcurtainStatus(const zone3::rcurtain::control::EcuRcurtainStatus &fieldValue)
    {
        std::stringstream ss;
        ss << "notifyRcurtainStatus (+)";
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");

        ss << "RcurtainStatus curMotorDir = " << (int)fieldValue.curMotorDir;
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");

        ss << "RcurtainStatus curMotorLimit = " << (int)fieldValue.curMotorLimit;
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");

        ss << "RcurtainStatus motorCurrent = " << (int)fieldValue.motorCurrent;
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");

        ss << "RcurtainStatus isNormal = " << (int)fieldValue.isNormal;
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");

        ss << "notifyRcurtainStatus (-)";
        CmdMgr::GetInstance()->Println(ss.str());
        ss.str("");
    }

    void getRcurtainStatus()
    {

    }

};

void RegisterEcuApi()
{
    CmdMgr::GetInstance()->InsertCommand("ecu",
            "ecu [motor|status] (args...)",
            "debug for ECU Rear Curtain APIs",
            "debug for ECU Rear Curtain APIs",
            cmd_Ecu, nullptr);

    auto *inst = zone3::rcurtain::control::Zone3RearCurtainProxyImpl::GetInstance();
    inst->setEventListener(std::make_shared<RearCurtainListener>());
}