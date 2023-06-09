#ifndef YE_ERRORS_HPP
#define YE_ERRORS_HPP

#include <string>
#include <vector>
#include <queue>

namespace YE {
namespace core {

    struct Error {

        enum class Level {

            DEBUG_WARNING = 0 ,
            WARNING = 1 , 
            FATAL = 2

        } ErrorLevel = Level::DEBUG_WARNING;

        std::string msg;

    };

    static class ErrorHandler {

        std::queue<Error> errors{};

        public:

    };

}
}

#endif