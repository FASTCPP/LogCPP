#pragma once
#include "baseSink.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace fastcpp{
    namespace logging{
        namespace sinks{
            class ConsoleSink : public BaseSink{
                public:
                    ConsoleSink(bool useColors = true) : use_colors_(useColors) {}
                
                protected:
                    void sink_it_(const LogMessage& msg) override {
                        auto time_t = std::chrono::system_clock::to_time_t(msg.timestamp);
                        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(msg.timestamp.time_since_epoch()) % 1000;
                        std:ostringstream oss;
                        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
                        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

                        if(use_colors_){
                            std::cout << get_color(msg.level);
                        }
                        
                        std::cout << "[" << oss.str() << "] " << "[" << to_string(msg.level) << "] " << "[" << msg.logger_name << "] " << msg.message;

                        if(!msg.fields.empty()){
                            std::cout << " {";
                            bool first = true;
                            for(const auto& [key, value] : msg.fields){
                                if(!first) std::cout << ", ";
                                std::cout << key << "=" << value;
                                first = false;
                            }
                            std::cout << "}";
                        }

                        if(use_colors_){
                            std::cout << "\033[0m"; // Color Reset
                        }

                        std::cout << "\n";
                    }

                    void flush_() override {
                        std::cout.flush();
                    }
                private:
                    bool use_colors_;
                    const char* get_color(LogLevel level){
                        switch(level){
                            case LogLevel::TRACE: return "\033[37m";    // White
                            case LogLevel::DEBUG: return "\033[36m";    // Cyan
                            case LogLevel::INFO: return "\033[32m";     // Green
                            case LogLevel::WARN: return "\033[33m";     // Yellow
                            case LogLevel::ERROR: return "\033[31m";    // Red
                            case LogLevel::CRITICAL: return "\033[35m"; // Magenta
                            default: return "\033[0m";
                        }
                    }
            }
        }
    }
}