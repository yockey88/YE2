#include "callbacks/fn_lex_states.hpp"

namespace ylang {

    TokenizerState GetNextFunctionState(ErrorHandler* err_handler , const RawTkn& tkn) {
        switch (tkn.type) {
            case ylang::RawTknType::i8_kw: return lex_fn_var_decl;
            case ylang::RawTknType::i16_kw: return lex_fn_var_decl;
            case ylang::RawTknType::i32_kw: return lex_fn_var_decl;
            case ylang::RawTknType::i64_kw: return lex_fn_var_decl;
            case ylang::RawTknType::u8_kw: return lex_fn_var_decl;
            case ylang::RawTknType::u16_kw: return lex_fn_var_decl;
            case ylang::RawTknType::u32_kw: return lex_fn_var_decl;
            case ylang::RawTknType::u64_kw: return lex_fn_var_decl;
            case ylang::RawTknType::f32_kw: return lex_fn_var_decl;
            case ylang::RawTknType::f64_kw: return lex_fn_var_decl;
            case ylang::RawTknType::char_kw: return lex_fn_var_decl;
            case ylang::RawTknType::string_kw: return lex_fn_var_decl;
            case ylang::RawTknType::bool_kw: return lex_fn_var_decl;
            case ylang::RawTknType::quote: return lex_fn_str_capture;
            case ylang::RawTknType::return_kw: return lex_fn_return;
            case ylang::RawTknType::r_brace: return lex_fn_end;
            case ylang::RawTknType::identifier: return lex_fn_identifier;
            case ylang::RawTknType::err:
            default: 
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected token" , tkn.line , tkn.col });
                return err_state;
        }
    }

}

void lex_fn(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() == ylang::RawTknType::fn_kw) {
        tkn_data->tokens.push_back({ ylang::TknType::fn_kw , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        if (tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
            tkn_data->tokens.push_back({ ylang::TknType::fn_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
        } else {
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expecting identifier after 'fn' keyword" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(err_state);
            return;
        }
    } 
    
    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::colon:
            tkn_data->tokens.push_back({ ylang::TknType::colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_paren) {
                tkn_data->state_stack.push(lex_fn_params);
                return;
            } else {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->NextRawTkn(err_handler);
                tkn_data->state_stack.push(err_state);
                return;
            }

            if (!IsKeyword(tkn_data->GetCurrRawValue())) {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expecting parameter list when using [<id> : <parameters>] syntax" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->NextRawTkn(err_handler);
                tkn_data->state_stack.push(err_state);
                return;
            } else {
                tkn_data->tokens.push_back({ ylang::IdentifyFuncParamType(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            }

            if (tkn_data->GetCurrRawType() == ylang::RawTknType::arrow) {
                tkn_data->tokens.push_back({ ylang::TknType::arrow_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
                tkn_data->state_stack.push(lex_fn_return_types);
            } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_brace) {
                tkn_data->state_stack.push(lex_fn_body);
            } else {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->NextRawTkn(err_handler);
                tkn_data->state_stack.push(err_state);
                return;
            }

        break;
        case ylang::RawTknType::l_paren:
            tkn_data->state_stack.push(lex_fn_params);
        break;
        case ylang::RawTknType::arrow:
            tkn_data->tokens.push_back({ ylang::TknType::arrow_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(lex_fn_return_types);
        break;
        case ylang::RawTknType::semicolon:
            tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
        break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(err_state);
            return;
    }
}

void lex_fn_params(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::l_paren) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '(' to open function parameter list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
        switch (tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::colon:
                tkn_data->tokens.push_back({ ylang::TknType::colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::identifier:
                tkn_data->tokens.push_back({ ylang::TknType::fn_param_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::comma:
                tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            default:
                if (IsTypeKeyword(tkn_data->GetCurrRawValue())) {
                    tkn_data->tokens.push_back({ ylang::IdentifyFuncParamType(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                    return;
                }
        }
    }
    tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);
    
    if (tkn_data->GetCurrRawType() == ylang::RawTknType::arrow) {
        tkn_data->tokens.push_back({ ylang::TknType::arrow_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
        tkn_data->state_stack.push(lex_fn_return_types);
    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_brace) {
        tkn_data->state_stack.push(lex_fn_body);
    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::colon) {
        tkn_data->tokens.push_back({ ylang::TknType::colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        if (tkn_data->GetCurrRawType() != ylang::RawTknType::l_paren) {
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '(' to open function parameter list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
        } else {
            tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
        }

        while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
            switch (tkn_data->GetCurrRawType()) {
                case ylang::RawTknType::comma:
                    tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                default:
                    if (IsTypeKeyword(tkn_data->GetCurrRawValue())) {
                        tkn_data->tokens.push_back({ ylang::IdentifyFuncParamType(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else {
                        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                        tkn_data->state_stack.push(err_state);
                        return;
                    }
            }
        }
        tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        if (tkn_data->GetCurrRawType() == ylang::RawTknType::arrow) {
            tkn_data->tokens.push_back({ ylang::TknType::arrow_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(lex_fn_return_types);
        } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_brace) {
            tkn_data->state_stack.push(lex_fn_body);
        } else {
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '->' to denote return types, or '{' to open function body" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
        }

    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::semicolon) {
        tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
        tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
    } else {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '->' to denote return types, '(' to clarify parameters, or '{' to open function body" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

}

void lex_fn_return_types(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_paren) {
        tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
            switch (tkn_data->GetCurrRawType()) {
                case ylang::RawTknType::comma:
                    tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                default:
                    if (IsTypeKeyword(tkn_data->GetCurrRawValue())) {
                        tkn_data->tokens.push_back({ ylang::IdentifyFuncReturnType(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else {
                        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                        tkn_data->state_stack.push(err_state);
                        return;
                    }
            }
        }
        tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
        
    } else if (IsTypeKeyword(tkn_data->GetCurrRawValue())) {
        tkn_data->tokens.push_back({ ylang::IdentifyFuncReturnType(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_brace) {
        tkn_data->state_stack.push(lex_fn_body);
        return;
    } else {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

    if (tkn_data->GetCurrRawType() ==  ylang::RawTknType::l_brace) {
        tkn_data->state_stack.push(lex_fn_body);
    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::semicolon) {
        tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
    } else {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }
}

void lex_fn_body(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::l_brace) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '{' to open function body" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::l_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        switch (tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::i8_kw: 
            case ylang::RawTknType::i16_kw:
            case ylang::RawTknType::i32_kw:
            case ylang::RawTknType::i64_kw:
            case ylang::RawTknType::u8_kw: 
            case ylang::RawTknType::u16_kw:
            case ylang::RawTknType::u32_kw:
            case ylang::RawTknType::u64_kw:
            case ylang::RawTknType::f32_kw:
            case ylang::RawTknType::f64_kw:
            case ylang::RawTknType::char_kw:
            case ylang::RawTknType::string_kw:
            case ylang::RawTknType::bool_kw: tkn_data->state_stack.push(lex_fn_var_decl); break;
            case ylang::RawTknType::quote: tkn_data->state_stack.push(lex_fn_str_capture); break;
            case ylang::RawTknType::return_kw: tkn_data->state_stack.push(lex_fn_return); break;
            default:
                tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
            break;
        }
        return;
    }
}

void lex_fn_var_decl(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) { 
    ylang::TknType t;
    if (!IsTypeKeyword(tkn_data->GetCurrRawValue())) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected type keyword" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        t = ylang::IdentifyVariableTypeTkn(tkn_data->GetCurrRawTkn());
        tkn_data->tokens.push_back({ t , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::identifier) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected identifier for variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        ylang::TknType t = ylang::IdentifyVarIdTypeTkn(tkn_data->tokens.back().type);
        tkn_data->tokens.push_back({ t , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::assign: tkn_data->state_stack.push(lex_fn_var_init); break;
        case ylang::RawTknType::semicolon:
            tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
        break;
        case ylang::RawTknType::comma:
            tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            while (tkn_data->GetCurrRawType() == ylang::RawTknType::comma || tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                if (tkn_data->GetCurrRawType() == ylang::RawTknType::comma) {
                    tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    tkn_data->tokens.push_back({ t , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                }
            }

            switch (tkn_data->GetCurrRawType()) {
                case ylang::RawTknType::assign: tkn_data->state_stack.push(lex_fn_var_init); break;
                case ylang::RawTknType::semicolon:
                    tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);

                    tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
                break;
                default:
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '=' or ';' after variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                break;
            }
        break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '=' or ';' after variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
        break;
    }
}

void lex_fn_var_init(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::assign) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '=' after variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::assignment_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    while (tkn_data->GetCurrRawType() != ylang::RawTknType::semicolon && tkn_data->GetCurrRawType() != ylang::RawTknType::comma) {
        switch (tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::quote:
                tkn_data->tokens.push_back({ ylang::TknType::quote , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::apostrophe:
                tkn_data->tokens.push_back({ ylang::TknType::apostrophe , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::identifier:
                tkn_data->tokens.push_back({ ylang::TknType::var_assign_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::int_literal:
                tkn_data->tokens.push_back({ ylang::TknType::var_assign_int , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::char_literal:
                tkn_data->tokens.push_back({ ylang::TknType::var_assign_char , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::string_literal:
                tkn_data->tokens.push_back({ ylang::TknType::var_assign_string , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::bool_literal:
                tkn_data->tokens.push_back({ ylang::TknType::var_assign_bool , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::l_paren:
                tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
                
                while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
                    switch (tkn_data->GetCurrRawType()) {
                        case ylang::RawTknType::identifier:
                            tkn_data->tokens.push_back({ ylang::TknType::var_assign_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::comma:
                            tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::int_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::var_assign_int , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::char_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::var_assign_char , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::string_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::var_assign_string , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::bool_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::var_assign_bool , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        default:
                            if (IsOperator(tkn_data->GetCurrRawValue())) {
                                tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                                tkn_data->NextRawTkn(err_handler);
                            } else {
                                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture function call" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                                tkn_data->state_stack.push(err_state);
                                return;
                            }
                    } 
                }
                tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            default:
                if (IsOperator(tkn_data->GetCurrRawValue())) {
                    tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture function call" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                    return;
                }
        }
    }

    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::semicolon:
            tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
        break;
        case ylang::RawTknType::comma:
            tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            while (tkn_data->GetCurrRawType() == ylang::RawTknType::comma || tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                if (tkn_data->GetCurrRawType() == ylang::RawTknType::comma) {
                    tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    tkn_data->tokens.push_back({ ylang::TknType::var_assign_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                }
            }

            switch (tkn_data->GetCurrRawType()) {
                case ylang::RawTknType::assign: tkn_data->state_stack.push(lex_fn_var_init); break;
                case ylang::RawTknType::semicolon:
                    tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);

                    tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
                break;
                default:
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '=' or ';' after variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                break;
            }
        break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected ';' or ',' after variable declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
        break;
    }
}

void lex_fn_capture_dest(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::dollar) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '$' to open capture destination" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::dollar_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::gt:
            tkn_data->tokens.push_back({ ylang::TknType::gt_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
        break;
        case ylang::RawTknType::l_brace:
            /* TODO :==> Make this shit way cooler 
                - capture raw data into functions
                - capture functions into other functions
                - use captures as a pseudo-function pointer:
                    ~ capture funtion into object (idk how yet) that can be used later 
            */
            tkn_data->tokens.push_back({ ylang::TknType::l_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_brace) {
                switch (tkn_data->GetCurrRawType()) {
                    case ylang::RawTknType::identifier:
                        tkn_data->tokens.push_back({ ylang::TknType::captured_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    case ylang::RawTknType::int_literal:
                        tkn_data->tokens.push_back({ ylang::TknType::i32_fn_param , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    case ylang::RawTknType::char_literal:
                        tkn_data->tokens.push_back({ ylang::TknType::char_fn_param , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    case ylang::RawTknType::string_literal:
                        tkn_data->tokens.push_back({ ylang::TknType::string_fn_param , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    case ylang::RawTknType::bool_literal:
                        tkn_data->tokens.push_back({ ylang::TknType::bool_fn_param , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    case ylang::RawTknType::comma:
                        tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    break;
                    default:
                        if (IsOperator(tkn_data->GetCurrRawValue())) {
                            tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        } else {
                            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                            tkn_data->state_stack.push(err_state);
                            return;
                        }
                    break;
                }
            }
            tkn_data->tokens.push_back({ ylang::TknType::r_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            if (tkn_data->GetCurrRawType() != ylang::RawTknType::gt) {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '>' to close capture destination" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->state_stack.push(err_state);
                return;
            } else {
                tkn_data->tokens.push_back({ ylang::TknType::gt_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            }
        break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture destination" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
    }

    while (tkn_data->GetCurrRawType() != ylang::RawTknType::semicolon) {
        switch (tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::identifier:
                tkn_data->tokens.push_back({ ylang::TknType::capture_dest_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::scope:
                tkn_data->tokens.back().type = ylang::TknType::scope_id;
                tkn_data->tokens.push_back({ ylang::TknType::scope_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::l_paren:
                tkn_data->tokens.back().type = ylang::TknType::fn_id;
                tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);

                while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
                    switch (tkn_data->GetCurrRawType()) {
                        case ylang::RawTknType::identifier:
                            tkn_data->tokens.push_back({ ylang::TknType::fn_call_param , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::comma:
                            tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        default:
                            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture function call" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                            tkn_data->state_stack.push(err_state);
                            return;
                    } 
                }
                tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::dot:
                tkn_data->tokens.push_back({ ylang::TknType::dot , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            default:
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected Token in capture destination" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->state_stack.push(err_state);
                return;
        }
    }
    tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
}

void lex_fn_str_capture(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::quote) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '\"' to open string capture" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::quote , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::string_literal) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected string literal" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::string_literal , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::quote) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '\"' to close string capture" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::quote , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    tkn_data->state_stack.push(lex_fn_capture_dest);
}

void lex_fn_identifier(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    tkn_data->tokens.push_back({ ylang::TknType::other_decl , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_paren) {
        tkn_data->tokens.back().type = ylang::TknType::fn_call_id;
        tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
            switch (tkn_data->GetCurrRawType()) {
                case ylang::RawTknType::identifier:
                    tkn_data->tokens.push_back({ ylang::TknType::fn_call_param_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                case ylang::RawTknType::int_literal:
                    tkn_data->tokens.push_back({ ylang::TknType::fn_call_param_int , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                case ylang::RawTknType::char_literal:
                    tkn_data->tokens.push_back({ ylang::TknType::fn_call_param_char , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                case ylang::RawTknType::string_literal:
                    tkn_data->tokens.push_back({ ylang::TknType::fn_call_param_string , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                case ylang::RawTknType::bool_literal:
                    tkn_data->tokens.push_back({ ylang::TknType::fn_call_param_bool , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                case ylang::RawTknType::comma:
                    tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                break;
                default:
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected identifier or ',' in function call parameter list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                    return;
            }
        }

        tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        if (tkn_data->GetCurrRawType() == ylang::RawTknType::semicolon) {
            tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            
            tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
            return;
        } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::dollar) {
            tkn_data->tokens.back().type = ylang::TknType::captured_id;
            tkn_data->state_stack.push(lex_fn_capture_dest);
            return;
        } else {
            tkn_data->tokens.push_back({ ylang::TknType::captured_fn_call , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
        }
    }

    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::dollar: break;
        case ylang::RawTknType::assign:
            tkn_data->tokens.push_back({ ylang::TknType::assignment_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(lex_fn_var_init);
            return;
        break;
        case ylang::RawTknType::semicolon:
            tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(ylang::GetNextFunctionState(err_handler , tkn_data->GetCurrRawTkn()));
            return;
        break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected ';' or '=' after identifier" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::dollar) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '$' to capture function call" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->state_stack.push(lex_fn_capture_dest);
    }
}

void lex_fn_return(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::return_kw) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected 'return' keyword" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::return_kw , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    while (tkn_data->GetCurrRawType() != ylang::RawTknType::semicolon) {
        switch ( tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::int_literal:
                tkn_data->tokens.push_back({ ylang::TknType::int_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::char_literal:
                tkn_data->tokens.push_back({ ylang::TknType::char_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::string_literal:
                tkn_data->tokens.push_back({ ylang::TknType::string_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::bool_literal:
                tkn_data->tokens.push_back({ ylang::TknType::bool_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::l_paren:
                tkn_data->tokens.push_back({ ylang::TknType::l_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , "(" });
                tkn_data->NextRawTkn(err_handler);
                while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_paren) {
                    switch ( tkn_data->GetCurrRawType()) {
                        case ylang::RawTknType::int_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::int_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::char_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::char_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::string_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::string_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        case ylang::RawTknType::bool_literal:
                            tkn_data->tokens.push_back({ ylang::TknType::bool_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                            tkn_data->NextRawTkn(err_handler);
                        break;
                        default:
                            if (tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                                tkn_data->tokens.push_back({ ylang::TknType::other_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                                tkn_data->NextRawTkn(err_handler);
                            } else if (IsOperator(tkn_data->GetCurrRawValue())) {
                                tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                                tkn_data->NextRawTkn(err_handler);
                            } else {
                                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected return value" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                                tkn_data->state_stack.push(err_state);
                                return;
                            }
                    }
                }
                tkn_data->tokens.push_back({ ylang::TknType::r_paren , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , ")" });
                tkn_data->NextRawTkn(err_handler);
            break;
            default:
                if (tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                    tkn_data->tokens.push_back({ ylang::TknType::other_fn_return , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else if (IsOperator(tkn_data->GetCurrRawValue())) {
                    tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected return value" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                    return;
                }
        }
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::semicolon) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected ';' after return statement" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(lex_fn_end);
        
        return;
    }
}

void lex_fn_end(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::r_brace) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '}' to close function body" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::r_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
        return;
    }
}