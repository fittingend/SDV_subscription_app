#include <Common.h>
#include <SoaDataType.h>
#include <string.h>
#include <VehicleContext.hpp>
#include <RearCurtainManager.hpp>
#include <Api_SoaRcurtain.hpp>
#include <SoaRcurtainSkeletonImpl.hpp>
#if !defined(DISABLE_SOMEIP)
#include <PaconSetting.hpp>
#endif
#include <Log.hpp>

static eevp::control::SoaRcurtainSkeletonImpl *s_inst = nullptr;

void Api_Rcurtain_Init(void)
{
    if (!s_inst)
    {
        ara::core::InstanceSpecifier specifier("SOA_RearCurtain/AA/PPort_SOA_RearCurtain");
        s_inst = new eevp::control::SoaRcurtainSkeletonImpl(specifier);
        s_inst->OfferService();
    }
}

void Api_Rcurtain_Term(void)
{
    if (s_inst)
    {
        delete s_inst;
        s_inst = nullptr;
    }
}

int Api_Rcurtain_Method_RequestRearCurtainOperation(RCtnSwitch_e eDirection)
{
    LOG_DEBUG() << "\n";
    RearCurtainManager *mgr = RearCurtainManager::GetInstance();
    return mgr->OnCmdRequestRearCurtainOperation(eDirection);
}

int Api_Rcurtain_Method_RequestRearCurtainPosition(int percentage)
{
    LOG_DEBUG() << "\n";
    RearCurtainManager *mgr = RearCurtainManager::GetInstance();
    return mgr->OnCmdRequestRearCurtainPosition(percentage);
}

void Api_Rcurtain_Field_SoaRctnStatus()
{
    if (s_inst != nullptr)
    {
        s_inst->UpdateStatus();
    }
}
