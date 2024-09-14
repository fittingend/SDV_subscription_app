#ifndef __API_SOA_ROA_HPP__
#define __API_SOA_ROA_HPP__

#include <SoaDataType.h>

extern void SOA_ROA_Init();
extern void SOA_ROA_Term();
extern void SOA_ROA_SetMode(RoaMode_e mode);
extern void SOA_ROA_ResetSensor();
extern void SOA_ROA_StartSensor();
extern void SOA_ROA_StopSensor();
extern void SOA_ROA_UpdateDeviceNormal();
extern void SOA_ROA_UpdateRunningState();
extern void SOA_ROA_UpdateRoaMode();
extern void SOA_ROA_UpdateDetectState();
extern void SOA_ROA_UpdateDetectCount();
extern void SOA_ROA_UpdateSensorError();

#endif // __API_SOA_ROA_HPP__