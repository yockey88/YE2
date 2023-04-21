#include "validator.hpp"

namespace ylang {

    std::pair<bool , StmntList> Validator::ValidateSrcFile(TokenFilter& tkn_filter , ErrorHandler* err_handler) {
        std::vector<Stmnt> stmnts = tkn_filter.GetStmntList().statements;
        
        StmntList stmnt_list{};

        std::vector<std::string> fn_decl_ids{};
        std::vector<std::string> fn_defn_ids{};
        /* TODO :==> 
            - check imports/exports
        */

        for (auto& stmnt : stmnts) {
            if (stmnt.type == StmntType::function_decl) {
                fn_decl_ids.push_back(stmnt.tokens[1].value);
            } else if (stmnt.type == StmntType::function_defn) {
                fn_defn_ids.push_back(stmnt.tokens[1].value);
            }
        }

        for (auto& fn_decl_id : fn_decl_ids) {
            bool found = false;
            for (auto& fn_defn_id : fn_defn_ids) {
                if (fn_decl_id == fn_defn_id) {
                    found = true;
                    break;
                }
            }
            std::string func_decl_id = fn_decl_id;
            if (!found) {
                err_handler->SubmitError({ ErrorLevel::fatal , "Function [" + std::string{ func_decl_id } + "]" , 0 , 0 });
                return { false , stmnt_list };
            }
        }

        std::cout << "[< src file validated >]\n";
        stmnt_list.statements = stmnts;
        return { true , stmnt_list };

        // for (auto& stmnt : stmnts) {
        //     if (stmnt.type == StmntType::function_defn) {
        //         for (auto& tkn : stmnt.tokens) {
        //             if (IsTypeKeyword(tkn.value)) {
                        
        //             }
        //         }
        //     }
        // }
    }

}