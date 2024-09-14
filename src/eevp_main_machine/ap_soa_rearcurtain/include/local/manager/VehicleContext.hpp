#ifndef __VEHICLE_CONTEXT_HPP__
#define __VEHICLE_CONTEXT_HPP__

#include <Common.h>
#include <SoaDataType.h>

#if defined(VEHICLE_CONTEXT_USE_ATOMIC)
#include <atomic>
#endif
#include <string>

class VehicleContext
{
private:
    static VehicleContext *mInst;

    VehicleContext();
    ~VehicleContext();

public:
    std::atomic<bool> mSpeedValid;
    std::atomic<int> mVehicleSpeed;
    std::atomic<GearState_e> mGearState;

    // Rear Curtain
    std::atomic<PowerState_e> mRctnPower;
    std::atomic<RCtnSwitch_e> mRctnSwitch;
    std::atomic<RCtnState_e> mRctnState;
    std::atomic<int> mRctnInputPosition;
    std::atomic<DeviceNormal_e> mIsNormal;

    std::atomic<bool> mMotorMoving;
    std::atomic<int> mRctnZoneInputPosition;
    std::atomic<int> mRctnCurrPosition;

    //
    // Methods
    //
    static VehicleContext *GetInstance();

    int Load(void);
    int Save(void);
    std::string DebugInfo(void);

};

#endif