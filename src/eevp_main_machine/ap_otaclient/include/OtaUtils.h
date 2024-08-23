#ifndef OTA_UTILS_H
#define OTA_UTILS_H

#include <fstream>
#include <vector>

#include <ara/log/logger.h>

#include <json-c/json.h>

#include "eevp/type/impl_type_string.h"

#include "OtaDefine.h"

namespace eevp {
namespace ota {

struct stSessionInfo {
    ara::core::String packageName;
    ara::core::String softwareCluster;
    ara::core::String version;
    ara::core::String actionType;

    void clear() {
        packageName = "";
        softwareCluster = "";
        version = "";
        actionType = "";
    }

    stSessionInfo() {
        clear();
    }
};

class OtaUtils {
public:
    static OtaUtils* getInstance();

    ~OtaUtils();

    bool loadBinaryFile(const ara::core::String& filePath, std::vector<uint8_t>& binaryPackage);
    bool loadPackageFile(const ara::core::String& packageFilePath, std::vector<char>& buffer);

    bool parseVpmJson(const ara::core::String& vpmPath, stSessionInfo& sInfo);

#ifdef UCM_TEST
    bool isInstall();
    bool isUpdate();
#endif

private:
    static OtaUtils* instance;

    OtaUtils();
    OtaUtils(const OtaUtils&) = delete;
    OtaUtils& operator=(const OtaUtils&) = delete;

    ara::log::Logger& mLogger;
};

} /// namespace ota
} /// namespace eevp

#endif  // OTA_UTILS_H
