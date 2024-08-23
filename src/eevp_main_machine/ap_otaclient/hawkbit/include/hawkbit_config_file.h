#ifndef CONFIG_FILE_H_
#define CONFIG_FILE_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "ara/log/logger.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <cstdint>

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

/**
 * @brief Class that contains the HawkBit configuration.
 */
struct ConfigClass
{
    ConfigClass()
        : logger_(ara::log::CreateLogger("Cnf", "Configuration file", ara::log::LogLevel::kVerbose))
    { }

    ~ConfigClass() = default;

    /**
     * @brief Struct containing the artifact specification
     */
    bool isInitializedCorrectly = false;

    /**
     * @brief hawkBit host or IP and port
     */
    std::string hawkbitServer;

    /**
     * @brief use https or http
     */
    bool ssl = false;

    /**
     * @brief verify https certificate
     */
    bool sslVerify = false;

    /**
     * @brief hawkBit target security token
     */
    std::string authToken;

    /**
     * @brief hawkBit gateway security token
     */
    std::string gatewayToken;

    /**
     * @brief hawkBit tenant id
     */
    std::string tenantId;

    /**
     * @brief hawkBit controller id
     */
    std::string targetName;

    /**
     * @brief  file to download
     */
    std::string downloadLocation;

    /**
     * @brief connection timeout
     */
    uint32_t connectTimeout = 0;

    /**
     * @brief reply timeout
     */
    uint32_t timeout = 0;

    /**
     * @brief wait between retries
     */
    uint32_t retryWait = 0;

    /**
     * @brief Additional attributes sent to hawkBit
     */
    std::shared_ptr<std::unordered_map<std::string, std::string>> device = nullptr;

    /**
     * @brief Loading the configuration file
     * @param configFile The configuration file
     */
    void LoadConfigFile(const char* configFile);

private:
    /**
     * @brief Initializes the additional attributes of the device
     * @param pt property tree to be read out
     * @return true if successful
     */
    bool LoadDeviceHashTable(boost::property_tree::ptree& pt);

    ara::log::Logger& logger_;
};

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp

#endif  // CONFIG_FILE_H_
