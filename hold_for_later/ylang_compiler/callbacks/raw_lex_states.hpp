#ifndef RAW_LEX_STATES_HPP
#define RAW_LEX_STATES_HPP

#include "defines.hpp"

void err_state(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

namespace ylang {

    struct InitialPassData {
        int index = 0;
        int line = 0 , column = 0;
        std::string filename = "[< BLANK >]";
        std::string source = "[< BLANK >]";
        std::vector<RawTkn> tokens{};
        std::stack<InitialPassState> state_stack;
    };

    struct TokenizationData {
        int index = 0;
        bool valid = false;
        std::string filepath = "[< BLANK >]";

        std::vector<RawTkn> raw_tokens{};
        std::vector<Token> tokens{};
        std::stack<TokenizerState> state_stack;

        void NextRawTkn(ErrorHandler *& error_handler);
        inline RawTkn GetCurrRawTkn() const { return raw_tokens[index]; }
        inline Token GetCurrTkn() const { return tokens[index]; }
        inline RawTknType GetCurrRawType() const { return raw_tokens[index].type; }
        inline TknType GetCurrType() const { return tokens[index].type; }
        inline std::string GetCurrRawValue() const { return raw_tokens[index].value; }
        inline std::string GetCurrValue() const { return tokens[index].value; } 
    };

    InitialPassState GetNextState(char c);
    TokenizerState GetNextTokenizerState(ErrorHandler* err_handler , const RawTkn& tkn);
    FilterState GetNextFilterState(ErrorHandler* err_handler , const Token& tkn);
    FilterState GetReFilterState(ErrorHandler* err_handler , const Token& tkn);

}

// Test Lex Funcs
// void lex_raw_fn(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
// void lex_raw_fn_body(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

// Lexing Raw Tokens
void sof_raw(ylang::InitialPassData* state_data);
void lex_identifier_raw(ylang::InitialPassData* state_data);
void lex_operator_raw(ylang::InitialPassData* state_data);
void lex_punctuator_raw(ylang::InitialPassData* state_data);
void lex_int_literal_raw(ylang::InitialPassData* state_data);
void lex_string_literal_raw(ylang::InitialPassData* state_data);
void lex_char_literal_raw(ylang::InitialPassData* state_data);
void lex_whitespace_raw(ylang::InitialPassData* state_data);
void eof_raw(ylang::InitialPassData* state_data);

#endif