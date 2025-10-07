#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace vi
{
class Log
{
public:
    static void init();
    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

private:
    inline static std::shared_ptr<spdlog::logger> s_coreLogger{};
    inline static std::shared_ptr<spdlog::logger> s_clientLogger{};
};
}

// Core log macros
#define VI_CORE_TRACE(...)  ::vi::Log::getCoreLogger()->trace(__VA_ARGS__)
#define VI_CORE_INFO(...)   ::vi::Log::getCoreLogger()->info(__VA_ARGS__)
#define VI_CORE_WARN(...)   ::vi::Log::getCoreLogger()->warn(__VA_ARGS__)
#define VI_CORE_ERROR(...)  ::vi::Log::getCoreLogger()->error(__VA_ARGS__)
#define VI_CORE_FATAL(...)  ::vi::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define VI_TRACE(...)       ::vi::Log::getClientLogger()->trace(__VA_ARGS__)
#define VI_INFO(...)        ::vi::Log::getClientLogger()->info(__VA_ARGS__)
#define VI_WARN(...)        ::vi::Log::getClientLogger()->warn(__VA_ARGS__)
#define VI_ERROR(...)       ::vi::Log::getClientLogger()->error(__VA_ARGS__)
#define VI_FATAL(...)       ::vi::Log::getClientLogger()->fatal(__VA_ARGS__)
