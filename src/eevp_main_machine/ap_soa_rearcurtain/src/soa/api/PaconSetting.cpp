#include <Common.h>
#include <SoaDataType.h>
#include "ara/core/initialization.h"
#include "ara/exec/execution_client.h"
#include "eevp/control/soarcurtain_common.h"
#include <Api_SoaRcurtain.hpp>
#include <Api_Zone3Rcurtain.hpp>
#include <PaconSetting.hpp>
#include <Log.hpp>

using namespace eevp::control;

PaconSetting *PaconSetting::mInst = nullptr;

PaconSetting *PaconSetting::GetInstance()
{
    if (PaconSetting::mInst == nullptr)
    {
        PaconSetting::mInst = new PaconSetting();
    }

    return PaconSetting::mInst;
}

void PaconSetting::RemoveInstance()
{


    if (PaconSetting::mInst != nullptr)
    {
        delete PaconSetting::mInst;
        PaconSetting::mInst = nullptr;
    }
}

PaconSetting::PaconSetting()
{
    this->mCoreInitialized = false;
    this->mExecutionStateReported = false;
}


PaconSetting::~PaconSetting()
{
    Zone3_RCtn_Term();
    Api_Rcurtain_Term();

    if (this->mCoreInitialized)
    {
        ara::core::Deinitialize();
    }
}

bool PaconSetting::StartPacon()
{
    LOG_INFO() << "[PaconSetting::StartPacon] (+)\n";
    LOG_DEBUG() << "[PaconSetting::StartPacon] ara::core::Initialize() (+)\n";
    ara::core::Initialize();
    this->mCoreInitialized = true;
    LOG_DEBUG() << "[PaconSetting::StartPacon] ara::core::Initialize() (-)\n";

    LOG_DEBUG() << "[PaconSetting::StartPacon] ara::exec::ExecutionClient::ReportExecutionState (+)\n";
    ara::exec::ExecutionClient execClient{};
    ara::core::Result<void> result = execClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    if (!result)
    {
        LOG_ERROR() << "[PaconSetting::StartPacon] (-) execClient.ReportExecutionState failed\n";
        return false;
    }
    this->mExecutionStateReported = true;
    LOG_DEBUG() << "[PaconSetting::StartPacon] ara::exec::ExecutionClient::ReportExecutionState (-)\n";

    Api_Rcurtain_Init();
    Zone3_RCtn_Init();

    LOG_INFO() << "[PaconSetting::StartPacon] (-)\n";
    return true;
}
