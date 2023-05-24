#ifndef YE_LOG_HPP
#define YE_LOG_HPP

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/ostr.h"

#ifdef YE_PLATFORM_WINDOWS
    #define YE_BREAKPOINT __debugbreak()
// #elif YE_PLATFORM_LINUX
//     #define YE_BREAKPOINT __builtin_debugtrap()
// #else
//     #define YE_BREAKPOINT __builtin_trap()
#endif

#define YE_MAIN_LOGGER_NAME "YE_DEFAULT_SINK"
#define YE_MAIN_FILE_NAME "YE_DEFAULT_FILE"
#define YE_MAIN_FILE_DEST "logs/ye.log"

#define YE_MAIN_ERROR_LOGGER_NAME "YE_DEFAULT_ERROR_SINK"
#define YE_MAIN_ERROR_FILE_NAME "YE_DEFAULT_ERROR_FILE"
#define YE_MAIN_ERROR_FILE_DEST "logs/ye_error.log" 

#ifdef YE_DEBUG

#define YE_INFO(...) \
    if (spdlog::get(YE_MAIN_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_LOGGER_NAME)->info(__VA_ARGS__); \
    }

#define YE_TRACE(...) \
    if (spdlog::get(YE_MAIN_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_DEBUG_LOG(...) \
    if (spdlog::get(YE_MAIN_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_LOGGER_NAME)->debug(__VA_ARGS__); \
    }

#define YE_WARN(...) \
    if (spdlog::get(YE_MAIN_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_LOGGER_NAME)->warn(__VA_ARGS__); \
    }

#define YE_ERROR(...) \
    if (spdlog::get(YE_MAIN_ERROR_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_ERROR_LOGGER_NAME)->error(__VA_ARGS__); \
    }

#define YE_FATAL(...) \
    if (spdlog::get(YE_MAIN_ERROR_LOGGER_NAME)) { \
        spdlog::get(YE_MAIN_ERROR_LOGGER_NAME)->critical(__VA_ARGS__); \
    }

#define YE_ASSERT(x , ...) \
    if ((x)) {} else { \
        YE_FATAL("Assertion Failure in File {} : {} | <{}> " , __FILE__ , __FUNCTION__ , __LINE__); \
        YE_FATAL("Fatal Error <{}>" , __VA_ARGS__); \
        YE_BREAKPOINT; \
    }

#endif
#ifdef YE_RELEASE

#define YE_INFO(...) (void)0
#define YE_TRACE(...) (void)0
#define YE_DEBUG_LOG(...) (void)0
#define YE_WARN(...) (void)0
#define YE_ERROR(...) (void)0
#define YE_FATAL(...) (void)0
#define YE_ASSERT(x , ...) (void)0

#endif

#endif