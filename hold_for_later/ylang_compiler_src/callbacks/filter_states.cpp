#include "callbacks/filter_states.hpp"

namespace ylang {

    void StmntList::NextTkn(ErrorHandler *& error_handler) {
        index++;

        if (index >= lexed_tkns.size()) {
            error_handler->SubmitError({ ErrorLevel::fatal , "<EOF Missing | Out of Bounds>" , 0 , 0 });
            state_stack.push(err_state);
        }
    }
    
    void StmntList::NextStmnt(ErrorHandler& error_handler) {
        index++;

        if (index >= statements.size()) {
            error_handler.SubmitError({ ErrorLevel::fatal , "<EOF Missing | Out of Bounds>" , 0 , 0 });
            return;
        }
    }
    
    FilterState GetNextFilterState(ErrorHandler* err_handler , const Token& tkn) {
        switch (tkn.type) {
            case TknType::import_kw: return import_stmnt;
            case TknType::fn_kw: return fn_stmnt;
            case TknType::fn_id: return fn_stmnt;
            case TknType::eof: return eof;
            case TknType::err: return err_state;
            default:
                err_handler->SubmitError({ ErrorLevel::fatal , "Invalid token type" , 0 , 0 });
                return err_state;
        }
        return nullptr;
    }

}

void err_state(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler) {
    std::cerr << "[< Error Encountered >]\n";
    while (state_data->state_stack.size() > 0) {
        state_data->state_stack.pop();
    }

    if (!error_handler->FlushErrors()) {
        std::cerr << "[< Fatal error(s) occured during token filter >]" << std::endl;
    }

    assert(state_data->state_stack.size() == 0);
}

void sof(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler) {
    if (state_data->GetCurrType() != ylang::TknType::sof) {
        error_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <SOF> token" , state_data->GetCurrTkn().line , state_data->GetCurrTkn().col });
        state_data->state_stack.push(err_state);
    } else {
        std::vector<ylang::Token> tokens{ state_data->GetCurrTkn() };
        state_data->statements.push_back({ ylang::StmntType::sof , tokens });
        state_data->NextTkn(error_handler);

        state_data->state_stack.push(ylang::GetNextFilterState(error_handler , state_data->GetCurrTkn()));
    }
}

void import_stmnt(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler) {
    if (state_data->GetCurrType() != ylang::TknType::import_kw) {
        error_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <import> keyword" , state_data->GetCurrTkn().line , state_data->GetCurrTkn().col });
        state_data->state_stack.push(err_state);
    } else {
        std::vector<ylang::Token> tokens{ state_data->GetCurrTkn() };
        state_data->NextTkn(error_handler);

        while (state_data->GetCurrType() != ylang::TknType::semi_colon) {
            tokens.push_back(state_data->GetCurrTkn());
            state_data->NextTkn(error_handler);
        }
        tokens.push_back(state_data->GetCurrTkn());
        state_data->NextTkn(error_handler);

        state_data->statements.push_back({ ylang::StmntType::import , tokens });
        state_data->state_stack.push(ylang::GetNextFilterState(error_handler , state_data->GetCurrTkn()));

    }
}

void fn_stmnt(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler) {
    std::vector<ylang::Token> fn_decl{ };
    std::vector<ylang::Token> fn_body{ };

    if (state_data->GetCurrType() == ylang::TknType::fn_kw) {
        fn_decl.push_back(state_data->GetCurrTkn());
        fn_body.push_back(state_data->GetCurrTkn());
        state_data->NextTkn(error_handler);
    }
    
    if (state_data->GetCurrType() != ylang::TknType::fn_id) {
        error_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <fn> identifier" , state_data->GetCurrTkn().line , state_data->GetCurrTkn().col });
        state_data->state_stack.push(err_state);
    } else {
        fn_decl.push_back(state_data->GetCurrTkn());
        fn_body.push_back(state_data->GetCurrTkn());
        state_data->NextTkn(error_handler);
    }

    fn_decl.push_back(state_data->GetCurrTkn());
    fn_body.push_back(state_data->GetCurrTkn());
    state_data->NextTkn(error_handler);

    while (state_data->GetCurrType() != ylang::TknType::l_brace &&
            state_data->GetCurrType() != ylang::TknType::semi_colon) {
        fn_body.push_back(state_data->GetCurrTkn());
        state_data->NextTkn(error_handler);
    }

    std::stack<char> brace_stack{};
    switch (state_data->GetCurrType()) {
        case ylang::TknType::semi_colon:
            state_data->statements.push_back({ ylang::StmntType::function_decl , fn_decl });
            state_data->state_stack.push(ylang::GetNextFilterState(error_handler , state_data->GetCurrTkn()));
            return;
        case ylang::TknType::l_brace:

            state_data->statements.push_back({ ylang::StmntType::function_decl , fn_decl });

            fn_body.push_back(state_data->GetCurrTkn());
            state_data->NextTkn(error_handler); 

            brace_stack.push('{');
            while (!brace_stack.empty()) {
                if (state_data->GetCurrType() == ylang::TknType::l_brace) {
                    brace_stack.push('{');
                } else if (state_data->GetCurrType() == ylang::TknType::r_brace) {
                    brace_stack.pop();
                }

                if (state_data->GetCurrType() == ylang::TknType::quote) {
                    std::vector<ylang::Token> captured_tokens{ };
                    while (state_data->GetCurrType() != ylang::TknType::semi_colon) {
                        captured_tokens.push_back(state_data->GetCurrTkn());
                        fn_body.push_back(state_data->GetCurrTkn());
                        state_data->NextTkn(error_handler);
                    }
                    captured_tokens.push_back(state_data->GetCurrTkn());
                    fn_body.push_back(state_data->GetCurrTkn());
                    state_data->NextTkn(error_handler);

                    state_data->statements.push_back({ ylang::StmntType::function_capture , captured_tokens });
                } else {
                    fn_body.push_back(state_data->GetCurrTkn());
                    state_data->NextTkn(error_handler);
                }
            }

            state_data->statements.push_back({ ylang::StmntType::function_defn , fn_body });
            
            state_data->state_stack.push(ylang::GetNextFilterState(error_handler , state_data->GetCurrTkn()));
        break;
        default:
            error_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <{> or <;> token" , state_data->GetCurrTkn().line , state_data->GetCurrTkn().col });
            state_data->state_stack.push(err_state);
            return;
    }
}

void eof(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler) {
    if (state_data->GetCurrType() != ylang::TknType::eof) {
        error_handler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <EOF> token" , state_data->GetCurrTkn().line , state_data->GetCurrTkn().col });
        state_data->state_stack.push(err_state);
        state_data->valid = false;
    } else {
        std::vector<ylang::Token> tokens{ state_data->GetCurrTkn() };
        state_data->statements.push_back({ ylang::StmntType::eof , tokens });

        state_data->valid = true;
    }   
}
