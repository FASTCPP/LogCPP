#pragma once
#include <string_view>

namespace fastcpp {
    namespace logcpp {
        enum class LogLevel:int{
            TRACE = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            CRITICAL = 5,
            OFF = 6
        };

        constexpr std::string_view to_string(LogLevel level){
            switch(level){
                case LogLevel::TRACE: return "TRACE";
                case LogLevel::DEBUG: return "DEBUG";
                case LogLevel::INFO: return "INFO";
                case LogLevel::WARN: return "WARN";
                case LogLevel::ERROR: return "ERROR";
                case LogLevel::CRITICAL: return "CRITICAL";
                case LogLevel::OFF: return "OFF";
                default: return "UNKNOWN";
            }
        }
    }
}