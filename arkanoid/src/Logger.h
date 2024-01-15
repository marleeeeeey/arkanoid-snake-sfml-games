#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class Logger
{
public:
    static inline std::shared_ptr<spdlog::logger>& getInstance()
    {
        static std::shared_ptr<spdlog::logger> instance = spdlog::stdout_color_mt( "logger" );
        return instance;
    }
};

#define MY_LOG( severity, message ) Logger::getInstance()->severity( message )

#define MY_LOG_FMT( severity, fmt_string, ... ) \
    Logger::getInstance()->severity( fmt::format( fmt_string, __VA_ARGS__ ) )

#define MY_LOG_VAR( severity, var ) MY_LOG_FMT( severity, "{} = {}", #var, var )
