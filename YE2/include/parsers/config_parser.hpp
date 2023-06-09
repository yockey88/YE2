#ifndef YE_CONFIG_PARSER_HPP
#define YE_CONFIG_PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility> 
#include <map>
#include <locale>

#include "SDL.h"
#include "glm/glm.hpp"
#include "nlohmann/json.hpp"
#include "glm/glm.hpp"

#include "parsers/parsing_util.hpp"

/**
 * Forward declarations of structs and classes.
*/
namespace YE {
namespace rendering {

    struct SDL2_Config;

}
namespace core {

    struct EngineConfiguration;

}
namespace parsing {

    /** Configuration Parser Class
     *   -> class for parsing specifically configuration files for YE
     *   -> Is only instatiated during during Engine Object Initialization and searches for 
     *          a yobj or json file in the runtime config directory. (pwd/config/)
     *          all other files are ignored. If the configuration parser can't find a config file
     *          then it will throw an error and exit the program, ending Engine Initialization and cleaning up
    */
    class ConfigParser {
        // utility function to print in debug builds
        void PrintToken(Token token);
        // Base Lexer function that takes a string and returns a vector of tokens
        // Creates a parsing::lexerState object and a parsing::ErrorHandler object and uses
        //      a stack of functions pointers to call the appropriate function to lex the next token 
        std::vector<Token> LexTokens(const std::string& source);

        // Stupid awful json files HUH-POO!!! (that was me spitting)
        void ParseJsonConfigFile(const std::string& path , core::EngineConfiguration *& config);
        // YObject files are much better than json files (They dont work yet)
        void ParseYConfigFile(const std::string& path , core::EngineConfiguration *& config);
        public:
            ConfigParser() {}
            // Main function to parse a config file
            // Detects the file type and calls the appropriate function to parse the file
            void ParseConfigFile(const std::string& path , core::EngineConfiguration* config);
    };

}
}

#endif