#pragma once

#include <cassert>
#include <cstdint>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

enum LogLevel
{
    ERROR = 0,
    CRITICAL,
    WARNING,
    INFO,
    DEBUG
};

class Logger
{
    public:
        Logger();
    
        static Logger* instance(void)
        {
            assert(self != nullptr);
            return self;
        }

        void setLevel(int level);
        void log(int level, const char* message, va_list args);

    private:
        static Logger* self;
        int logLevel = LogLevel::DEBUG;
    
        void logPrefix(int level);
};

static inline void SET_LEVEL(int level)
{
    Logger::instance()->setLevel(level);
}

static inline void LOG_ERROR(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Logger::instance()->log(LogLevel::ERROR, message, args);
}

static inline void LOG_CRITICAL(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Logger::instance()->log(LogLevel::CRITICAL, message, args);
}

static inline void LOG_WARNING(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Logger::instance()->log(LogLevel::WARNING, message, args);
}

static inline void LOG_INFO(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Logger::instance()->log(LogLevel::INFO, message, args);
    va_end(args);
}

static inline void LOG_DEBUG(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Logger::instance()->log(LogLevel::DEBUG, message, args);
    va_end(args);
}
