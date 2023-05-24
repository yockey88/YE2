#ifndef YE_LOGGER_HPP
#define YE_LOGGER_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <memory>

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
        
        // default log sink for non-fatal warnings and errors as
        // well as general information and runtime traces
        std::shared_ptr<spdlog::logger> m_DefaultLogger;
        // default log sink for fatal errors and assertions
        // this sink is also used for non-fatal errors and warnings but is not recommended
        // as it is not as easy to read as the default logger
        std::shared_ptr<spdlog::logger> m_DefaultErrorLogger;
        bool m_Open;

        public:
            Logger() {}
            ~Logger() {}

            void Init();
            void Shutdown();
            inline const bool IsOpen() { return m_Open; } 
    };

}
}

#endif