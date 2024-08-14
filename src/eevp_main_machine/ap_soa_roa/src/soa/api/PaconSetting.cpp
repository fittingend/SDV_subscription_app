#include <Common.h>
#include <SoaDataType.h>
#include "ara/core/initialization.h"
#include "ara/exec/execution_client.h"
#include "eevp/control/soaroa_common.h"
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
    this->mSoaRoa = nullptr;
}


PaconSetting::~PaconSetting()
{
    if (this->mSoaRoa != nullptr) {
        delete this->mSoaRoa;
        this->mSoaRoa = nullptr;
    }

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

    this->setRoa();

    LOG_INFO() << "[PaconSetting::StartPacon] (-)\n";
    return true;
#endif
}

void PaconSetting::setRoa()
{
    ara::core::InstanceSpecifier specifier("SOA_ROA/AA/PPort_SOA_ROA");
    this->mSoaRoa = new SoaRoaSkeletonImpl(specifier);
    this->mSoaRoa->OfferService();
}

eevp::control::SoaRoaSkeletonImpl *PaconSetting::GetSoaRoa()
{
    return this->mSoaRoa;
}