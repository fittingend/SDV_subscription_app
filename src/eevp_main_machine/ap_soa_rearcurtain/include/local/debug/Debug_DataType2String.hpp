#ifndef __DEBUG_DATATYPE_TO_STRING_H__
#define __DEBUG_DATATYPE_TO_STRING_H__

#include <Common.h>
#include <SoaDataType.h>
#include <string>

extern std::string getStringEnum_DeviceNormal_e(DeviceNormal_e val);
extern std::string getStringEnum_PowerState_e(PowerState_e val);
extern std::string getStringEnum_GearState_e(GearState_e val);
extern std::string getStringEnum_RCtnSwitch_e(RCtnSwitch_e val);
extern std::string getStringEnum_RCtnState_e(RCtnState_e val);

#endif