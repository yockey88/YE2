#include "callbacks/raw_lex_states.hpp"

namespace ylang {

    void TokenizationData::NextRawTkn(ErrorHandler *& error_handler) {
        index++;

        if (index >= raw_tokens.size()) {
            error_handler->SubmitError({ ErrorLevel::fatal , "<EOF Missing | Out of Bounds>" , 0 , 0 });
            state_stack.push(err_state);
        }
    }

}

void sof_raw(ylang::InitialPassData* state_data) {
    std::string file_name = "[< " + state_data->filename + " >]";
    state_data->tokens.push_back({ ylang::RawTknType::sof , state_data->line , state_data->column , file_name });

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_identifier_raw(ylang::InitialPassData* state_data) {
    std::string identifier = "";
    while (IsAlphaNumeric(state_data->source[state_data->index])) {
        identifier += state_data->source[state_data->index];
        state_data->index++;
        state_data->column++;
    }
    
    if (IsKeyword(identifier)) {
        state_data->tokens.push_back({ ylang::IdentifyKeywordTkn(identifier) , state_data->line , state_data->column , identifier });
    } else {
        state_data->tokens.push_back({ ylang::RawTknType::identifier , state_data->line , state_data->column , identifier });
    }

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_operator_raw(ylang::InitialPassData* state_data) {
    std::string op = "" , check = "";
    while (IsSymbol(state_data->source[state_data->index])) {
        op += state_data->source[state_data->index];
        check = std::string{ state_data->source[state_data->index+1] };
        state_data->index++;
        state_data->column++;
    }

    ylang::RawTknType type;
    if (IsOperator(op)) {
        type = ylang::IdentifyRawOperator(op);
    } else if (op.length() == 1 && IsPunctuator(op[0])) {
        type = ylang::IdentifyRawPunctuator(op);
    } else {
        type = ylang::RawTknType::op;
    }
    
    state_data->tokens.push_back({ type , state_data->line , state_data->column , op });
    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_punctuator_raw(ylang::InitialPassData* state_data) {
    std::string punctuator = { state_data->source[state_data->index] };
    state_data->index++;
    state_data->column++;

    if (punctuator == ":" && std::string{ state_data->source[state_data->index] } == ":") {
        punctuator += state_data->source[state_data->index];
        state_data->index++;
        state_data->column++;

        state_data->tokens.push_back({ ylang::RawTknType::scope , state_data->line , state_data->column , punctuator });
    } else {
        state_data->tokens.push_back({ ylang::IdentifyRawPunctuator(punctuator) , state_data->line , state_data->column , punctuator });
    }

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_int_literal_raw(ylang::InitialPassData* state_data) {
    std::string int_literal = "";
    while (std::isdigit(state_data->source[state_data->index])) {
        int_literal += state_data->source[state_data->index];
        state_data->index++;
        state_data->column++;
    }
    state_data->tokens.push_back({ ylang::RawTknType::int_literal , state_data->line , state_data->column , int_literal });

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_string_literal_raw(ylang::InitialPassData* state_data) {
    std::string string_literal = "";

    state_data->tokens.push_back({ ylang::RawTknType::quote , state_data->line , state_data->column , std::string{ state_data->source[state_data->index] } });
    state_data->index++;
    state_data->column++;

    while (state_data->source[state_data->index] != '"') {
        string_literal += state_data->source[state_data->index];
        state_data->index++;
        state_data->column++;
    }
    state_data->tokens.push_back({ ylang::RawTknType::string_literal , state_data->line , state_data->column , string_literal });

    state_data->tokens.push_back({ ylang::RawTknType::quote , state_data->line , state_data->column , std::string{ state_data->source[state_data->index] } });
    state_data->index++;
    state_data->column++;

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void lex_char_literal_raw(ylang::InitialPassData* state_data) {
    std::string string_literal = "";

    state_data->tokens.push_back({ ylang::RawTknType::apostrophe , state_data->line , state_data->column , string_literal });
    state_data->index++;
    state_data->column++;

    while (state_data->source[state_data->index] != '\'') {
        string_literal += state_data->source[state_data->index];
        state_data->index++;
        state_data->column++;
    }
    state_data->tokens.push_back({ ylang::RawTknType::string_literal , state_data->line , state_data->column , string_literal });

    state_data->tokens.push_back({ ylang::RawTknType::apostrophe , state_data->line , state_data->column , string_literal });
    state_data->index++;
    state_data->column++;

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

// void lex_comment_raw(ylang::InitialPassData* state_data) {
//     std::string comment = "";
//     while (state_data->source[state_data->index] != '\n') {
//         comment += state_data->source[state_data->index];
//         state_data->index++;
//         state_data->column++;
//     }
//     state_data->tokens.push_back({ ylang::RawTknType::comment , state_data->line , state_data->column , comment });

//     state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
// }

void lex_whitespace_raw(ylang::InitialPassData* state_data) {
    state_data->index++;
    state_data->column++;

    if (state_data->source[state_data->index] == '\n') {
        state_data->line++;
        state_data->column = 0;
    }

    state_data->state_stack.push(ylang::GetNextState(state_data->source[state_data->index]));
}

void eof_raw(ylang::InitialPassData* state_data) {
    ylang::RawTkn eof_tkn = { ylang::RawTknType::eof , state_data->line , state_data->column , "[< " + state_data->filename + " >]" };
    state_data->tokens.push_back(eof_tkn);
}