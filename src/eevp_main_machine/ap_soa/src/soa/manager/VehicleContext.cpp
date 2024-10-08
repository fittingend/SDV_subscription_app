#include <Common.h>
#include <SoaDataType.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <VehicleContext.hpp>
#include <Log.hpp>

#define VEHICLE_CONTEXT_CONF_FILE "verhicle_context.conf"
#define CONF_FILE_HEAD "VC_CONF"
#define CONF_FILE_VERSION 1

VehicleContext *VehicleContext::mInst = nullptr;

VehicleContext *VehicleContext::GetInstance()
{
    if (VehicleContext::mInst == nullptr)
    {
        VehicleContext::mInst = new VehicleContext();
    }

    return VehicleContext::mInst;
}

VehicleContext::VehicleContext()
{
    this->mSpeedValid = false;
    this->mVehicleSpeed = 0;
    this->mGearState = eGearState_P;
    this->mRCPower = ePowerState_Off;
    this->mRCSwitch = eRCtnSwitch_Unknown;
    this->mRCState = eRCtnState_Unknown;
    this->mRCLastUserSwitch = eRCtnSwitch_Unknown;
    this->mMlmPower = ePowerState_Off;
    this->mMlmColorIndex = 0;
    this->mMlmBrightness = 0;
    this->mMlmMoodMode = eMlmMoodMode_CareMood;
}

VehicleContext::~VehicleContext()
{

}

int VehicleContext::Load()
{
    struct stat file_stat;
    if (stat(DATAFILE_DIR_PATH, &file_stat) != 0)
    {
        LOG_ERROR() << "[VehicleContext::Load] path [" << DATAFILE_DIR_PATH << "] not exists...\n";
        return -1;
    }

    if (!S_ISDIR(file_stat.st_mode))
    {
        LOG_ERROR() << "[VehicleContext::Load] path [" << DATAFILE_DIR_PATH << "] not directory...\n";
        return -1;
    }

    std::stringstream ss;
    ss << DATAFILE_DIR_PATH << "/" << VEHICLE_CONTEXT_CONF_FILE;
    const char *file_path = ss.str().c_str();
    if (stat(file_path, &file_stat) != 0)
    {
        LOG_ERROR() << "[VehicleContext::Load] path [" << file_path << "] not exists...\n";
        return -1;
    }

    if (!S_ISREG(file_stat.st_mode))
    {
        LOG_ERROR() << "[VehicleContext::Load] path [" << file_path << "] not file...\n";
        return -1;
    }

    std::ifstream ifs(file_path, std::ios::binary);
    if (!ifs)
    {
        LOG_ERROR() << "[VehicleContext::Load] file [" << file_path << "] not opened for reading...\n";
        return -1;
    }

    unsigned char buffer[strlen(CONF_FILE_HEAD) + 1];
    ifs.read(reinterpret_cast<char *>(buffer), strlen(CONF_FILE_HEAD));
    if (memcmp(buffer, CONF_FILE_HEAD, sizeof(CONF_FILE_HEAD)) != 0)
    {
        LOG_ERROR() << "[VehicleContext::Load] file [" << file_path << "] is not VehicleContext Config file...\n";
        ifs.close();
        return -1;
    }

    int version;
    ifs.read(reinterpret_cast<char *>(&version), sizeof(version));
    if (version != CONF_FILE_VERSION)
    {
        LOG_ERROR() << "[VehicleContext::Load] version different: file(" << version << "), Current(" << CONF_FILE_VERSION << ")\n";
    }

    // Implement the load function using ifs:
    RCtnSwitch_e rcLastUserSwitch;
    ifs.read(reinterpret_cast<char *>(&rcLastUserSwitch), sizeof(rcLastUserSwitch));
    this->mRCLastUserSwitch = rcLastUserSwitch;

    RCtnState_e rcLastState;
    ifs.read(reinterpret_cast<char *>(&rcLastState), sizeof(rcLastState));
    this->mRCLastState = rcLastState;



    ifs.close();
    return 0;
}

int VehicleContext::Save()
{
    struct stat file_stat;
    if (stat(DATAFILE_DIR_PATH, &file_stat) != 0)
    {
        LOG_ERROR() << "[VehicleContext::Save] path [" << DATAFILE_DIR_PATH << "] not exists...\n";
        return -1;
    }

    if (!S_ISDIR(file_stat.st_mode))
    {
        LOG_ERROR() << "[VehicleContext::Save] path [" << DATAFILE_DIR_PATH << "] not directory...\n";
        return -1;
    }

    std::stringstream ss;
    ss << DATAFILE_DIR_PATH << "/" << VEHICLE_CONTEXT_CONF_FILE;
    const char *file_path = ss.str().c_str();

    std::ofstream ofs(file_path, std::ios::binary | std::ios::out);
    if (!ofs)
    {
        LOG_ERROR() << "[VehicleContext::Save] file [" << file_path << "] not opened for writing...\n";
        return -1;
    }

    ofs.write(CONF_FILE_HEAD, strlen(CONF_FILE_HEAD));

    int version = CONF_FILE_VERSION;
    ofs.write(reinterpret_cast<const char *>(&version), sizeof(version));

    // Implement the load function using ifs:
    RCtnSwitch_e rcLastUserSwitch = this->mRCLastUserSwitch;
    ofs.write(reinterpret_cast<char *>(&rcLastUserSwitch), sizeof(rcLastUserSwitch));

    RCtnState_e rcLastState = this->mRCLastState;
    ofs.write(reinterpret_cast<char *>(&rcLastState), sizeof(rcLastState));


    ofs.close();
    return 0;
}


//
// For Debugging
//

#include <Debug_DataType2String.hpp>

std::string VehicleContext::DebugInfo()
{
    std::ostringstream ss;

    ss << "VehicleContext:\r\n";
    ss << "- Speed : " << this->mVehicleSpeed << ", valid: " << (this->mSpeedValid ? "True" : "False") << "\r\n";
    ss << "- Gear  : " << getStringEnum_GearState_e(this->mGearState) << "\r\n";
    ss << "- Rear Curtain : Power(" << getStringEnum_PowerState_e(this->mRCPower) << "), Switch(" << getStringEnum_RCtnSwitch_e(this->mRCSwitch) << "), State(" << getStringEnum_RCtnState_e(this->mRCState) << ")\r\n";
    ss << "- Moodlamp : Power(" << getStringEnum_PowerState_e(this->mMlmPower) << "), ColorIndex(" << this->mMlmColorIndex << "), Brightness(" << this->mMlmBrightness << "), Mode(" << getStringEnum_MlmMoodMode_e(this->mMlmMoodMode) << ")\r\n";

    return ss.str();
}