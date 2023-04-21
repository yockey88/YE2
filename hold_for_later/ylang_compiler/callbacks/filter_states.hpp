#ifndef FILTER_STATES_HPP
#define FILTER_STATES_HPP

#include "defines.hpp"

namespace ylang {

    struct StmntList {
        int index = 0;
        bool valid = false;

        std::string filepath = "[< BLANK >]";

        std::vector<Token> lexed_tkns{};
        std::vector<Stmnt> statements{};
        std::stack<FilterState> state_stack{};

        void NextTkn(ErrorHandler *& error_handler);
        void NextStmnt(ErrorHandler& error_handler);
        inline Token GetCurrTkn() const { return lexed_tkns[index]; }
        inline Stmnt GetCurrStmnt() const { return statements[index]; }
        inline TknType GetCurrType() const { return lexed_tkns[index].type; }
        inline StmntType GetCurrStmntType() const { return statements[index].type; }
        inline std::string GetCurrValue() const { return lexed_tkns[index].value; }
        inline std::vector<Token>& GetCurrTokens() { return statements[index].tokens; }
    };

}

void err_state(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);
void sof(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);
void import_stmnt(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);
void fn_stmnt(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);
void eof(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);

#endif