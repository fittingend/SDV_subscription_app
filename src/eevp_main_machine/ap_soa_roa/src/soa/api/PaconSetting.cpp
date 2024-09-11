#include <Common.h>
#include <SoaDataType.h>
#include "ara/core/initialization.h"
#include "ara/exec/execution_client.h"
#include <Api_SoaRoa.hpp>
#include <Api_Zone2Roa.hpp>
#include <PaconSetting.hpp>
#include <Log.hpp>

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
    Zone2_SOA_Term();
    SOA_ROA_Term();

    if (this->mCoreInitialized)
    {
        ara::core::Deinitialize();
    }
}

bool PaconSetting::StartPacon()
{
    LOG_INFO() << "[PaconSetting::StartPacon] (+)\n";
#if defined(DISABLE_SOMEIP)
    LOG_INFO() << "[PaconSetting::StartPacon] (-)\n";
    return true;
#else
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

    SOA_ROA_Init();
    Zone2_SOA_Init();

    LOG_INFO() << "[PaconSetting::StartPacon] (-)\n";
    return true;
#endif
}
