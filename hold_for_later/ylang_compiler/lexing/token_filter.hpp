#ifndef TOKEN_FILTER_HPP
#define TOKEN_FILTER_HPP

#include "lexer.hpp"
#include "callbacks/filter_states.hpp"

namespace ylang {

    class TokenFilter {
        StmntList m_Stmnts{};
        StmntList m_FinalStmnts{};
        ErrorHandler* m_ErrorHandler = nullptr;

        StmntType GetObjStmntTokens(std::vector<Token>& tkns);

        public:
            TokenFilter() {}
            ~TokenFilter() {}

            bool FilterSrcFile(TokenizationData* tkn_data , ErrorHandler* err_handler);
            bool FilterObjFile(TokenizationData* tkn_data , ErrorHandler* err_handler);

            inline StmntList GetStmntList() { return m_Stmnts; }
    };

}

#endif