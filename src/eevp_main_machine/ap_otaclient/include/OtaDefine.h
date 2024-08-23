#ifndef OTA_DEFINE_H_
#define OTA_DEFINE_H_

//#define UCM_TEST

const char* const VEHICLE_PACKAGE_MANIFEST_JSON         = "vehicle_package_manifest.json";

// dirs
//const char* const OTA_PACKAGE_DIR                       = "/tmp/ota-update-packages";
const char* const OTA_PACKAGE_DIR                       = "/opt/para/OTAClient/var";

// action type
const char* const ACTION_TYPE_INSTALL                   = "install";
const char* const ACTION_TYPE_REMOVE                    = "remove";
const char* const ACTION_TYPE_UPDATE                    = "update";

#ifdef UCM_TEST
const char* const INSTALL_SOFTWARE_PACKAGE              = "DummyTest_Consumer_Install_1_0_0";
const char* const UPDATE_SOFTWARE_PACKAGE               = "DummyTest_Consumer_Update_1_0_1";
const char* const REMOVE_SOFTWARE_PACKAGE               = "DummyTest_Consumer_Remove_1_0_1";
const char* const SOFTWARE_CLUSTER                      = "DummyTest_Consumer";
const char* const OTA_TEST_PACKAGE_DIR                  = "/opt/para/otapackage";
#endif

#endif /// OTA_DEFINE_H_
