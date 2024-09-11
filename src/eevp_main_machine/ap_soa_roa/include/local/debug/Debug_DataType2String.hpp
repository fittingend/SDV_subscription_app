#ifndef __DEBUG_DATATYPE_TO_STRING_H__
#define __DEBUG_DATATYPE_TO_STRING_H__

#include <Common.h>
#include <SoaDataType.h>
#include <string>

std::string getStringEnum_DeviceNormal_e(DeviceNormal_e val);
std::string getStringEnum_PowerState_e(PowerState_e val);
std::string getStringEnum_RoaRunningState_e(RoaRunningState_e val);
std::string getStringEnum_RoaMode_e(RoaMode_e val);
std::string getStringEnum_RoaSensorError_e(RoaSensorError_e val);

#endif