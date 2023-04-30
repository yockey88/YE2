#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "SDL.h"

static const std::vector<char> punctuators {
    '=' , ',' , ';' , ':' , '(' , ')' , '{' , '}' , '[' , ']' , '<' , '>' , '"'
};

static const std::vector<std::string> keywords {
    "Engine" , "Window" , "YE" , "PROJECTION" , "ORTHOGRAPHIC" , "SDL2"
};

static const std::vector<std::string> built_in_funcs {
    "SetEngineType" , "SetVersion" , "SetName" , "SetAuthor" , "SetDescription" ,
    "SetWindow" 
};

inline bool IsOperator(char c) { return std::find(punctuators.begin() , punctuators.end() , c) != punctuators.end(); }

inline bool IsKeyword(const std::string& str) { return std::find(keywords.begin() , keywords.end() , str) != keywords.end(); }
inline bool IsBuiltInFunc(const std::string& str) { return std::find(built_in_funcs.begin() , built_in_funcs.end() , str) != built_in_funcs.end(); }

inline bool IsAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'); }
inline bool IsDigit(char c) { return c >= '0' && c <= '9'; }
inline bool IsAlphaNumeric(char c) { return IsAlpha(c) || IsDigit(c); }

inline bool IsWhitespace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\n'; }

namespace YE {
namespace parsing {

    struct ParsedEngine {
        enum class Type {
            NO_RENDERING = 0 ,
            ORTHO = 1 , // 2D
            PROJ = 2    // 3D
        };

        int version_major = 0;
        int version_minor = 0;
        int version_patch = 0;

        std::string name = "";
        std::string author = "";
        std::string description = "";
    };

    struct ParsedWindow {
        glm::vec4 color{ 0.0f , 0.0f , 0.0f , 1.0f };
        glm::ivec2 size{ 800 , 600 };
        glm::ivec2 position{ SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED };
        std::string title = "";
        std::vector<std::string> flags{};
    };

    struct Token {
        enum class Type {
            none = 0 ,
            identifier = 1 ,
            number = 2 ,
            string = 3 ,
            keyword = 4 ,
            op = 5 ,
            punctuation = 6 ,
            func = 7 ,
            obj_param = 8
        };

        Type type = Type::none;
        std::string value = "";
    };

    static void(*SetEngineType)(int) = nullptr;
    static void(*SetVersion)(int , int , int) = nullptr;
    static void(*SetName)(const std::string&) = nullptr;
    static void(*SetAuthor)(const std::string&) = nullptr;
    static void(*SetDescription)(const std::string&) = nullptr;
    static void(*SetWindow)(const ParsedWindow& win) = nullptr;

    void PrintToken(Token token);

    std::vector<Token> LexTokens(const std::string& source);

}
}

#endif