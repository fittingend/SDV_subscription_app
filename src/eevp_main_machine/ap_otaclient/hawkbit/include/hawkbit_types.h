#ifndef HAWKBIT_TYPES_H_
#define HAWKBIT_TYPES_H_

#include <queue>
#include <boost/uuid/detail/sha1.hpp>

#include "provider_common_types.h"

namespace eevp
{
namespace ucm
{
namespace ota
{
namespace hawkbitClient
{

constexpr char HAWKBIT_USERAGENT[] = "hawkbit-c-agent/1.0";
constexpr std::chrono::seconds DEFAULT_SLEEP_TIME_SEC(60 * 60);  // 1 hour

/**
 * \brief Struct containing the artifact specification
 */
struct HawkbitArtifactSpecification
{
    std::string downloadURL;  // download URL of software file
    std::string feedbackURL;  // URL status feedback should be sent to
    FileInformation fileInformation;  // file information, e.g. name, size, checksum
};

/**
 * \brief Struct containing the chunk specification
 */
struct HawkbitChunkSpecification
{
    std::string name;  // name of software
    std::string version;  // software version
    std::string part;  // module category
    std::queue<std::unique_ptr<HawkbitArtifactSpecification>> artifactsQueue;
};

}  // namespace hawkbitClient
}  // namespace ota
}  // namespace ucm
}  // namespace eevp

#endif  // HAWKBIT_TYPES_H_
