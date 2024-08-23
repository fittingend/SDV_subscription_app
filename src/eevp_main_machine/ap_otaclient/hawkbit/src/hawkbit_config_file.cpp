#include "hawkbit_config_file.h"

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

// TODO : Verify the values of config file, Defaut values, Return error of config file

bool ConfigClass::LoadDeviceHashTable(boost::property_tree::ptree& pt)
{
    if (device != nullptr) {
        logger_.LogError() << "Something was  wrong during memory allocation";
        return false;
    }

    device.reset(new std::unordered_map<std::string, std::string>);

    (*device)["product"] = pt.get<std::string>("device.product");
    (*device)["model"] = pt.get<std::string>("device.model");
    (*device)["serialnumber"] = pt.get<std::string>("device.serialnumber");
    (*device)["hw_revision"] = pt.get<std::string>("device.hw_revision");
    (*device)["key1"] = pt.get<std::string>("device.key1");
    (*device)["key2"] = pt.get<std::string>("device.key2");

    logger_.LogError() << "Device was initialized successfully";

    return true;
}

void ConfigClass::LoadConfigFile(const char* configFile)
{

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(configFile, pt);

    // TODO check if initialization was ok,if not return false

    hawkbitServer = pt.get<std::string>("client.hawkbit_server");
    ssl = pt.get<bool>("client.ssl");
    sslVerify = pt.get<bool>("client.ssl_verify");
    tenantId = pt.get<std::string>("client.tenant_id");
    targetName = pt.get<std::string>("client.target_name");
    authToken = pt.get<std::string>("client.auth_token");
    gatewayToken = pt.get<std::string>("client.gateway_token");
    downloadLocation = pt.get<std::string>("client.download_location");
    retryWait = pt.get<int>("client.retry_wait");
    connectTimeout = pt.get<uint32_t>("client.connect_timeout");
    timeout = pt.get<uint32_t>("client.timeout");

    if (!LoadDeviceHashTable(pt)) {
        logger_.LogError() << "Cannot initialize device";
        return;
    }

    isInitializedCorrectly = true;
}

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp
