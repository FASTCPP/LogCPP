#pragma once
#include "level.hpp"
#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>

namespace fastcpp{
    namespace logging{
        struct LogMessage{
            std::chrono::system_clock::time_point timestamp;
            LogLevel level;
            std::string logger_name;
            std::string message;
            std::thread::id thread_id;
            const char* file;
            int line;
            const char* function;
            std::unordered_map<std::string, std::string> fields;

            LogMessage(LogLevel logLevel, const std::string& name, const std::string& msg)
            : timestamp(std::chrono::system_clock::now()),
            level(logLevel),
            logger_name(name),
            message(msg),
            thread_id(std::this_thread::get_id()),
            file(nullptr),
            line(0),
            function(nullptr) {}
        };
    }
}