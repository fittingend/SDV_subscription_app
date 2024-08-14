#ifndef __PACON_SETTING_HPP__
#define __PACON_SETTING_HPP__

#include <Common.h>
#include <SoaDataType.h>
#include <SoaRcurtainSkeletonImpl.hpp>

class PaconSetting
{
private:
    static PaconSetting *mInst;

    bool mCoreInitialized;
    bool mExecutionStateReported;
    eevp::control::SoaRcurtainSkeletonImpl *mSoaRctn;

    PaconSetting();
    ~PaconSetting();
    void setRearCurtain();

public:
    static PaconSetting *GetInstance();
    static void RemoveInstance();

    bool StartPacon();

    eevp::control::SoaRcurtainSkeletonImpl *GetSoaRcurtain();
};

#endif