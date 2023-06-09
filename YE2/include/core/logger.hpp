#ifndef YE_LOGGER_HPP
#define YE_LOGGER_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <memory>
#include <string>
#include <mutex>

#include "log.hpp"

/**
 * Operator overloads for printing glm types
*/

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector) {

	return os << glm::to_string(vector);

}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix) {

	return os << glm::to_string(matrix);

}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion) {
	
    return os << glm::to_string(quaternion);

}

namespace YE {
namespace core {

    /** Logger Class
     *  -> class to handle opening log sinks/files
     *  -> Init() called upon Engine Object Creation before anything else and handles its own errors, crashing if it fails
     *  -> Shutdown() called upon Engine Object Destruction and handles its own errors, crashing if it fails (Not really necessary because the program has probably already crashed if this is going wrong)
     *  -> There is a method and member variable to check if the log is open, but this is for debug/development purposes only if the log is not open during the entirety of the Engine Object lifetime then there is a much larger problem at hand and this will only be a possible issue during development.
    */
    class Logger {
        
        public:
            enum class LogType {
                CONSOLE = 0 ,
                APP     = 1 ,
                ERR     = 2
            };
            
            enum class LogLevel {
                TRACE  = 0 , 
                DEBUG  = 1 ,
                INFO   = 2 , 
                WARN   = 3 , 
                ERR    = 4 , 
                FATAL  = 5
            };

        private:

            static Logger* log_instance;

            std::mutex log_mtx;

            std::shared_ptr<spdlog::logger> console_logger   = nullptr;
            std::shared_ptr<spdlog::logger> app_logger       = nullptr;
            std::shared_ptr<spdlog::logger> error_logger     = nullptr;
            std::shared_ptr<spdlog::logger> file_logger      = nullptr;
            std::shared_ptr<spdlog::logger> user_file_logger = nullptr;

            Logger() {}
            Logger(Logger&&) = delete;
            Logger(const Logger&) = delete;
            Logger& operator=(Logger&&) = delete;
            Logger& operator=(const Logger&) = delete;

            void ConsoleLog(Logger::LogLevel lvl , std::string msg);
            void AppLog(Logger::LogLevel lvl , std::string msg);
            void ErrorLog(Logger::LogLevel lvl , std::string msg);                                                          

        public:

            ~Logger();

            static Logger* Get();

            void Init(std::string log_path = "logs/ye.log");
            void Shutdown();

            /// \note this is here for greater control over logging, and eventually once logging needs grow I'll hav more sinks with explicit callbacks for different things
            void Log(Logger::LogType type , Logger::LogLevel lvl , std::string message);
    };

}
}

#endif