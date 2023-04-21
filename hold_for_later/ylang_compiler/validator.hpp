#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "lexing/token_filter.hpp"

namespace ylang {

    struct Validator {
        std::pair<bool , StmntList> ValidateSrcFile(TokenFilter& tkn_filter , ErrorHandler* err_handler);
        std::pair<bool , StmntList> ValidateObjFile(TokenFilter& tkn_filter , ErrorHandler* err_handler) { UNIMPLIMENTED return { false , StmntList{} }; }
    };

}

#endif