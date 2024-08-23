#include "OtaUtils.h"

namespace eevp {
namespace ota {

OtaUtils *OtaUtils::instance = NULL;

OtaUtils*
OtaUtils::getInstance() {
    if (instance == NULL) {
        instance = new OtaUtils();
    }

    return instance;
}

OtaUtils::OtaUtils() :
        mLogger(ara::log::CreateLogger("OTAC", "UTIL", ara::log::LogLevel::kInfo)) {
}

OtaUtils::~OtaUtils() {}

bool
OtaUtils::loadBinaryFile(const ara::core::String& filePath, std::vector<uint8_t>& binaryPackage) {
    bool fileFound = false;
    std::ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        char c;
        while (ifs.get(c)) {
            binaryPackage.push_back(c);
        }

        fileFound = true;
    }
    ifs.close();

    return fileFound;
}

bool
OtaUtils::loadPackageFile(const ara::core::String& packageFilePath, std::vector<char>& buffer) {
    std::ifstream file(packageFilePath.c_str(), std::ios::binary | std::ios::ate);
    std::uint32_t size = 0;

    if (file.is_open()) {
        size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(size);
        if (!file.read(buffer.data(), size)) {
            buffer.clear();
            mLogger.LogError() << "Read Package failed :" << packageFilePath.c_str();
            return false;
        }
        file.close();
    } else {
        mLogger.LogError() << "Open Package failed :" << packageFilePath.c_str();
        return false;
    }

    mLogger.LogInfo() << "Read Package successed :" << packageFilePath.c_str() << ", Size : " << buffer.size();
    return true;
}

bool
OtaUtils::parseVpmJson(const ara::core::String& vpmPath, stSessionInfo& sInfo) {
    bool ret = true;

    json_object *root = nullptr;
    json_object *swpkgs = nullptr;
    json_object *swpkg = nullptr;
    json_object *val = nullptr;

    root = json_object_from_file(vpmPath.c_str());

    if (root == nullptr) {
        mLogger.LogError() << "Open VehiclePackageManifest failed";
        return false;
    }

    swpkgs = json_object_object_get(root, "software-packages");
    if (swpkgs != nullptr) {
        int length = (int)json_object_array_length(swpkgs);
        if (length != 1) {
            mLogger.LogError() << "SW package count is not 1";
            json_object_put(root);
            return false;
        }

        for (int i = 0; i < length; i++) {
            swpkg = json_object_array_get_idx(swpkgs, i);

            val = json_object_object_get(swpkg, "package-name");
            if (val != nullptr) {
                sInfo.packageName =
                                json_object_get_string(val) == nullptr ?
                                    "" : static_cast<ara::core::String>(json_object_get_string(val));
            } else {
                mLogger.LogError() << "package-name parse error";
                ret = false;
                break;
            }

            val = json_object_object_get(swpkg, "software-cluster");
            if (val != nullptr) {
                sInfo.softwareCluster =
                                json_object_get_string(val) == nullptr ?
                                    "" : static_cast<ara::core::String>(json_object_get_string(val));
            } else {
                mLogger.LogError() << "software-cluster parse error";
                ret = false;
                break;
            }

            val = json_object_object_get(swpkg, "version");
            if (val != nullptr) {
                sInfo.version =
                                json_object_get_string(val) == nullptr ?
                                    "" : static_cast<ara::core::String>(json_object_get_string(val));
            } else {
                mLogger.LogError() << "version parse error";
                ret = false;
                break;
            }

            val = json_object_object_get(swpkg, "action-type");
            if (val != nullptr) {
                sInfo.actionType =
                                json_object_get_string(val) == nullptr ?
                                    "" : static_cast<ara::core::String>(json_object_get_string(val));
            } else {
                mLogger.LogError() << "action-type parse error";
                ret = false;
                break;
            }
        }
    } else {
        mLogger.LogError() << "software-packages parse error";
        ret = false;
    }

    json_object_put(root);
    return ret;
}

#ifdef UCM_TEST
bool
OtaUtils::isInstall() {
    ara::core::String path = "/opt/para/otapackage/install";
    std::ifstream ifs;

    ifs.open(path.c_str(), std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        return true;
    }
    return false;
}

bool
OtaUtils::isUpdate() {
    ara::core::String path = "/opt/para/otapackage/update";
    std::ifstream ifs;

    ifs.open(path.c_str(), std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        return true;
    }
    return false;
}
#endif

} /// namespace ota
} /// namespace eevp