#include "log.hpp"
#include "parsers/parsing_util.hpp"

namespace YE {
namespace parsing {

    void ErrorHandler::HandleError(Error error) {

        switch (error.level) {
            case Error::Level::warning: {
                YE_WARN(error.message);
                nonfatal_error_ecnountered = true;
            } break;
            case Error::Level::fatal: YE_FATAL(error.message); break;
            case Error::Level::none: YE_FATAL("Error Handler ecnountered null error level"); break;
            default: YE_FATAL("Unknown error level"); break;
        }

    }

    // returns the correct lexer state for the next character
    // if the character is unknown for some reason (this just checks the ascii value so basically impossible
    //      except for in the case of an operator which is checked against the vector of characters in th hpp file
    //      or if for some reason the character is unicode) then YE_LexError is returned
    YE_LexerFunction GetNextLexerState(char c) {
        if (IsAlpha(c)) return YE_LexIdentifier;
        if (IsDigit(c)) return YE_LexNumber;
        if (IsOperator(c)) return YE_LexOp;
        if (IsWhitespace(c)) return YE_LexWhitespace;
        if (c == '\0') return YE_LexEOF;

        return YE_LexError;
    }


    // Error State
    // empties the error handler's error queue, handling errors as needed, 
    //      if the error is fatal then all remaining state is popped from the stack and 
    //      the lex is aborted. If the error is nonfatal then the error is logged and the lex continues
    void YE_LexError(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        while (state.stack.size() > 0) state.stack.pop();

        YE_ASSERT(state.stack.size() == 0 , "Lexer state stack is not empty after panic empty");

        while (error_handler->errors.size() > 0) {

            Error e = error_handler->errors.front();
            error_handler->errors.pop();

            error_handler->HandleError(e);

        }

        YE_ASSERT(error_handler->errors.size() == 0 , "Error handler errors queue is not empty after panic empty");
    }

    void YE_LexSOF(const std::string& source , LexerState& state , ErrorHandler* error_handler) {
        if (error_handler == nullptr) {
            
            YE_FATAL("Error handler is null during configuration lex");
            return;

        }

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexMinorComment(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        if (source[state.index] != '/') {

            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected '/' to open minor comment" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        } 

        state.index++;
        state.column++;

        if (state.index + 1 >= source.size()) {

            error_handler->errors.push(Error(state.line , state.column , "Unexpected end of file during configuration file lex | Expected '/' to open minor comment" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        } else if (source[state.index] != '/') {
                
            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected '/' to open minor comment" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        while (source[state.index] != '\n') {

            state.index++;
            state.column++;

        }

        state.index++;
        state.column = 0;
        state.line++;

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexMajorComment(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        bool found_end_of_comment = false;
        while (!found_end_of_comment) {
            
            if (state.index + 1 >= source.size()) {
                
                error_handler->errors.push(Error(state.line , state.column , "Unexpected end of file during configuration file lex" , Error::Level::fatal));
                state.stack.pop();
                state.stack.push(YE_LexError);
                return;

            }

            if (source[state.index] == '*') {

                if (state.index + 1 >= source.size()) {
                        
                    error_handler->errors.push(Error(state.line , state.column , "Unexpected end of file during configuration file lex" , Error::Level::fatal));
                    state.stack.pop();
                    state.stack.push(YE_LexError);
                    return;

                } 
                
                if (source[state.index + 1] == '/') {

                    state.column += 2;
                    state.index += 2;
                    found_end_of_comment = true;

                } else {

                    if (source[state.index] == '\n') {
                        
                        state.index++;
                        state.column = 0;
                        state.line++;

                    } else {

                        state.index++;
                        state.column++;

                    }

                }

            } else {

                if (source[state.index] == '\n') {
                    
                    state.index++;
                    state.column = 0;
                    state.line++;

                } else {
                    
                    state.index++;
                    state.column++;

                }

            }

        }

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexEOF(const std::string& source , LexerState& state , ErrorHandler* error_handler) {
        
        if (source[state.index] != '\0') {
            
            error_handler->errors.push(Error(state.line , state.column , "Error handler is null during configuration lex" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        state.stack.pop();
    }

    void YE_LexWhitespace(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        if (!IsWhitespace(source[state.index])) {
                
            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected whitespace" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        while (IsWhitespace(source[state.index])) {

            if (source[state.index] == '\n') {
                
                state.index++;
                state.column = 0;
                state.line++;

            } else {
                    
                state.index++;
                state.column++;

            }

        }

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexIdentifier(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        if (!IsAlphaNumeric(source[state.index])) {

            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected alphanumeric" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        Token token;
        token.type = Token::Type::identifier;
        token.value += source[state.index];
        token.line = state.line;
        token.column = state.column;
        
        state.column++;
        state.index++;

        while (IsAlphaNumeric(source[state.index])) {

            token.value += source[state.index];
            token.line = state.line;
            token.column = state.column;

            state.index++;
            state.column++;

        }

        if (IsKeyword(token.value)) {

            if (state.tokens.back().value.length() >= 2) {

                if (state.tokens.back().value.substr(state.tokens.back().value.length() - 2 , 2) == "::") {
                    state.tokens.back().value += token.value;
                    state.tokens.back().line = token.line;
                    state.tokens.back().column = token.column;
                    
                    state.stack.pop();
                    state.stack.push(GetNextLexerState(source[state.index]));
                    return;

                }

            }
            token.type = Token::Type::keyword;

        } else if (IsBuiltInFunc(token.value)) {

            token.type = Token::Type::func;

        } else {

            token.type = Token::Type::identifier;

        }

        token.line = state.line;
        token.column = state.column;

        state.tokens.push_back(token);
        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexNumber(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        if (!IsDigit(source[state.index])) {

            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected digit" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        Token token;

        token.type = Token::Type::number;
        token.value += source[state.index];
        token.line = state.line;
        token.column = state.column;

        state.index++;
        state.column++;

        while (IsDigit(source[state.index]) || source[state.index] == '.') {

            token.value += source[state.index];
            token.line = state.line;
            token.column = state.column;

            state.index++;
            state.column++;

        }

        if (source[state.index] == 'f') {

            token.value += source[state.index];
            token.line = state.line;
            token.column = state.column;

            state.index++;
            state.column++;

        }

        state.tokens.push_back(token);

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));
    }

    void YE_LexOp(const std::string& source , LexerState& state , ErrorHandler* error_handler) {

        Token token;
        if (source[state.index] == '/' && state.index < source.size() - 1) {

            if (source[state.index + 1] == '/') {

                state.stack.pop();
                state.stack.push(YE_LexMinorComment);
                return;

            } else if (source[state.index + 1] == '*') {

                state.stack.pop();
                state.stack.push(YE_LexMajorComment);
                return;

            }

        } else if (source[state.index] == '"') {

            token.type = Token::Type::string;

            state.index++;
            state.column++;

            while (source[state.index] != '"') {

                token.value += source[state.index];
                token.line = state.line;
                token.column = state.column;

                state.index++;
                state.column++;

            }

            state.index++;
            state.column++;
            state.tokens.push_back(token);
            state.stack.pop();
            state.stack.push(GetNextLexerState(source[state.index]));
            return;

        } else if (source[state.index] == ':' && state.index < source.size() - 1) {

            if (source[state.index + 1] == ':') {

                state.tokens.back().value += "::";
                state.index += 2;
                state.column += 2;

                state.tokens.back().line = state.line;
                state.tokens.back().column = state.column;

                state.stack.pop();
                state.stack.push(GetNextLexerState(source[state.index]));
                return;

            }

        } else if (source[state.index] == '{' && state.tokens.back().value.substr(state.tokens.back().value.length() - 2 , 2) == "::") {

            while (state.index < source.length() && source[state.index] != ';') {

                if (source[state.index] == '\0' || source[state.index] == '>') {

                    error_handler->errors.push(Error(state.line , state.column , "Unexpected end of file" , Error::Level::fatal));

                }

                token.value += source[state.index];
                token.line = state.line;
                token.column = state.column;

                state.index++;
                state.column++;

            }

            token.value += source[state.index];
            token.type = Token::Type::obj_param_value;
            token.line = state.line;
            token.column = state.column;

            state.index++;
            state.column++;
            
            state.tokens.back().type = Token::Type::obj_param;
            state.tokens.push_back(token);

            state.stack.pop();
            state.stack.push(GetNextLexerState(source[state.index]));
            return;
            
        }

        if (!IsOperator(source[state.index])) {

            error_handler->errors.push(Error(state.line , state.column , "Unexpected character during configuration file lex | Expected operator" , Error::Level::fatal));
            state.stack.pop();
            state.stack.push(YE_LexError);
            return;

        }

        token.type = Token::Type::op;
        token.value += source[state.index];
        token.line = state.line;
        token.column = state.column;

        state.index++;
        state.column++;

        state.tokens.push_back(token);

        state.stack.pop();
        state.stack.push(GetNextLexerState(source[state.index]));

    }

    void YE_ParseError(const std::string& source , ParseState& state , ErrorHandler* error_handler) {
        while (!state.stack.empty()) {

            state.stack.pop();

        }

        YE_ASSERT(state.stack.empty() , "Parser state stack is not empty after panic empty");

        while (error_handler->errors.size() > 0) {

            Error e = error_handler->errors.front();
            error_handler->errors.pop();

            error_handler->HandleError(e);

        }

        YE_ASSERT(error_handler->errors.size() == 0 , "Error handler errors queue is not empty after panic empty");
    }

    void YE_ParseSOF(const std::string& source , ParseState& state , ErrorHandler* error_handler) {

        if (error_handler == nullptr) {

            YE_FATAL("Error handler is null in configuration parse");
            return;

        }

        if (state.tokens.size() == 0) {

            YE_FATAL("Token list is empty in configuration parse");
            return;

        }

        state.stack.pop();

        Token token = state.tokens[state.index];

        switch (token.type) {
            default:
                error_handler->errors.push(Error(token.line , token.column , "Unexpected token during configuration file parse | Expected keyword" , Error::Level::fatal));
        }

    }

    void YE_ParseMacro(const std::string& source , ParseState& state , ErrorHandler* error_handler) {



    }

    void YE_ParseYObject(const std::string& source , ParseState& state , ErrorHandler* error_handler) {

    }

}
}