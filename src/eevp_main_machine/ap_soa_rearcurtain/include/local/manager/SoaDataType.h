#ifndef __SOA_DATA_TYPE_H__
#define __SOA_DATA_TYPE_H__

#include <Common.h>

typedef enum {
    eDeviceNormal_Ok,
    eDeviceNormal_Abnormal,

    eDeviceNormal_EndOfCase
} DeviceNormal_e;

typedef enum {
    ePowerState_Off,
    ePowerState_On,
    ePowerState_Error,

    ePowerState_EndOfCase
} PowerState_e;

typedef enum {
    eGearState_P,
    eGearState_D,
    eGearState_N,
    eGearState_R,
    eGearState_Fault,
    eGearState_Unknown,

    eGearState_EndOfCase
} GearState_e;

typedef enum {
    eRCtnSwitch_Off,
    eRCtnSwitch_OpenOn,
    eRCtnSwitch_CloseOn,
    eRCtnSwitch_Unknown,

    eRCtnSwitch_EndOfCase
} RCtnSwitch_e;

typedef enum {
    eRCtnState_FullyOpened,
    eRCtnState_FullyClosed,
    eRCtnState_PartlyOpened,
    eRCtnState_Opening,
    eRCtnState_Closing,
    eRCtnState_Unknown,
    eRCtnState_Error,

    eRCtnState_EndOfCase
} RCtnState_e;
#endif