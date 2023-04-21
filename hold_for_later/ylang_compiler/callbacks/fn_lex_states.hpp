#ifndef FUNC_LEX_STATES_HPP
#define FUNC_LEX_STATES_HPP

#include "raw_lex_states.hpp"

namespace ylang {

    TokenizerState GetNextFunctionState(ErrorHandler* err_handler , const RawTkn& tkn);

}

void lex_fn(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_params(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_return_types(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_body(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_var_decl(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_var_init(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_capture_dest(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_fn_str_capture(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_fn_identifier(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_fn_return(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_fn_end(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

#endif