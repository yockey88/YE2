#ifndef LEXER_HPP
#define LEXER_HPP

#include "callbacks/lex_obj_states.hpp"

namespace ylang {

    enum class FileTypes {
        source ,

        project ,
        build ,
        space ,
        object , 
        config ,
        
        error
    };

    class Lexer {
        FileTypes m_FileType = FileTypes::error;
        InitialPassData m_Init_lex_result{};
        TokenizationData m_Tkn_data{};
        ErrorHandler* m_ErrorHandler = nullptr;

        bool m_Valid = false;
        
        void InitialPass();

        bool LexSrcFile();
        bool LexObjFile();
        bool LexCfgFile();

        public:
            Lexer(const std::string& path , ErrorHandler* errors = nullptr);
            ~Lexer() {}
            
            

            bool Lex();
            inline bool IsValid() const { return m_Valid; }     
            
            TokenizationData* GetTokenizationData() { return &m_Tkn_data; }
            const InitialPassData& GetInitialPassData() const { return m_Init_lex_result; }
            const TokenizationData& GetTokenizationData() const { return m_Tkn_data; }
    };

}

#endif