#ifndef YE_CONFIG_PARSER_HPP
#define YE_CONFIG_PARSER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility> 

#include "SDL.h"
#include "glm/glm.hpp"
#include "nlohmann/json.hpp"

#include "lexer.hpp"

namespace YE {

    namespace rendering {
        struct SDL2_Config;
    }

    static class ConfigParser {
        static rendering::SDL2_Config ParseJsonConfigFile(const std::string& path);
        static rendering::SDL2_Config ParseYConfigFile(const std::string& path);
        public:
            ConfigParser() {}
            static rendering::SDL2_Config ParseConfigFile(const std::string& path);
    };

}

#endif