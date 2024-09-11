#ifndef __ZONE_3_API_LOCAL_H__
#define __ZONE_3_API_LOCAL_H__

#include <Common.h>
#include <SoaDataType.h>

extern void Zone3_RCtn_Init(void);
extern void Zone3_RCtn_Term(void);
extern void Zone3_RCtn_PowerOn(PowerState_e power);
extern void Zone3_RCtn_MoveCurtainMotor(RCtnSwitch_e btn);
extern void Zone3_RCtn_MoveCurtainMotorToPosition(int pos);

#endif