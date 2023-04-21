#include "lexing/token_filter.hpp"

namespace ylang {

    StmntType TokenFilter::GetObjStmntTokens(std::vector<Token>& tkns) {
        StmntType stmnt_type = StmntType::err;

        switch (m_Stmnts.GetCurrType()) {
            case ylang::TknType::proj_kw: stmnt_type = StmntType::proj_stmnt; break;
            case ylang::TknType::build_kw: stmnt_type = StmntType::build_stmnt; break;
            case ylang::TknType::space_kw: stmnt_type = StmntType::space_stmnt; break;
            case ylang::TknType::object_kw: stmnt_type = StmntType::object_stmnt; break;
            default:
                m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Expected object keyword" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
                return StmntType::err;
            break;
        }

        while (m_Stmnts.GetCurrType() != ylang::TknType::r_bracket) {
            tkns.push_back(m_Stmnts.GetCurrTkn());
            m_Stmnts.NextTkn(m_ErrorHandler);
        }

        tkns.push_back(m_Stmnts.GetCurrTkn());
        m_Stmnts.NextTkn(m_ErrorHandler);

        return stmnt_type;
    }

    bool TokenFilter::FilterSrcFile(TokenizationData* tkn_data , ErrorHandler* err_handler) {

        m_ErrorHandler = err_handler;

        tkn_data->index = 0;
        
        if (!tkn_data->valid) {
            m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "TokenizationData is not valid" , 0 , 0 });
            return false;
        } else {
            for (auto tkn : tkn_data->tokens)
                m_Stmnts.lexed_tkns.push_back(tkn);
        }

        m_Stmnts.state_stack.push(sof);

        while (!m_Stmnts.state_stack.empty()) {
            FilterState curr_state = m_Stmnts.state_stack.top();
            m_Stmnts.state_stack.pop();

            curr_state(&m_Stmnts , m_ErrorHandler);
            if (m_Stmnts.index >= m_Stmnts.lexed_tkns.size()) break;
        }

        if (!m_Stmnts.state_stack.empty()) {
            m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Lexer in an Unknown State" , 0 , 0 });
            return false;
        }

        if (!m_ErrorHandler->FlushErrors()) {
            return false;
        }

        for (const auto& stmnt : m_Stmnts.statements) {
            PrintStatement(stmnt);
        }

        return true;
    }
    
    bool TokenFilter::FilterObjFile(TokenizationData* tkn_data , ErrorHandler* err_handler) {
        
        m_ErrorHandler = err_handler;

        tkn_data->index = 0;

        if (!tkn_data->valid) {
            m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "TokenizationData is not valid" , 0 , 0 });
            return false;
        } else {
            for (auto tkn : tkn_data->tokens)
                m_Stmnts.lexed_tkns.push_back(tkn);
        }

        if (m_Stmnts.GetCurrType() != TknType::sof) {
            m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <SOF> token" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
            return false;
        } else {
            std::vector<Token> sof{ m_Stmnts.GetCurrTkn() };
            m_Stmnts.statements.push_back({ StmntType::sof , sof });
            m_Stmnts.NextTkn(m_ErrorHandler);
        }

        while (m_Stmnts.GetCurrType() != TknType::eof) {
            std::vector<Token> tokens{};
            if (m_Stmnts.GetCurrType() != TknType::l_bracket) {
                m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '[' token to open object definition" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
                return false;
            } else {
                tokens.push_back(m_Stmnts.GetCurrTkn());
                m_Stmnts.NextTkn(m_ErrorHandler);
            }

            if (m_Stmnts.GetCurrType() != TknType::lt_op) {
                m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Expected '<' to define object type" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
                return false;
            } else {
                tokens.push_back(m_Stmnts.GetCurrTkn());
                m_Stmnts.NextTkn(m_ErrorHandler);
            }

            StmntType stmnt_type = GetObjStmntTokens(tokens);
            if (stmnt_type == StmntType::err) {
                m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Invalid Statement" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
                return false;
            } else {
                m_Stmnts.statements.push_back({ stmnt_type , tokens });
            }
        }

        if (m_Stmnts.GetCurrType() != TknType::eof) {
            m_ErrorHandler->SubmitError({ ylang::ErrorLevel::fatal , "Expected <EOF> token" , m_Stmnts.GetCurrTkn().line , m_Stmnts.GetCurrTkn().col });
            return false;
        } else {
            std::vector<Token> eof{ m_Stmnts.GetCurrTkn() };
            m_Stmnts.statements.push_back({ StmntType::eof , eof });
        }

        if (!m_ErrorHandler->FlushErrors()) {
            return false;
        }

        // for (const auto& stmnt : m_Stmnts.statements) {
        //     PrintStatement(stmnt);
        // }

        return true;
    }

}