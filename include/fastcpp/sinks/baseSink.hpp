#pragma once
#include "../core/message.hpp"
#include <memory>
#include <mutex>

namespace fastcpp{
    namespace logging{
        namespace sinks{
            class BaseSink{
                public:
                    virtual ~BaseSink() = default;
                    
                    void log(const LogMessage& msg){
                        std::lock_guard<std::mutex> lock(mutex_);
                        sink_it_(msg);
                    }
                    
                    void flush(){
                        std::lock_guard<std::mutex> lock(mutex_);
                        flush_();
                    }

                    void set_level(LogLevel level){
                        level_ = level;
                    }

                    LogLevel level() const {
                        return level_;
                    }

                    bool should_log(LogLevel msgLevel) const {
                        return msgLevel >= level;
                    }
                protected:
                    virtual void sink_it_(const LogMessage& msg) = 0;
                    virtual void flush_() {}

                    LogLevel level_ = LogLevel::TRACE;
                    mutable std::mutex mutex_;
            };

            using SinkPtr = std::shared_ptr<BaseSink>;
        }
    }
}