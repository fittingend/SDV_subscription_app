#include <Common.h>
#include <SoaDataType.h>
#include <string>
#include <Debug_DataType2String.hpp>

std::string getStringEnum_DeviceNormal_e(DeviceNormal_e val)
{
    switch (val)
    {
    case eDeviceNormal_Ok:          return "OK";
    case eDeviceNormal_Abnormal:    return "ABNORMAL";
    default:
        break;
    }

    return "UNKNOWN";
}

std::string getStringEnum_PowerState_e(PowerState_e val)
{
    switch (val)
    {
    case ePowerState_On:    return "ON";
    case ePowerState_Off:   return "OFF";
    case ePowerState_Error: return "Error";
    default:
        break;
    }

    return "UNKNOWN";
}

std::string getStringEnum_RoaRunningState_e(RoaRunningState_e val)
{
    switch (val)
    {
    case eRoaRunningState_Off:      return "OFF";
    case eRoaRunningState_On:       return "ON";
    case eRoaRunningState_Error:    return "Error";
    default:
        break;
    }

    return "UNKNOWN";
}

std::string getStringEnum_RoaMode_e(RoaMode_e val)
{
    switch (val)
    {
    case eRoaMode_Off:          return "OFF";
    case eRoaMode_Normal:       return "Normal";
    case eRoaMode_Advanced:     return "Advanced";
    default:
        break;
    }

    return "UNKNOWN";
}

std::string getStringEnum_RoaSensorError_e(RoaSensorError_e val)
{
    switch (val)
    {
    case eRoaSensorError_Ok:         return "OK";
    case eRoaSensorError_Snsr:       return "SNSR";
    case eRoaSensorError_Blckge:     return "BLCKGE";
    default:
        break;
    }

    return "UNKNOWN";

}

