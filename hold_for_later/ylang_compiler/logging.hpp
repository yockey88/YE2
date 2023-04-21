#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "spdlog/spdlog.h"

namespace ylang {

    class Logger {
        std::shared_ptr<spdlog::logger> m_Logger;

        public:
            Logger();
            ~Logger() {}

            void Log(const std::string& msg) {}
    };

}

#endif