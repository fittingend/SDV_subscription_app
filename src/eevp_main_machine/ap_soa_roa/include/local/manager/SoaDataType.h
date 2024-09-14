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
    eRoaRunningState_Off,
    eRoaRunningState_On,
    eRoaRunningState_Error,

    eRoaRunningState_EndOfCase

} RoaRunningState_e;

typedef enum {
    eRoaMode_Off,
    eRoaMode_Normal,
    eRoaMode_Advanced,

    eRoaMode_EndOfCase
} RoaMode_e;

typedef enum {
    eRoaSensorError_Ok,
    eRoaSensorError_Snsr,
    eRoaSensorError_Blckge,

    eRoaSensorError_EndOfCase
} RoaSensorError_e;

#endif