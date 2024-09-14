#ifndef __SOA_LOG_HPP__
#define __SOA_LOG_HPP__

#include <string>
#include <sstream>

namespace soa
{
namespace debug
{
typedef enum
{
    eLOG_FATAL = 0x01,
    eLOG_ERROR = 0x02,
    eLOG_WARNING = 0x04,
    eLOG_INFO = 0x08,
    eLOG_DEBUG = 0x10,
    eLOG_VERBOSE = 0x20,

    eLOG_ALL = 0xFF
} LogLevel_e;

class Log {
private:
    bool mEnableLog;
    soa::debug::LogLevel_e mLevel;
    std::string mLabel;
    std::string mLogHeader;
    std::stringstream mStream;
    void flush();

public:
    Log(soa::debug::LogLevel_e level, std::string label, bool enable = false);
    ~Log();
    Log & operator<<(bool value);
    Log & operator<<(char value);
    Log & operator<<(unsigned char value);
    Log & operator<<(short value);
    Log & operator<<(unsigned short value);
    Log & operator<<(int value);
    Log & operator<<(unsigned int value);
    Log & operator<<(long value);
    Log & operator<<(unsigned long value);
    Log & operator<<(float value);
    Log & operator<<(double value);
    Log & operator<<(const char *value);
    Log & operator<<(std::string value);
    void setLogHeader(std::string header);
};
}
}

extern soa::debug::Log &LOG_FATAL(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());
extern soa::debug::Log &LOG_ERROR(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());
extern soa::debug::Log &LOG_WARNING(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());
extern soa::debug::Log &LOG_INFO(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());
extern soa::debug::Log &LOG_DEBUG(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());
extern soa::debug::Log &LOG_VERBOSE(const char *path = __builtin_FILE(), const uint32_t line = __builtin_LINE(), const char *func = __builtin_FUNCTION());

#endif