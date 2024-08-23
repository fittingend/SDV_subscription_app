#ifndef EEVP_OTA_BACKEND_COMMON_TYPES_H_
#define EEVP_OTA_BACKEND_COMMON_TYPES_H_

namespace eevp
{
namespace ucm
{
namespace ota
{

/**
 * \brief Struct containing the file information
 */
struct FileInformation
{
    std::string filename;  // name of software
    int64_t size;  // size of software bundle file
    std::string sha1;  // sha1 checksum of software file
};

/**
 * \brief  Struct containing information of the new downloaded file.
 */
struct NewSoftwareDeploymentData
{
    std::string filesLocation;  // path to files
    FileInformation vehiclePackage;  // name of vehicle package
    std::vector<FileInformation> swPackages;  // list of SW packages
};

}  // namespace ota
}  // namespace ucm
}  // namespace eevp

#endif  // EEVP_OTA_BACKEND_COMMON_TYPES_H_
