#ifndef LEX_OBJ_STATES_HPP
#define LEX_OBJ_STATES_HPP

#include "lex_states.hpp"

namespace ylang {

    TokenizerState GetNextObjectState(ErrorHandler* err_handler , const RawTkn& tkn);

}

void obj_sof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_unknown_obj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_proj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_build(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_space(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);
void lex_obj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void lex_obj_attributes(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

void obj_eof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler);

#endif