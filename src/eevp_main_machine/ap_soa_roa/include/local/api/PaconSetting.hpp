#ifndef __PACON_SETTING_HPP__
#define __PACON_SETTING_HPP__

#include <Common.h>
#include <SoaDataType.h>
#include <SoaRoaSkeletonImpl.hpp>

class PaconSetting
{
private:
    static PaconSetting *mInst;

    bool mCoreInitialized;
    bool mExecutionStateReported;
    eevp::control::SoaRoaSkeletonImpl *mSoaRoa;

    PaconSetting();
    ~PaconSetting();
    void setRoa();

public:
    static PaconSetting *GetInstance();
    static void RemoveInstance();

    bool StartPacon();
    eevp::control::SoaRoaSkeletonImpl *GetSoaRoa();
};

#endif