#include "apd/rest/serialize/serialize.h"

#include "json_helper.h"

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

using namespace apd::rest;

static apd::rest::Pointer<apd::rest::ogm::Field> JsonExtractValue(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const std::string& path)
{
    std::string copyPath(path);
    std::string delimiter = ".";
    std::size_t pos = 0;
    Pointer<ogm::Object> value = Copy(root);
    Pointer<ogm::Field> field = NULL;

    auto newValue = value->Find(copyPath.substr(0, pos));

    while ((pos = copyPath.find(delimiter)) != std::string::npos) {
        newValue = value->Find(copyPath.substr(0, pos));

        if (newValue == value->GetFields().end()) {
            return nullptr;
        }
        copyPath.erase(0, pos + delimiter.length());

        ogm::Visit(&((*newValue).GetValue()),
            [&value](const ogm::Object* object_with_in_field) { value = Copy(object_with_in_field); });
    }

    newValue = value->Find(copyPath);

    if (newValue == value->GetFields().end()) {
        return nullptr;
    }

    return Copy(&(*newValue));
}

apd::rest::Pointer<apd::rest::ogm::String> JsonGetString(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const std::string& path)
{
    Pointer<ogm::Field> field = JsonExtractValue(root, path);
    Pointer<ogm::String> content;

    if (field == nullptr) {
        return nullptr;
    }

    ogm::Visit(&field->GetValue(), [&content](ogm::String* str) { content = Copy(str); });
    return Copy(content);
}

int64_t JsonGetInt(apd::rest::Pointer<apd::rest::ogm::Object>& root, const char* path)
{
    Pointer<ogm::Field> field = JsonExtractValue(root, path);
    int64_t value = -1;
    ogm::Visit(&field->GetValue(), [&value](apd::rest::ogm::Int* integer) { value = integer->GetValue(); });

    return value;
}

apd::rest::Pointer<apd::rest::ogm::Array> JsonGetArray(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const char* path)
{
    Pointer<ogm::Field> field = JsonExtractValue(root, path);
    Pointer<ogm::Array> array = nullptr;
    ogm::Visit(&field->GetValue(), [&array](ogm::Array* arrayField) { array = Copy(arrayField); });

    return array;
}

bool JsonContains(apd::rest::Pointer<apd::rest::ogm::Object>& root, const char* key)
{
    Pointer<ogm::Field> field = JsonExtractValue(root, key);

    if (field == nullptr)
        return false;

    return true;
}

apd::rest::Pointer<apd::rest::ogm::Object> JsonArrayGetElement(apd::rest::Pointer<apd::rest::ogm::Array>& array,
    uint index)
{
    Pointer<ogm::Object> content = nullptr;

    if (index >= array->GetSize())
        return nullptr;

    ogm::Visit(&array->GetValue(index), [&content](ogm::Object* objectInField) { content = Copy(objectInField); });

    return content;
}

/// @brief Get polling sleep time from hawkBit JSON response.
std::chrono::seconds JsonGetSleeptime(apd::rest::Pointer<apd::rest::ogm::Object>& root,
    const std::chrono::seconds& defaultTimeSec)
{
    // TODO define all consts in unique file
    const char* valueTime = JsonGetString(root, "config.polling.sleep")->GetValue().c_str();

    if (valueTime != nullptr) {
        struct tm time;
        strptime(valueTime, "%T", &time);
        std::chrono::seconds pollSleepTime(time.tm_sec + (time.tm_min * 60) + (time.tm_hour * 60 * 60));
        return pollSleepTime;
    }
    return defaultTimeSec;
}

/// Build JSON status request.
/// have a look at :
/// https://www.eclipse.org/hawkbit/rest-api/rootcontroller-api-guide/#_post_tenant_controller_v1_controllerid_deploymentbase_actionid_feedback
void JsonBuildStatus(apd::rest::Pointer<apd::rest::ogm::Object>& obj_node,
    const std::string& id,
    const std::string& detail,
    const std::string& finished,
    const std::string& execution,
    const std::unordered_map<std::string, std::string>& data,
    int progress)
{
    // TODO Check if file was created
    // TODO define all using in unique file
    time_t currentTime;
    struct tm timeInfo;
    // TODO Check if 16 enough
    char timeString[16];

    Pointer<ogm::Object> statusJson = ogm::Object::Make();
    Pointer<ogm::Object> resultJson = ogm::Object::Make();
    Pointer<ogm::Object> progressJson = ogm::Object::Make();
    Pointer<ogm::Object> dataJson = ogm::Object::Make();
    Pointer<ogm::Array> detailsJson = ogm::Array::Make();

    // Get current time in UTC
    time(&currentTime);
    gmtime_r(&currentTime, &timeInfo);
    strftime(timeString, sizeof(timeString), "%Y%m%dT%H%M%S", &timeInfo);
    if (!id.empty())
        obj_node->Insert(ogm::Field::Make("id", ogm::String::Make(id)));

    obj_node->Insert(ogm::Field::Make("time", ogm::String::Make(String(timeString))));

    if (execution.compare("proceeding") == 0) {
        progressJson->Insert(ogm::Field::Make("of", ogm::Int::Make(3)));
        progressJson->Insert(ogm::Field::Make("cnt", ogm::Int::Make(progress)));
        resultJson->Insert(ogm::Field::Make("progress", std::move(progressJson)));
    }

    resultJson->Insert(ogm::Field::Make("finished", ogm::String::Make(finished)));

    statusJson->Insert(ogm::Field::Make("result", std::move(resultJson)));
    statusJson->Insert(ogm::Field::Make("execution", ogm::String::Make(execution)));

    if (!detail.empty()) {

        detailsJson->Append(ogm::String::Make(detail));
        statusJson->Insert(ogm::Field::Make("details", std::move(detailsJson)));
    }

    obj_node->Insert(ogm::Field::Make("status", std::move(statusJson)));

    if (!data.empty()) {

        for (const auto& pair : data)
            dataJson->Insert(ogm::Field::Make(pair.first, ogm::String::Make(pair.second)));

        obj_node->Insert(ogm::Field::Make("data", std::move(dataJson)));
    }
}

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp
