#include "callbacks/lex_states.hpp"

namespace ylang {

    InitialPassState GetNextState(char c) {
        if (IsAlpha(c)) return lex_identifier_raw;
        if (IsSymbol(c) && c == '"') return lex_string_literal_raw;
        if (IsSymbol(c) && c == '\'') return lex_char_literal_raw;
        if (IsSymbol(c) && c != '"' && c != '\'' && !IsPunctuator(c)) return lex_operator_raw;
        if (IsPunctuator(c)) return lex_punctuator_raw;
        if (IsNumeric(c)) return lex_int_literal_raw;
        if (IsWhiteSpace(c) || c =='\n' || c == '\t' || c == '\r' || c == '\v') return lex_whitespace_raw;
        if (c == '\0') return eof_raw;
        return nullptr;
    }

    TokenizerState GetNextTokenizerState(ErrorHandler* err_handler , const RawTkn& tkn) {
        switch (tkn.type) {
            case ylang::RawTknType::r_bracket: return lex_fn_tag;
            case ylang::RawTknType::keyword: return lex_keyword;
            case ylang::RawTknType::import_kw: return lex_import;
            case ylang::RawTknType::export_kw: return lex_fn;
            case ylang::RawTknType::package_kw: return lex_fn;
            case ylang::RawTknType::fn_kw: return lex_fn;
            case ylang::RawTknType::identifier: return lex_identifier;
            case ylang::RawTknType::eof: return eof;
            case ylang::RawTknType::err:
            default: 
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected token" , tkn.line , tkn.col });
                return err_state;
        }
    }

}

void err_state(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    std::cerr << "[< Error Encountered >]\n";
    while (tkn_data->state_stack.size() > 0) {
        tkn_data->state_stack.pop();
    }

    if (!err_handler->FlushErrors()) {
        std::cerr << "[< Fatal error(s) occured during tokenization >]" << std::endl;
    }

    assert(tkn_data->state_stack.size() == 0);
}

void sof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::sof) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <SOF> token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        std::string value = "<SOF> -> " + tkn_data->filepath;
        tkn_data->tokens.push_back({ ylang::TknType::sof , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , value });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
    }

    while (tkn_data->GetCurrRawType() != ylang::RawTknType::eof) {
        if (tkn_data->GetCurrRawType() == ylang::RawTknType::eof) break;

        if (tkn_data->index >= tkn_data->raw_tokens.size()) {
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected end of file" , tkn_data->raw_tokens[tkn_data->index - 1].line , tkn_data->raw_tokens[tkn_data->index - 1].col });
            tkn_data->state_stack.push(err_state);
            return;
        }

        TokenizerState state = tkn_data->state_stack.top();
        tkn_data->state_stack.pop();

        state(tkn_data , err_handler);
    }
}

void lex_keyword(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {

    ylang::TknType type = ylang::IdentifyKeywordTkn(tkn_data->GetCurrRawTkn());

    switch (type) {
        case ylang::TknType::import_kw: tkn_data->state_stack.push(lex_import); break;
        case ylang::TknType::fn_kw:
            tkn_data->tokens.push_back({ ylang::TknType::fn_kw , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
            tkn_data->state_stack.push(lex_identifier);
        break;
        default: 
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected token -> [" + tkn_data->GetCurrRawTkn().value + "]" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
        break;
    }

}

void lex_identifier(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->index + 1 >= tkn_data->raw_tokens.size()) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Unexpected end of file" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

    tkn_data->tokens.push_back({ ylang::TknType::fn_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    tkn_data->state_stack.push(lex_fn);

}

void lex_fn_tag(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    if (tkn_data->GetCurrRawType() != ylang::RawTknType::r_bracket) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <R_BRACKET> token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::r_bracket , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->tokens.push_back({ ylang::TknType::fn_tag_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->tokens.push_back({ ylang::TknType::l_bracket , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->tokens.push_back({ ylang::TknType::fn_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);

        tkn_data->state_stack.push(lex_fn);
    }
}

void lex_operator(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    ylang::TknType type = ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn());
    if (type != ylang::TknType::err) {
        tkn_data->tokens.push_back({ type , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    } else {

        std::string tkn = "";
        for (auto& c : tkn_data->GetCurrRawValue()) {
            tkn += c;

            if (IsOperator(tkn)) {
                tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken({ ylang::RawTknType::op , tkn }) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn });
                tkn_data->NextRawTkn(err_handler);

                tkn = "";
            }

        }

        for (auto& c : tkn) {
            if (IsPunctuator({ c })) {
                tkn_data->tokens.push_back({ ylang::IdentifyPunctuatorToken({ ylang::RawTknType::punctuator , { c } }) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , { c } });
                tkn_data->NextRawTkn(err_handler);
            } else {
                std::string err_msg = "Invalid operator { " + std::string{ c }  + " }";
                err_handler->SubmitError({ ylang::ErrorLevel::warning , err_msg  , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            }
        }

    }
}

void lex_int_literal(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {
    tkn_data->tokens.push_back({ ylang::TknType::int_literal , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
    tkn_data->NextRawTkn(err_handler);

    tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));
}

void lex_import(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::import_kw) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected import keyword" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else {
        tkn_data->tokens.push_back({ ylang::TknType::import_kw , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::identifier){
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected module identifier" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    } else  {
        tkn_data->tokens.push_back({ ylang::TknType::module_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
        tkn_data->NextRawTkn(err_handler);
    }

    switch (tkn_data->GetCurrRawType()) {
        case ylang::RawTknType::semicolon:
            tkn_data->tokens.push_back({ ylang::IdentifyOperatorToken(tkn_data->GetCurrRawTkn()) , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);
        break;
        case ylang::RawTknType::scope:
            tkn_data->tokens.push_back({ ylang::TknType::scope_op , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
            tkn_data->NextRawTkn(err_handler);

            if (tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                tkn_data->tokens.push_back({ ylang::TknType::package_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::l_brace) {
                tkn_data->tokens.push_back({ ylang::TknType::l_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
                while (tkn_data->GetCurrRawType() != ylang::RawTknType::r_brace) {
                    if (tkn_data->GetCurrRawType() == ylang::RawTknType::identifier) {
                        tkn_data->tokens.push_back({ ylang::TknType::package_id , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else if (tkn_data->GetCurrRawType() == ylang::RawTknType::comma) {
                        tkn_data->tokens.push_back({ ylang::TknType::comma , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                        tkn_data->NextRawTkn(err_handler);
                    } else {
                        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected identifier" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                        tkn_data->state_stack.push(err_state);
                        return;
                    }
                }
                tkn_data->tokens.push_back({ ylang::TknType::r_brace , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            } else {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected module identifier or identifier list" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->state_stack.push(err_state);
                return;
            }

            if (tkn_data->GetCurrRawType() != ylang::RawTknType::semicolon) {
                err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected semicolon" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
                tkn_data->state_stack.push(err_state);
                return;
            } else {
                tkn_data->tokens.push_back({ ylang::TknType::semi_colon , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col , tkn_data->GetCurrRawValue() });
                tkn_data->NextRawTkn(err_handler);
            }

        break;
        default:   
            err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected semicolon or scope operator" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
            tkn_data->state_stack.push(err_state);
            return;
    }

    tkn_data->state_stack.push(ylang::GetNextTokenizerState(err_handler , tkn_data->GetCurrRawTkn()));

}

void eof(ylang::TokenizationData* tkn_data , ylang::ErrorHandler* err_handler) {

    if (tkn_data->GetCurrRawType() != ylang::RawTknType::eof) {
        err_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected end of file token" , tkn_data->GetCurrRawTkn().line , tkn_data->GetCurrRawTkn().col });
        tkn_data->state_stack.push(err_state);
        return;
    }

    tkn_data->valid = true;

}
