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
// Eliminating in the near futre
// Will be using YLang as scripting language 
// This will extend to configurations
#include "nlohmann/json.hpp"

namespace YE {

    namespace rendering {
        struct SDL2_Config;
    }

    class ConfigParser {
        public:
            ConfigParser() {}
            rendering::SDL2_Config ParseConfigFile(const std::string& path);
    };

}

#endif