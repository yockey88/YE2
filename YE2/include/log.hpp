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

#define YE_CONSOLE_LOGGER_NAME "YE Console Log"
#define YE_APP_LOGGER_NAME "YE Application Log"
#define YE_ERROR_LOGGER_NAME "YE Error Log"

#define YE_FILE_LOGGER_NAME "YE Log File"
#define YE_LOG_FILE_DEST "logs/ye.log" 

#define YE_USER_FILE_LOGGER_NAME "YE User Log File"

#ifdef YE_DEBUG

#define YE_TRACE(...) \
    if (spdlog::get(YE_CONSOLE_LOGGER_NAME)) { \
        spdlog::get(YE_CONSOLE_LOGGER_NAME)->trace(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_DEBUG_LOG(...) \
    if (spdlog::get(YE_CONSOLE_LOGGER_NAME)) { \
        spdlog::get(YE_CONSOLE_LOGGER_NAME)->debug(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_INFO(...) \
    if (spdlog::get(YE_CONSOLE_LOGGER_NAME)) { \
        spdlog::get(YE_CONSOLE_LOGGER_NAME)->info(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_WARN(...) \
    if (spdlog::get(YE_ERROR_LOGGER_NAME)) { \
        spdlog::get(YE_ERROR_LOGGER_NAME)->warn(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_ERROR(...) \
    if (spdlog::get(YE_ERROR_LOGGER_NAME)) { \
        spdlog::get(YE_ERROR_LOGGER_NAME)->error(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_FATAL(...) \
    if (spdlog::get(YE_ERROR_LOGGER_NAME)) { \
        spdlog::get(YE_ERROR_LOGGER_NAME)->critical(__VA_ARGS__); \
    } \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_FILE_TRACE(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_FILE_DEBUG_LOG(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->debug(__VA_ARGS__); \
    }

#define YE_FILE_INFO(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->info(__VA_ARGS__); \
    }

#define YE_FILE_WARN(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->warn(__VA_ARGS__); \
    }

#define YE_FILE_ERROR(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->error(__VA_ARGS__); \
    }

#define YE_FILE_FATAL(...) \
    if (spdlog::get(YE_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_FILE_LOGGER_NAME)->critical(__VA_ARGS__); \
    }

#define YE_ASSERT(x , ...) \
    if ((x)) {} else { \
        YE_FILE_FATAL("Assertion Failure in File {} : {} | <{}> " , __FILE__ , __FUNCTION__ , __LINE__); \
        YE_FILE_FATAL("Fatal Error <{}>" , __VA_ARGS__); \
        YE_FATAL("Assertion Failure in File {} : {} | <{}> " , __FILE__ , __FUNCTION__ , __LINE__); \
        YE_FATAL("Fatal Error <{}>" , __VA_ARGS__); \
        YE_BREAKPOINT; \
    }

#endif  

#define YE_USER_FILE(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_USER_FILE_TRACE(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->trace(__VA_ARGS__); \
    }

#define YE_USER_FILE_DEBUG_LOG(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->debug(__VA_ARGS__); \
    }

#define YE_USER_FILE_INFO(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->info(__VA_ARGS__); \
    }

#define YE_USER_FILE_WARN(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->warn(__VA_ARGS__); \
    }

#define YE_USER_FILE_ERROR(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->error(__VA_ARGS__); \
    }

#define YE_USER_FILE_FATAL(...) \
    if (spdlog::get(YE_USER_FILE_LOGGER_NAME)) { \
        spdlog::get(YE_USER_FILE_LOGGER_NAME)->critical(__VA_ARGS__); \
    }

#ifdef YE_RELEASE

#define YE_INFO(...) (void)0
#define YE_TRACE(...) (void)0
#define YE_DEBUG_LOG(...) (void)0
#define YE_WARN(...) (void)0
#define YE_ERROR(...) (void)0
#define YE_FATAL(...) (void)0
#define YE_ASSERT(x , ...) (void)0

#define YE_FILE0_TRACE(...) (void)0
#define YE_FILE0_DEBUG_LOG(...) (void)0
#define YE_FILE0_INFO(...) (void)0
#define YE_FILE0_WARN(...) (void)0
#define YE_FILE0_ERROR(...) (void)0
#define YE_FILE0_FATAL(...) (void)0

#endif

#endif