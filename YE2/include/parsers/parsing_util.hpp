#ifndef YE_PARSING_UTIL_HPP
#define YE_PARSING_UTIL_HPP

#include <stack>
#include <queue>
#include <string>

/**
 * Data to check if identifiers are keywords, built-in macros and function, operators, etc.
 * Documentation in progress for a tutorial on how to write a YE config file/the ins and outs of YScript and eventually YLang implementations.
*/

static const std::vector<char> punctuators {
    '=' , ',' , ';' , ':' , '(' , ')' , '{' , '}' , '[' , ']' , '<' , '>' , '"' , '/' , '$'
};

static const std::vector<std::string> keywords {
    "Engine" , "Window" , "Scene" , "Entity" ,
    "YE" , "PERSPECTIVE" , "ORTHOGRAPHIC" , "NO_RENDER" , "SDL2"
};

static const std::vector<std::string> built_in_funcs {
    "SetEngineType" , "SetVersion" , "SetName" , "SetAuthor" , "SetDescription" ,
    "SetActiveWindow" , "SetActiveScene"
};

/**
 * Inline utility functions to check character types.
*/

inline bool IsOperator(char c) { return std::find(punctuators.begin() , punctuators.end() , c) != punctuators.end(); }

inline bool IsKeyword(const std::string& str) { return std::find(keywords.begin() , keywords.end() , str) != keywords.end(); }
inline bool IsBuiltInFunc(const std::string& str) { return std::find(built_in_funcs.begin() , built_in_funcs.end() , str) != built_in_funcs.end(); }

inline bool IsAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'); }
inline bool IsDigit(char c) { return c >= '0' && c <= '9'; }
inline bool IsAlphaNumeric(char c) { return IsAlpha(c) || IsDigit(c); }

inline bool IsWhitespace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\n'; }

namespace YE {
namespace parsing {

    // forward declarations of structs and classes
    struct LexerState;
    struct ParseState;

    // // Beginning of maybe might use stuff and maybe might not 
    // struct ParsedEngine {
    //     enum class Type { NO_RENDERING = 0 , ORTHO = 1 , PERSPECTIVE = 2 };

    //     int version_major = 0;
    //     int version_minor = 0;
    //     int version_patch = 0;

    //     std::string name = "";
    //     std::string author = "";
    //     std::string description = "";
    // };

    // struct ParsedWindow {
    //     enum class Type { SDL2 = 0 } window_type = Type::SDL2;
    //     glm::vec4 color{ 0.0f , 0.0f , 0.0f , 1.0f };
    //     glm::ivec2 size{ 800 , 600 };
    //     glm::ivec2 position{ SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED };
    //     std::vector<Uint32> flags{ SDL_WINDOW_OPENGL , SDL_WINDOW_RESIZABLE };
    //     std::string title = "";
    //     std::string parsed_name = "";
    // };
    // // End of maybe might use objects

    // Tokens and errors
    struct Token {
        enum class Type {
            none = 0 ,
            identifier = 1 ,
            number = 2 ,
            string = 3 ,
            keyword = 4 ,
            op = 5 ,
            func = 6 ,
            obj_param = 7 ,
            obj_param_value = 8
        };

        Type type = Type::none;
        int line = 0 , column = 0;
        std::string value = "";
    };

    struct Error {
        enum class Level {
            none = 0 ,
            warning = 1 ,
            fatal = 2
        };

        Level level = Level::none;
        int line = 0 , column = 0;
        std::string message = "";

        Error(int line , int col , const std::string& msg , Level type) : line(line) , column(col) , message(msg) , level(Level::none) {}
    };

    // Only made this a class cause purists and their dogma, it really doesnt deserve to be a 'class'
    // Maybe as engine grows and more error handling is needed it will be more justified
    class ErrorHandler {
        public:
            bool nonfatal_error_ecnountered = false;
            std::queue<Error> errors{};
            void HandleError(Error error);
    };

    // Lexer and Parser state functions
    typedef void(*YE_LexerFunction)(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    typedef void(*YE_ParseFunction)(const std::string& source , ParseState& state , ErrorHandler* error_handler);

    // Lexer and Parser state that gets passed around to the different states to hold all data needed
    // Also exists only to reduce the amount of parameters needed to pass around
    struct LexerState {
        bool valid = false;
        int index = 0;
        int line = 1 , column = 0;
        std::string current_token = "";
        std::vector<Token> tokens{};
        std::stack<YE_LexerFunction> stack{};
    };

    struct ParseState {
        bool valid = false;
        int index = 0;
        std::vector<Token> tokens{};
        std::stack<YE_ParseFunction> stack{};
    };


    // Lexer and Parser state functions
    void YE_LexError(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexSOF(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexMinorComment(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexMajorComment(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexEOF(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexWhitespace(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexIdentifier(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexNumber(const std::string& source , LexerState& state , ErrorHandler* error_handler);
    void YE_LexOp(const std::string& source , LexerState& state , ErrorHandler* error_handler);

    void YE_ParseError(const std::string& source , ParseState& state , ErrorHandler* error_handler);
    void YE_ParseSOF(const std::string& source , ParseState& state , ErrorHandler* error_handler);
    void YE_ParseMacro(const std::string& source , ParseState& state , ErrorHandler* error_handler);
    void YE_ParseYObject(const std::string& source , ParseState& state , ErrorHandler* error_handler);

}
}

#endif