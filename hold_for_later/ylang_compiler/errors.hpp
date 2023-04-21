#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>
#include <filesystem>
#include <algorithm>
#include <utility>

namespace ylang {

    enum class ErrorLevel {
        warning ,
        error ,
        fatal ,
    };

    struct Error {
        ErrorLevel level;
        std::string message;
        int line ,  col;
    };

    class ErrorHandler {
        std::queue<Error> m_Errors;

        public:
            ErrorHandler() {}
            ~ErrorHandler() {}
            
            bool FlushErrors();
            void SubmitError(Error error);
    };

}

#endif