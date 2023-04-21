#ifndef LEX_STATES_HPP
#define LEX_STATES_HPP

#include "fn_lex_states.hpp"

// Lexing Tokens from Raw Tokens
void sof(ylang::TokenizationData* state_data , ylang::ErrorHandler* error_handler);
void lex_keyword(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_identifier(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_tag(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_operator(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_int_literal(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_import(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void eof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

#endif