#include <Common.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <ara/log/logger.h>
#include <Log.hpp>

std::vector<std::string> split(std::string str, char Delimiter) {
    std::istringstream iss(str);
    std::string buffer;

    std::vector<std::string> result;

    while (getline(iss, buffer, Delimiter))
    {
        result.push_back(buffer);
    }

    char lastChar = str[str.size() - 1];
    if (lastChar == '\n')
    {
        result.push_back("");
    }

    return result;
}

static ara::log::Logger& logger()
{
    static ara::log::Logger& logger = ara::log::CreateLogger("SOA", "Default");
    return logger;
}

static std::string logHeader(const char *path, const uint32_t line, const char *func)
{
    std::stringstream ss;
    std::string path_str(path);
    int find = path_str.rfind('/') + 1;
    std::string file = path_str.substr(find, path_str.length() - find);

    ss << "[" << file << ":" << line << "|" << func << "] ";
    return ss.str();
}

soa::debug::Log &LOG_FATAL(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_FATAL, "FATAL", true);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}

soa::debug::Log &LOG_ERROR(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_ERROR, "ERROR", true);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}

soa::debug::Log &LOG_WARNING(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_WARNING, "WARN", true);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}

soa::debug::Log &LOG_INFO(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_INFO, "INFO", ture);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}

soa::debug::Log &LOG_DEBUG(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_DEBUG, "DEBUG", false);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}

soa::debug::Log &LOG_VERBOSE(const char *path, const uint32_t line, const char *func)
{
    static soa::debug::Log *log = new soa::debug::Log(soa::debug::eLOG_VERBOSE, "VERBOSE", false);
    std::string header = logHeader(path, line, func);
    log->setLogHeader(header);
    return *log;
}


namespace soa
{
namespace debug
{
Log::Log(soa::debug::LogLevel_e level, std::string label, bool enable)
{
    this->mEnableLog = enable;
    this->mLevel = level;
    this->mLabel = label;
    this->mStream.str("");
}

Log::~Log()
{

}

Log & Log::operator<<(bool value)
{
    this->mStream << ((value) ? "true" : "false");
    return *this;
}

Log & Log::operator<<(char value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(unsigned char value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(short value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(unsigned short value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(int value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(unsigned int value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(long value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(unsigned long value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(float value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(double value)
{
    this->mStream << value;
    return *this;
}

Log & Log::operator<<(const char *str)
{
    if (str)
    {
        int src, dst;
        char temp[1024];

        for (src = 0, dst = 0; str[src] != '\0'; src++)
        {
            if (str[src] == '\n')
            {
                temp[dst] = '\0';
                this->mStream << temp;
                dst = 0;
                this->flush();
            }
            else
            {
                temp[dst] = str[src];
                dst++;
                if (dst >= 1020)
                {
                    temp[dst] = '\0';
                    this->mStream << temp;
                    dst = 0;
                }
            }
        }

        if (dst > 0)
        {
            temp[dst] = '\0';
            this->mStream << temp;
        }
    }

    return *this;
}

Log & Log::operator<<(std::string str)
{
    std::vector<std::string> strVector = split(str, '\n');
    int length = strVector.size();
    int i = 0;
    for (std::string strItem: strVector) {
        if (strItem != "")
        {
            this->mStream << strItem;
        }

        i++;
        if (i < length) {
            this->flush();
        }
    }

    return *this;
}

void Log::setLogHeader(std::string header)
{
    this->mLogHeader = header;
}

void Log::flush()
{
    std::string string = this->mStream.str();

#if defined(USE_LOG_CONSOLE)
    if (this->mEnableLog)
    {
        switch (this->mLevel)
        {
        case soa::debug::eLOG_FATAL:
        case soa::debug::eLOG_ERROR:
        case soa::debug::eLOG_WARNING:
            std::cerr << "[" << this->mLabel << "] " << this->mLogHeader << string << '\n';
            break;
        case soa::debug::eLOG_INFO:
        case soa::debug::eLOG_DEBUG:
        case soa::debug::eLOG_VERBOSE:
        default:
            std::cout << "[" << this->mLabel << "] " << this->mLogHeader << string << '\n';
            break;
        }
    }
#endif

#if defined(USL_LOG_ARA_LOG)
        switch (this->mLevel)
        {
        case soa::debug::eLOG_FATAL:
            logger().LogFatal() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        case soa::debug::eLOG_ERROR:
            logger().LogError() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        case soa::debug::eLOG_WARNING:
            logger().LogWarn() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        case soa::debug::eLOG_INFO:
            logger().LogInfo() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        case soa::debug::eLOG_DEBUG:
            logger().LogDebug() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        case soa::debug::eLOG_VERBOSE:
            logger().LogVerbose() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        default:
            logger().LogDebug() << this->mLogHeader.c_str() << string.c_str() << '\n';
            break;
        }
#endif

    // Clear stream
    this->mStream.str("");
}

}
}