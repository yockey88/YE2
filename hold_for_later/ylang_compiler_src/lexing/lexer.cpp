#include "lexing/lexer.hpp"

#include "parsers/config_parser.hpp"

namespace ylang {
        
    void Lexer::InitialPass() {

        m_Init_lex_result.filename = m_Tkn_data.filepath;

        std::ifstream source_file(m_Tkn_data.filepath);
        if (!source_file.is_open()) {
            m_Valid = false;
            std::cout << "Could not open file: " + m_Tkn_data.filepath << std::endl;
            return;
        }

        std::stringstream ss;
        ss << source_file.rdbuf();
        m_Init_lex_result.source = ss.str();
        m_Init_lex_result.source += '\0';

        m_Init_lex_result.state_stack.push(sof_raw);
        while (!m_Init_lex_result.state_stack.empty()) {
            InitialPassState curr_state = m_Init_lex_result.state_stack.top();
            m_Init_lex_result.state_stack.pop();

            curr_state(&m_Init_lex_result);
            if (m_Init_lex_result.index >= m_Init_lex_result.source.size()) break;
        }
        for (auto& tkn : m_Init_lex_result.tokens) {
            if (tkn.type == RawTknType::op) {
                tkn.type = IdentifyRawOperator(tkn.value);
            } else if (IsObjectKeyword(tkn.value)) {
                tkn.type = IdentifyRawObjToken(tkn.value);
            }
        }
        for (const auto& tkn : m_Init_lex_result.tokens) {
            m_Tkn_data.raw_tokens.push_back(tkn);
        }

        m_Valid = true;

    }

    bool Lexer::LexSrcFile() {
        
        std::cout << "[< Lexer | Lexing Src File >]\n";

        m_Tkn_data.state_stack.push(sof);
        while (!m_Tkn_data.state_stack.empty()) {
            TokenizerState curr_state = m_Tkn_data.state_stack.top();
            m_Tkn_data.state_stack.pop();

            if (curr_state == nullptr) {
                std::cerr << "< Fatal Error | Lexer in an Unknown State >" << std::endl;
                while (!m_Tkn_data.state_stack.empty()) {
                    m_Tkn_data.state_stack.pop();
                }
                return false;
            }

            curr_state(&m_Tkn_data , m_ErrorHandler);

            if (!m_ErrorHandler->FlushErrors()) {
                std::cerr << "< Lex Aborted >\n";
                return false;
            }
        }

        return true;
    }
    
    bool Lexer::LexObjFile() {

        std::cout << "[< Lexer | Lexing Object File >]\n";
        
        m_Tkn_data.state_stack.push(obj_sof);
        while (!m_Tkn_data.state_stack.empty()) {
            TokenizerState curr_state = m_Tkn_data.state_stack.top();
            m_Tkn_data.state_stack.pop();

            if (curr_state == nullptr) {
                std::cerr << "< Fatal Error | Lexer in an Unknown State >" << std::endl;
                while (!m_Tkn_data.state_stack.empty()) {
                    m_Tkn_data.state_stack.pop();
                }
                return false;
            }

            curr_state(&m_Tkn_data , m_ErrorHandler);

            if (!m_ErrorHandler->FlushErrors()) {
                std::cerr << "< Lex Aborted >\n";
                return false;
            }
        }

        return true;
    }

    
    bool Lexer::LexCfgFile() {
        
        std::cout << "[< Lexer | Lexing Config File >]\n";


        
        return true;
    }

    Lexer::Lexer(const std::string& filepath , ErrorHandler* handler) {
        m_Tkn_data.filepath = filepath;
        m_ErrorHandler = handler;

        if (filepath.find(".y") != std::string::npos && filepath.find(".yproj") == std::string::npos &&
            filepath.find(".ybuild") == std::string::npos && filepath.find(".yspace") == std::string::npos &&
            filepath.find(".yobj") == std::string::npos && filepath.find(".ycfg") == std::string::npos) {
            
            m_FileType = FileTypes::source;
        
        } else if (filepath.find(".yproj") != std::string::npos) {
            m_FileType = FileTypes::project;
        } else if (filepath.find(".ybuild") != std::string::npos) {
            m_FileType = FileTypes::build;
        } else if (filepath.find(".yspace") != std::string::npos) {
            m_FileType = FileTypes::space;
        } else if (filepath.find(".yobj") != std::string::npos) {
            m_FileType = FileTypes::object;
        } else if (filepath.find(".ycfg") != std::string::npos) {
            m_FileType = FileTypes::config;
        } else {
            m_FileType = FileTypes::error;
        }

    }

    bool Lexer::Lex() {

        if (m_FileType == FileTypes::error) {
            m_ErrorHandler->SubmitError({ ErrorLevel::fatal , "Invalid File Type" , 0 , 0 });
            return false;
        }

        std::ifstream source_file(m_Tkn_data.filepath);
        if (!source_file.is_open()) {
            m_ErrorHandler->SubmitError({ ErrorLevel::fatal , "Could not open file: " + m_Tkn_data.filepath , 0 , 0 });
            m_Valid = false;
            return false;
        }
        source_file.close();

        if (!m_Tkn_data.state_stack.empty()) {
            std::cerr << "< Fatal Error | Lexer in an Unknown State >" << std::endl;
            return false;
        }

        InitialPass();
        if (!m_Valid) {
            std::cerr << "< Lex Aborted >\n";
            return false;
        } else {
            m_Valid = false;
        }
        // for (const auto& tkn : m_Tkn_data.raw_tokens) {
        //     PrintRawToken(tkn);
        // }

        if (m_FileType == FileTypes::source) {
            if (!LexSrcFile()) return false;
        } else if (m_FileType == FileTypes::project || m_FileType == FileTypes::build ||
                   m_FileType == FileTypes::space   || m_FileType == FileTypes::object) {
            if (!LexObjFile()) return false;
        } else if (m_FileType == FileTypes::config) {
            if (!LexCfgFile()) return false;
        } else {
            std::cerr << "< Fatal Error | Lexer in an Unknown State >" << std::endl;
            return false;
        }

        std::string value = "<EOF> -> " + m_Tkn_data.filepath;
        m_Tkn_data.tokens.push_back({ ylang::TknType::eof , m_Tkn_data.GetCurrRawTkn().line , m_Tkn_data.GetCurrRawTkn().col , value });

        if (!m_Tkn_data.valid) {
            std::cerr << "Lexer encountered unknown errors, aborting...\n";
            return false;
        } else {
            m_Valid = true;
        }
        
        for (const auto& tkn : m_Tkn_data.tokens) {
            PrintToken(tkn);
        }

        return true;
    }

}