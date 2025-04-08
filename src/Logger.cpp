#include <Logger.hpp>

Logger* Logger::self = nullptr;

Logger::Logger()
{
    assert(self == nullptr);
    self = this;
}


void Logger::setLevel(int level)
{
    if (logLevel >= LogLevel::CRITICAL)
    {
        logLevel = level;
    }
}

void Logger::log(int level, const char* message, va_list args)
{
    if (level <= logLevel)
    {
       logPrefix(level);
       vprintf(message, args);
    }
}

void Logger::logPrefix(int level)
{
    switch (level)
    {
        case LogLevel::ERROR:
        {
            printf("\033[0;31m[ERROR]\033[0m ");
        } break;
        case LogLevel::CRITICAL:
        {
            printf("\033[0;31m[CRITICAL]\033[0m ");
        } break;
        case LogLevel::WARNING:
        {
            printf("\033[0;33m[WARNING]\033[0m ");
        } break;
        case LogLevel::INFO:
        {
            printf("\033[0;32m[INFO]\033[0m ");
        } break;
        case LogLevel::DEBUG:
        {
            printf("\033[0;34m[DEBUG]\033[0m ");
        } break;
        default: break;
    }
}
