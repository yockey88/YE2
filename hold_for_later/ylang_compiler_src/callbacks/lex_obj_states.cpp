#include "callbacks/lex_obj_states.hpp"

namespace ylang {

    TokenizerState GetNextObjectState(ErrorHandler* err_handler , const RawTkn& tkn) {
        switch (tkn.type) {
            case ylang::RawTknType::l_bracket: return lex_unknown_obj;
            case ylang::RawTknType::eof: return obj_eof;
            default:
                err_handler->SubmitError({ ErrorLevel::fatal , "Lexer in an Unknown State" , 0 , 0 });
                return err_state;
        }
    }

}

void obj_sof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::sof) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <SOF> token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::sof, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    tkn_data->state_stack.push(lex_unknown_obj);
}

void lex_unknown_obj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::l_bracket) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '[' to begin object definition" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::l_bracket, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::lt) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '<' to begin object type declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::lt_op, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    std::string obj_type = tkn_data->GetCurrRawValue();
    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::proj_kw: tkn_data->state_stack.push(lex_proj); break;
        case ylang::RawTknType::build_kw: tkn_data->state_stack.push(lex_build); break;
        case ylang::RawTknType::space_kw: tkn_data->state_stack.push(lex_space); break;
        case ylang::RawTknType::object_kw: tkn_data->state_stack.push(lex_obj); break;
        default:
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Lexer in an Unknown State" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
    }
}

void lex_obj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    UNIMPLIMENTED
}

void lex_proj(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::proj_kw) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected 'project' keyword" , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawTkn().line });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::proj_kw, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::gt) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '>' to close object type declaration" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::gt_op, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::arrow) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '->' to begin object attribute description" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::arrow_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    tkn_data->state_stack.push(lex_obj_attributes);
}

void lex_build(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    UNIMPLIMENTED
}

void lex_space(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    UNIMPLIMENTED
    
}

void lex_obj_attributes(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::l_brace) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '{' to begin object attibute list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

    tkn_data->tokens.push_back({ ylang::TknType::l_brace, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    ylang::TknType t = ylang::TknType::err;
    while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_brace) {
        switch (tkn_data->GetCurrRawType()) {
            case ylang::RawTknType::lt:
                tkn_data->tokens.push_back({ ylang::TknType::lt_op, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::gt:
                tkn_data->tokens.push_back({ ylang::TknType::gt_op, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::arrow:
                tkn_data->tokens.push_back({ ylang::TknType::arrow_op, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::l_brace:
                tkn_data->tokens.push_back({ ylang::TknType::l_brace, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);

                while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_brace) {
                    if (tkn_data->GetCurrRawType() == ylang::RawTknType::comma) {
                        tkn_data->tokens.push_back({ ylang::TknType::comma, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::quote) {
                        tkn_data->tokens.push_back({ ylang::TknType::quote, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::string_literal) {
                        tkn_data->tokens.push_back({ ylang::TknType::string_literal, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    }  else {
                        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected only ',' or identifier in attribute list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                        tkn_data->state_stack.push(err_state);
                        return;
                    }
                }
                tkn_data->tokens.push_back({ ylang::TknType::r_brace, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::quote:
                tkn_data->tokens.push_back({ ylang::TknType::quote, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::comma:
                tkn_data->tokens.push_back({ ylang::TknType::comma, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::dot:
                tkn_data->tokens.push_back({ ylang::TknType::dot, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::int_literal:
                tkn_data->tokens.push_back({ ylang::TknType::int_literal, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::string_literal:
                tkn_data->tokens.push_back({ ylang::TknType::string_literal, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::bool_literal:
                tkn_data->tokens.push_back({ ylang::TknType::bool_literal, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::identifier:
                tkn_data->tokens.push_back({ ylang::TknType::other_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            case ylang::RawTknType::target_kw:
                tkn_data->tokens.push_back({ ylang::TknType::target_kw, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            break;
            default:
                if (IsObjectKeyword(tkn_data->GetCurrRawValue())) {
                    tkn_data->tokens.push_back({ ylang::IdentifyObjToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                    tkn_data->NextRawTkn(err_handler);
                } else {
                    err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected token in object file" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                    tkn_data->state_stack.push(err_state);
                    return;
                }
        }
    }
    tkn_data->tokens.push_back({ ylang::TknType::r_brace, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::r_bracket) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected ']' to end object definition" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::r_bracket, tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(ylang::GetNextObjectState(err_handler , tkn_data->GetCurrRawTkn()));
    }
}

void obj_eof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::eof) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <EOF> token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

    tkn_data->valid = true;
}