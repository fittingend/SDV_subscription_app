#ifndef JSON_HELPER_H_
#define JSON_HELPER_H_

#include <string>
#include <unordered_map>

#include "apd/rest/ogm/base.h"
#include "apd/rest/ogm/node.h"
#include "apd/rest/ogm/field.h"
#include "apd/rest/ogm/object.h"
#include "apd/rest/ogm/array.h"
#include "apd/rest/ogm/string.h"
#include "apd/rest/ogm/int.h"
#include "apd/rest/ogm/real.h"
#include "apd/rest/ogm/visit.h"
#include "apd/rest/ogm/copy.h"

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

/**
 * \brief Extraction function to get a string from a given path of a given json object
 * \param root root object of the json
 * \param path path to the json field where the string shall be read out
 * \return pointer to string or nullptr if path was not found in json
 */
apd::rest::Pointer<apd::rest::ogm::String> JsonGetString(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const std::string& path);

/**
 * \brief Extraction function to get a int from a given path of a given json object
 * \param root root object of the json
 * \param path path to the json field where the string shall be read out
 * \return int value. -1 if path was not found in json
 */
int64_t JsonGetInt(apd::rest::Pointer<apd::rest::ogm::Object>& root, const char* path);

/**
 * \brief Extraction function to get an array from a given path of a given json object
 * \param root root object of the json
 * \param path path to the json field where the string shall be read out
 * \return pointer to the array object or nullptr if path was not found in json
 */
apd::rest::Pointer<apd::rest::ogm::Array> JsonGetArray(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const char* path);

/**
 * \brief Checking function to check for the presence of a key in a json.
 * \param root root object of the json
 * \param key key to check for
 * \return true if key is present, false if not
 */
bool JsonContains(apd::rest::Pointer<apd::rest::ogm::Object>& root, const char* key);

/**
 * \brief Extraction function to get an object of an array at a specific index.
 * \param array array object
 * \param index index from which the object shall be read out
 * \return pointer to object or nullptr if index is out of bounds
 */
apd::rest::Pointer<apd::rest::ogm::Object> JsonArrayGetElement(apd::rest::Pointer<apd::rest::ogm::Array>& array,
    uint index);

/**
 * \brief Extraction function to get the sleeping time from a json object
 * \param root root object of the json
 * \param defaultTimeSec default time if no sleep time has been found in given json
 * \return sleeping time
 */
std::chrono::seconds JsonGetSleeptime(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const std::chrono::seconds& defaultTimeSec);

/**
 * \brief Function to build hawkbit feedback json
 * \param obj_node root object of the json
 * \param id path to the json field where the string shall be read out
 * \param detail path to the json field where the string shall be read out
 * \param finished path to the json field where the string shall be read out
 * \param execution path to the json field where the string shall be read out
 * \param progress path to the json field where the string shall be read out
 */
void JsonBuildStatus(apd::rest::Pointer<apd::rest::ogm::Object>& obj_node,
    const std::string& id,
    const std::string& detail,
    const std::string& finished,
    const std::string& execution,
    const std::unordered_map<std::string, std::string>& data,
    int progress);

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp

#endif  // JSON_HELPER_H_
