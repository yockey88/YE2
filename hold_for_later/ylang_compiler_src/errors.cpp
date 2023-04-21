#include "errors.hpp"

namespace ylang {

    bool ErrorHandler::FlushErrors() {
        if (m_Errors.empty()) return true;

        Error error;
        while (!m_Errors.empty()) {
            error = m_Errors.front();

            switch (error.level) {
                case ErrorLevel::warning: std::cout << "< Warning | "; break;
                case ErrorLevel::error: std::cout << "< Error | "; break;
                case ErrorLevel::fatal: std::cout << "< Fatal Error | "; break;
                default: std::cout << "< Unknown Error | "; break;
            }

            std::cerr << error.message << " | (" << error.line << " : " << error.col << ") >" << std::endl;
            m_Errors.pop();
            
            switch (error.level) {
                case ErrorLevel::warning: /* Handle Warning */ break;
                case ErrorLevel::error: /* Handle Error */ break;
                case ErrorLevel::fatal: break;
                default: break; 
            }
        }

        // TODO :==> Ret false for fatal errors and handle those mfs
        switch (error.level) {
            case ErrorLevel::warning: /* Handle Warning */ return true;
            case ErrorLevel::error: /* Handle Error */ return true;
            case ErrorLevel::fatal: return false;
            default: return true; 
        }
    }

    void ErrorHandler::SubmitError(Error error) {
        m_Errors.push(error);
    }

}