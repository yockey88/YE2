#include "core/logger.hpp"

// #include "spdlog/spdlog.h"

namespace YE {
namespace core {

    void Logger::Init() {

        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> default_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        default_sink->set_pattern("[%^%l%$] %v < %c >");
        default_sink->set_level(spdlog::level::trace);

        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> error_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        error_sink->set_pattern("[%^%l%$] %v < %@ >");
        error_sink->set_level(spdlog::level::warn);

        std::vector<spdlog::sink_ptr> sinks1 { default_sink };
        std::vector<spdlog::sink_ptr> sinks2 { error_sink };

        m_DefaultLogger = std::make_shared<spdlog::logger>(YE_MAIN_LOGGER_NAME , sinks1.begin() , sinks1.end());
        m_DefaultErrorLogger = std::make_shared<spdlog::logger>(YE_MAIN_ERROR_LOGGER_NAME , sinks2.begin() , sinks2.end());

        m_DefaultLogger->set_level(spdlog::level::trace);
        m_DefaultErrorLogger->set_level(spdlog::level::warn);

        m_DefaultLogger->flush_on(spdlog::level::trace);
        m_DefaultErrorLogger->flush_on(spdlog::level::warn);

        spdlog::register_logger(m_DefaultLogger);
        spdlog::register_logger(m_DefaultErrorLogger);

        m_Open = true;
    }

    void Logger::Shutdown() {
        if (m_Open) {
            spdlog::shutdown();
            m_Open = false;
        }
    }

}
}