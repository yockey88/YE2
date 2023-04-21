#ifndef DEFINES_HPP
#define DEFINES_HPP

#include "errors.hpp"

#define UNIMPLIMENTED std::cout << "< Unimplimented Function> -> " << __FUNCTION__ << "\n\t"; assert(false);

const std::vector<char> punctuators = {
    '(' , ')' , '{' , '}' , '[' , ']' ,
    ';' , ',' , '.' , '"' , '\'' , ':' ,
    '$' 
};

const std::vector<std::string> operators = {
    "=" , "+" , "-" , "*" , "/" , "%" ,
    "!" , "?" , "$" ,
    "==" , "!=" , "<" , ">" , "<=" , ">=" ,
    "&&" , "||" , "#!" , "$>" , "++" , "--" ,
    "+=" , "-=" , "*=" , "/=" , "%=" ,
    "::" , "->"
};

const std::vector<std::string> keywords = {
    "i8" , "i16" , "i32" , "i64" , 
    "u8" , "u16" , "u32" , "u64" ,
    "f32" , "f64" , "char" , "string" , 
    "bool" , 

    "true" , "false" , 
    
    "return" ,

    "export" , "import" , "package" , 

    "enum" , "struct" , "class" , 
    "fn" , 

    "project" , "build" , "space" , "object" ,
    "name" , "version" , "description" , 
    "author" , 

    "root" , "target" , "config" , "type" ,
    "files" , "links" , "dependencies" ,
    
    "exe" , "lib" , 
    "debug" , "release" ,
};

const std::vector<std::string> type_keywords = {
    "i8" , "i16" , "i32" , "i64" , 
    "u8" , "u16" , "u32" , "u64" ,
    "f32" , "f64" , "char" , "string" , 
    "bool" , 
};

const std::vector<std::string> keywords_requires_identifier = {
    "enum" , "struct" , "class" , 
    "fn"
};

const std::vector<std::string> control_keywords = {
    "return" , "import"
};

const std::vector<std::string> obj_file_keywords = {
    "project" , "build" , "space" , "object" ,
     
    "config" , "window" , 

    "name" , "version" , "description" , 
    "author" , 

    "root" , "target" , "build" , "config" , "type" ,
    "files" , "links" , "dependencies" ,
    
    "exe" , "library" , 
    "debug" , "release" ,
};

inline bool IsNumeric(char c) { return (c >= '0' && c <= '9'); }
inline bool IsAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
inline bool IsAlphaNumeric(char c) { return (IsAlpha(c) || IsNumeric(c) || c == '_'); }

inline bool IsSymbol(char c) { return  (((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
                                        (c >= '[' && c <= '`') || (c >= '{' && c <= '~') && c != '_')); }
inline bool IsWhiteSpace(char c) { return (c == ' '); }
inline bool IsTab(char c) { return (c == '\t'); }
inline bool IsFormFeed(char c) { return (c == '\f'); }
inline bool IsVerticaltab(char c) { return (c == '\v'); }
inline bool IsEndOfLine(char c) { return (c == '\n'); }

inline bool IsPunctuator(char c) { return (std::find(punctuators.begin() , punctuators.end() , c) != punctuators.end()); }

inline bool IsKeyword(const std::string& str) { return (std::find(keywords.begin() , keywords.end() , str) != keywords.end()); }
inline bool IsObjectKeyword(const std::string& str) { return (std::find(obj_file_keywords.begin() , obj_file_keywords.end() , str) != obj_file_keywords.end()); }
inline bool IsOperator(const std::string& str) { return (std::find(operators.begin() , operators.end() , str) != operators.end()); } 

inline bool IsTypeKeyword(const std::string& str) { return (std::find(type_keywords.begin() , type_keywords.end() , str) != type_keywords.end()); }
inline bool IsControlKeyword(const std::string& str) { return (std::find(control_keywords.begin() , control_keywords.end() , str) != control_keywords.end()); } 

inline bool KeywordRequiresIdentifier(const std::string& keyword) { 
    return (std::find(keywords_requires_identifier.begin() , keywords_requires_identifier.end() , keyword) != keywords_requires_identifier.end());
}

namespace ylang {

    struct InitialPassData;
    struct TokenizationData;
    struct StmntList;

    /* TODO :===> 
        $> figure out hot give initial pass more detail
        $> add in errors and syntax checks on first pass
    */
    // raw_fn_id , 
    // raw_class_id , raw_struct_id , raw_enum_id , raw_package_id , raw_import_id ,
    enum class RawTknType {
        sof , 

        keyword ,
            i8_kw ,
            i16_kw ,
            i32_kw ,
            i64_kw ,
            u8_kw ,
            u16_kw ,
            u32_kw ,
            u64_kw ,
            f32_kw ,
            f64_kw ,
            char_kw ,
            string_kw ,
            bool_kw ,
            return_kw ,
            export_kw ,
            import_kw ,
            module_kw ,
            package_kw ,
            struct_kw ,
            class_kw ,
            fn_kw ,

            // obj file keywords
            proj_kw , 
            build_kw ,
            space_kw ,
            object_kw ,
            files_kw ,
            name_kw , 
            version_kw ,
            description_kw ,
            author_kw ,
            root_kw ,
            target_kw ,
            config_kw ,
            type_kw ,
            links_kw , 
            dependencies_kw ,
            executable_kw ,
            library_kw ,
            debug_kw ,
            release_kw ,
            // end obj file keywords
        
        identifier ,

        op ,
            add , sub , mul , div , mod ,
            assign , add_assign , sub_assign , mul_assign , div_assign , mod_assign ,
            exclamation , question , dollar ,
            empty_paren , empty_brace , empty_bracket ,
            eq , neq , lt , gt , lte , gte ,
            arrow , scope ,
        punctuator , 
            l_paren , r_paren , l_brace , r_brace , l_bracket , r_bracket ,
            semicolon , comma , dot , quote , apostrophe , colon ,
        
        int_literal , string_literal , char_literal ,
        bool_literal ,

        whitespace , // comment , 
    
        eof , err
    };

    enum class TknType {
        sof , 

        i8_kw ,
        i16_kw ,
        i32_kw ,
        i64_kw ,
        u8_kw ,
        u16_kw ,
        u32_kw ,
        u64_kw ,
        f32_kw ,
        f64_kw ,
        char_kw ,
        string_kw ,
        bool_kw ,
        
        return_kw ,
        export_kw ,
        import_kw ,
        module_kw ,
        package_kw ,
        struct_kw ,
        class_kw ,
        fn_kw ,

        fn_id ,
        i8_id ,
        i16_id ,
        i32_id ,
        i64_id ,
        u8_id ,
        u16_id ,
        u32_id ,
        u64_id ,
        f32_id ,
        f64_id ,
        char_id ,
        string_id ,
        bool_id ,
        export_id ,
        other_id ,
        fn_param_id ,
        fn_return_id ,
        fn_call_id ,
        fn_call_param_id ,
        var_assign_id ,
        var_assign_int ,
        var_assign_char ,
        var_assign_string ,
        var_assign_bool ,
        captured_id ,
        capture_dest_id , 
        captured_fn_call ,
        scope_id ,

        import_id ,
        module_id ,
        package_id ,
        struct_id ,
        class_id ,

        fn_tag_id , 

        l_paren ,
        r_paren ,
        l_brace ,
        r_brace ,
        l_bracket ,
        r_bracket , 
        semi_colon ,
        comma ,
        dot ,
        quote ,
        apostrophe ,
        colon ,

        assignment_op ,
        add_op ,
        sub_op ,
        mul_op ,
        div_op ,
        mod_op ,
        exclamation_op ,
        question_op ,
        dollar_op ,
        arrow_op ,
        eq_op ,
        neq_op ,
        lt_op ,
        gt_op ,
        leq_op ,
        geq_op , 
        and_op ,
        or_op ,
        capture_op ,
        inc_op ,
        dec_op ,
        add_assign_op ,
        sub_assign_op ,
        mul_assign_op ,
        div_assign_op ,
        mod_assign_op ,
        scope_op ,

        int_literal ,
        string_literal ,
        char_literal , 
        float_literal ,
        bool_literal ,
 
        fn_call ,
        fn_call_param ,
        fn_param_type ,

        i8_fn_param ,
        i16_fn_param ,
        i32_fn_param ,
        i64_fn_param ,
        u8_fn_param ,
        u16_fn_param ,
        u32_fn_param ,
        u64_fn_param ,
        f32_fn_param , 
        f64_fn_param ,
        char_fn_param ,
        string_fn_param ,
        bool_fn_param ,
        other_fn_param ,
        fn_call_param_int , 
        fn_call_param_char ,
        fn_call_param_string , 
        fn_call_param_bool , 
        fn_call_param_other ,

        int_fn_return ,
        i8_fn_return ,
        i16_fn_return ,
        i32_fn_return ,
        i64_fn_return ,
        u8_fn_return ,
        u16_fn_return ,
        u32_fn_return ,
        u64_fn_return ,
        f32_fn_return ,
        f64_fn_return ,
        char_fn_return ,
        string_fn_return ,
        bool_fn_return ,
        other_fn_return ,

        i8_decl ,
        i16_decl ,
        i32_decl ,
        i64_decl ,
        u8_decl ,
        u16_decl ,
        u32_decl ,
        u64_decl ,
        f32_decl ,
        f64_decl ,
        char_decl ,
        string_decl ,
        bool_decl ,
        other_decl ,

        // beginning of obj-file-specific tokens
        proj_kw , 
        build_kw ,
        space_kw ,
        object_kw ,
        files_kw ,
        name_kw , 
        version_kw ,
        description_kw ,
        author_kw ,
        root_kw ,
        target_kw ,
        config_kw ,
        type_kw ,
        links_kw ,
        dependencies_kw ,
        executable_kw ,
        library_kw ,
        debug_kw ,
        release_kw ,
        // end opf obj-file-specific tokens
        
        proj_name , 
        proj_version_num ,
        proj_description ,
        proj_author ,
        proj_root_dir , 
        proj_build_dir ,
        proj_config , 
        proj_type ,

        build_name , 
        build_version_num , 
        build_description ,
        build_author ,
        build_dir ,

        space_name ,
        space_version_num ,
        space_description ,
        space_author ,
        space_dir , 

        file_id ,  

        eof , err ,
    };

    enum class StmntType {
        sof , 

        import , 

        function_decl ,
        function_defn ,
        function_call ,
        function_capture , 

        // object statements
        proj_stmnt , 
        build_stmnt ,
        space_stmnt ,
        object_stmnt ,

        eof , err
    };

    struct RawTkn {
        RawTknType type = RawTknType::err;
        int line = 0 , col = 0;
        bool retokenized = false;
        std::string value = "[< BLANK >]";

        RawTkn() : type(RawTknType::err) , line(-1) , col(-1) , value("<!>") {}
        RawTkn(RawTknType type, std::string value) : type(type) , line(-1) , col(-1) , value(value) {}
        RawTkn(RawTknType type, int line, int col, std::string value) : type(type) , line(line) , col(col) , value(value) {}
    };
     
    struct Token {
        TknType type = TknType::err;
        int line = 0 , col = 0;
        std::string value = "<!>";

        Token() : type(TknType::err) , line(-1) , col(-1) , value("<!>") {}
        Token(TknType type, std::string value) : type(type) , line(-1) , col(-1) , value(value) {}
        Token(TknType type, int line, int col, std::string value) : type(type) , line(line) , col(col) , value(value) {}
    };

    struct Stmnt {
        StmntType type = StmntType::err;
        std::vector<Token> tokens;

        Stmnt() : type(StmntType::err) {}
        Stmnt(StmntType type) : type(type) {}
        Stmnt(StmntType type, std::vector<Token> tokens) : type(type) , tokens(tokens) {}
    };

} 

typedef void(*InitialPassState)(ylang::InitialPassData* state_data);
typedef void(*TokenizerState)(ylang::TokenizationData* state_data , ylang::ErrorHandler* error_handler);
typedef void(*FilterState)(ylang::StmntList* state_data , ylang::ErrorHandler* error_handler);

namespace ylang {

    void PrintRawToken(const RawTkn& tkn);
    void PrintToken(const Token& tkn);
    void PrintStatement(const Stmnt& stmnt);

    bool IsLiteral(const RawTknType& tkn);

    RawTknType IdentifyKeywordTkn(const std::string& tkn);
    RawTknType IdentifyRawObjToken(const std::string& tkn);

    RawTknType IdentifyRawOperator(const std::string& tkn);
    RawTknType IdentifyRawPunctuator(const std::string& tkn);

    TknType IdentifyKeywordTkn(const RawTkn& tkn);
    TknType IdentifyFuncParamType(const RawTkn& tkn);
    TknType IdentifyFuncReturnType(const RawTkn& tkn);
    TknType IdentifyFuncRetIdType(const RawTknType& tkn);
    TknType IdentifyVariableTypeTkn(const RawTkn& tkn);
    TknType IdentifyVarIdTypeTkn(const TknType& tkn);

    TknType IdentifyOperatorToken(const RawTkn& tkn);
    TknType IdentifyPunctuatorToken(const RawTkn& tkn);
    TknType IdentifyIdentifierToken(TknType type , const RawTkn& tkn);

    TknType IdentifyObjToken(const RawTkn& tkn);

}

#endif