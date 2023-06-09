#include "core/logger.hpp"

#include <iostream>

namespace YE {
namespace core {

    Logger* Logger::log_instance = nullptr;
    
    void Logger::ConsoleLog(Logger::LogLevel lvl , std::string msg) {

        switch (lvl) {
            case Logger::LogLevel::TRACE: console_logger->trace(msg);    break;
            case Logger::LogLevel::DEBUG: console_logger->debug(msg);    break;
            case Logger::LogLevel::INFO:  console_logger->info(msg);     break;
            case Logger::LogLevel::WARN:  console_logger->warn(msg);     break;
            case Logger::LogLevel::ERR:   console_logger->error(msg);    break;
            case Logger::LogLevel::FATAL: console_logger->critical(msg); break;
            default:
                throw std::runtime_error("Invalid Log Level Passed Into Console Log");
        }

    }

    void Logger::AppLog(Logger::LogLevel lvl , std::string msg) {

        switch (lvl) {            
            // case Logger::LogLevel::TRACE: app_logger->trace(msg);    break;
            // case Logger::LogLevel::DEBUG: app_logger->debug(msg);    break;
            // case Logger::LogLevel::INFO:  app_logger->info(msg);     break;
            // case Logger::LogLevel::WARN:  app_logger->warn(msg);     break;
            // case Logger::LogLevel::ERR:   app_logger->error(msg);    break;
            // case Logger::LogLevel::FATAL: app_logger->critical(msg); break;
            default:
                throw std::runtime_error("Application Log Unimplemented");
        }

    }

    void Logger::ErrorLog(Logger::LogLevel lvl , std::string msg) {

        switch (lvl) {
            case Logger::LogLevel::TRACE: error_logger->trace(msg);    break;
            case Logger::LogLevel::DEBUG: error_logger->debug(msg);    break;
            case Logger::LogLevel::INFO:  error_logger->info(msg);     break;
            case Logger::LogLevel::WARN:  error_logger->warn(msg);     break;
            case Logger::LogLevel::ERR:   error_logger->error(msg);    break;
            case Logger::LogLevel::FATAL: error_logger->critical(msg); break;
            default:
                throw std::runtime_error("Invalid Log Level Passed Into Error Log");
        }

    }
    
    Logger::~Logger() {

        if (log_instance == nullptr) 
            throw std::runtime_error("Logger Instance Null on Deletion | Logger Corrupt");

        std::cout << "deleting log\n";
        delete log_instance;
        log_instance = nullptr;

    }

    Logger* Logger::Get() {

        if (log_instance == nullptr) {

            log_instance = new Logger;

        }

        return log_instance;

    }

    void Logger::Init(std::string user_log_path) {

        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("%^[%l]| %c >%$ %v");
        console_sink->set_level(spdlog::level::debug);

        /*
            std::shared_ptr<spdlog::sinks::callback_sink_mt> callback_sink = std::make_shared<spdlog::sinks::callback_sink_mt>([](const spdlog::details::log_msg &msg) {

                ** send messages to be displayed in application??? ** 

            })
            callback_sink->set_pattern(*pattern*);
            callback_sink->set_level(idk);
        */

        std::shared_ptr<spdlog::sinks::stderr_color_sink_mt> error_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
        error_sink->set_pattern("[%^%l%$] %v < %@ >");
        error_sink->set_level(spdlog::level::warn);

        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(YE_LOG_FILE_DEST);
        file_sink->set_pattern("%^[%c][thread => %t][%l] %v%$");
        file_sink->set_level(spdlog::level::trace);

        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> user_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(user_log_path);
        user_file_sink->set_pattern("%^[%c][thread => %t][%l] %v%$");
        user_file_sink->set_level(spdlog::level::trace);

        std::vector<spdlog::sink_ptr> sinks1 { console_sink , file_sink };
        std::vector<spdlog::sink_ptr> sinks2 { error_sink   , file_sink };
        std::vector<spdlog::sink_ptr> sinks3 { file_sink };
        std::vector<spdlog::sink_ptr> sinks4 { user_file_sink };

        console_logger = std::make_shared<spdlog::logger>(YE_CONSOLE_LOGGER_NAME , sinks1.begin() , sinks1.end());
        /// \note application logger unimplemented right now, 
        // app_logger = std::make_shared<spdlog::logger>(YE_APP_LOGGER_NAME , sinks1.begin() , sinks1.end());
        error_logger     = std::make_shared<spdlog::logger>(YE_ERROR_LOGGER_NAME     , sinks2.begin() , sinks2.end());
        file_logger      = std::make_shared<spdlog::logger>(YE_FILE_LOGGER_NAME      , sinks3.begin() , sinks3.end());
        user_file_logger = std::make_shared<spdlog::logger>(YE_USER_FILE_LOGGER_NAME , sinks4.begin() , sinks4.end());

        console_logger->set_level(spdlog::level::trace);
        console_logger->flush_on(spdlog::level::trace);

        error_logger->set_level(spdlog::level::warn);
        error_logger->flush_on(spdlog::level::warn);

        file_logger->set_level(spdlog::level::trace);
        file_logger->flush_on(spdlog::level::trace);

        user_file_logger->set_level(spdlog::level::trace);
        user_file_logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(console_logger);
        spdlog::register_logger(error_logger);
        spdlog::register_logger(file_logger);
        spdlog::register_logger(user_file_logger);
    }

    void Logger::Shutdown() {
        spdlog::shutdown();
    }

    void Logger::Log(Logger::LogType type , Logger::LogLevel lvl , std::string msg) {

        std::unique_lock l{ log_mtx };

        switch (type) {
            case Logger::LogType::CONSOLE: ConsoleLog(lvl , msg); break;
            case Logger::LogType::APP:     AppLog(lvl , msg); break;
            case Logger::LogType::ERR:     ErrorLog(lvl , msg); break;
            default: throw std::runtime_error("Invalid Log Type Passed into Log");
        }

    }

}
}