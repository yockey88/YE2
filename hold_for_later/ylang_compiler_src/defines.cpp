#include "defines.hpp"

namespace ylang {

    void PrintRawToken(const RawTkn& tkn) {
        switch (tkn.type) {
            case RawTknType::sof: std::cout << "<SOF> -> "; break;
            case RawTknType::keyword: std::cout << "<Keyword> -> "; break;
            case RawTknType::i8_kw: std::cout << "<I8 kw> -> "; break;
            case RawTknType::i16_kw: std::cout << "<I16 kw> -> "; break;
            case RawTknType::i32_kw: std::cout << "<I32 kw> -> "; break;
            case RawTknType::i64_kw: std::cout << "<I64 kw> -> "; break;
            case RawTknType::u8_kw: std::cout << "<U8 kw> -> "; break;
            case RawTknType::u16_kw: std::cout << "<U16 kw> -> "; break;
            case RawTknType::u32_kw: std::cout << "<U32 kw> -> "; break;
            case RawTknType::u64_kw: std::cout << "<U64 kw> -> "; break;
            case RawTknType::f32_kw: std::cout << "<F32 kw> -> "; break;
            case RawTknType::f64_kw: std::cout << "<F64 kw> -> "; break;
            case RawTknType::bool_kw: std::cout << "<Bool kw> -> "; break;
            case RawTknType::char_kw: std::cout << "<Char kw> -> "; break;
            case RawTknType::string_kw: std::cout << "<String kw> -> "; break;
            case RawTknType::return_kw: std::cout << "<Return kw> -> "; break;
            case RawTknType::export_kw: std::cout << "<Export kw> -> "; break;
            case RawTknType::import_kw: std::cout << "<Import kw> -> "; break;
            case RawTknType::module_kw: std::cout << "<Module kw> -> "; break;
            case RawTknType::struct_kw: std::cout << "<Struct kw> -> "; break;
            case RawTknType::class_kw: std::cout << "<Class kw> -> "; break;
            case RawTknType::fn_kw: std::cout << "<Function kw> -> "; break;

            case RawTknType::proj_kw: std::cout << "<Project kw> -> "; break;
            case RawTknType::build_kw: std::cout << "<Build kw> -> "; break;
            case RawTknType::space_kw: std::cout << "<Space kw> -> "; break;
            case RawTknType::object_kw: std::cout << "<Object kw> -> "; break;
            case RawTknType::name_kw: std::cout << "<Name kw> -> "; break;
            case RawTknType::version_kw: std::cout << "<Version kw> -> "; break;
            case RawTknType::description_kw: std::cout << "<Description kw> -> "; break;
            case RawTknType::author_kw: std::cout << "<Author kw> -> "; break;
            case RawTknType::root_kw: std::cout << "<Root kw> -> "; break;
            case RawTknType::target_kw: std::cout << "<Target kw> -> "; break;
            case RawTknType::config_kw: std::cout << "<Config kw> -> "; break;
            case RawTknType::type_kw: std::cout << "<Type kw> -> "; break;
            case RawTknType::files_kw: std::cout << "<Files kw> -> "; break;
            case RawTknType::links_kw: std::cout << "<Links kw> -> "; break;
            case RawTknType::dependencies_kw: std::cout << "<Dependencies kw> -> "; break;
            case RawTknType::executable_kw: std::cout << "<Executable kw> -> "; break;
            case RawTknType::library_kw: std::cout << "<Library kw> -> "; break;
            case RawTknType::debug_kw: std::cout << "<Debug kw> -> "; break;
            case RawTknType::release_kw: std::cout << "<Release kw> -> "; break;

            case RawTknType::identifier: std::cout << "<Identifier> -> "; break;
            case RawTknType::op: std::cout << "<Operator> -> "; break;
            case RawTknType::add: std::cout << "<Add> -> "; break;
            case RawTknType::sub: std::cout << "<Subtract> -> "; break;
            case RawTknType::mul: std::cout << "<Multiply> -> "; break;
            case RawTknType::div: std::cout << "<Divide> -> "; break;
            case RawTknType::mod: std::cout << "<Modulus> -> "; break;
            case RawTknType::assign: std::cout << "<Assign> -> "; break;
            case RawTknType::add_assign: std::cout << "<Add Assign> -> "; break;
            case RawTknType::sub_assign: std::cout << "<Substract Assign> -> "; break;
            case RawTknType::mul_assign: std::cout << "<Multiply Assign> -> "; break;
            case RawTknType::div_assign: std::cout << "<Divide Assign> -> "; break;
            case RawTknType::mod_assign: std::cout << "<Modulus Assign> -> "; break;
            case RawTknType::exclamation: std::cout << "<Exclamation> -> "; break;
            case RawTknType::question: std::cout << "<Question> -> "; break;
            case RawTknType::dollar: std::cout << "<Dollar> -> "; break;
            case RawTknType::empty_paren: std::cout << "<Empty Paren> -> "; break;
            case RawTknType::empty_brace: std::cout << "<Empty Brace> -> "; break;
            case RawTknType::empty_bracket: std::cout << "<Empty Bracket> -> "; break;
            case RawTknType::eq: std::cout << "<Equal> -> "; break;
            case RawTknType::neq: std::cout << "<Not Equal> -> "; break;
            case RawTknType::lt: std::cout << "<Less Than> -> "; break;
            case RawTknType::gt: std::cout << "<Greater Than> -> "; break;
            case RawTknType::lte: std::cout << "<Less Than or Equal> -> "; break;
            case RawTknType::gte: std::cout << "<Greater Than or Equal> -> "; break;
            case RawTknType::arrow: std::cout << "<Arrow> -> "; break;
            case RawTknType::scope: std::cout << "<Scope> -> "; break;
            case RawTknType::punctuator: std::cout << "<Punctuator> -> "; break;
            case RawTknType::l_paren: std::cout << "<Left Parenthesis> -> "; break;
            case RawTknType::r_paren: std::cout << "<Right Parenthesis> -> "; break;
            case RawTknType::l_brace: std::cout << "<Left Brace> -> "; break;
            case RawTknType::r_brace: std::cout << "<Right Brace> -> "; break;
            case RawTknType::l_bracket: std::cout << "<Left Bracket> -> "; break;
            case RawTknType::r_bracket: std::cout << "<Right Bracket> -> "; break;
            case RawTknType::semicolon: std::cout << "<Semicolon> -> "; break;
            case RawTknType::comma: std::cout << "<Comma> -> "; break;
            case RawTknType::dot: std::cout << "<Dot> -> "; break;
            case RawTknType::quote: std::cout << "<Quote> -> "; break;
            case RawTknType::apostrophe: std::cout << "<Apostrophe> -> "; break;
            case RawTknType::colon: std::cout << "<Colon> -> "; break;
            case RawTknType::int_literal: std::cout << "<Integer Literal> -> "; break;
            case RawTknType::string_literal: std::cout << "<String Literal> -> "; break;
            case RawTknType::char_literal: std::cout << "<Character Literal> -> "; break;
            case RawTknType::whitespace: return;
            case RawTknType::eof: std::cout << "<EOF> -> "; break;
            case RawTknType::err: std::cerr << "<Error> -> "; break;
            // default: std::cerr << "<Error | Unknown Token Type>\n"; return;
        }
        
        std::cout << "< [" << tkn.value << "] | (" << tkn.line << " , " << tkn.col << ") >\n\n";
    }

    void PrintToken(const Token& tkn) {

        switch (tkn.type) {
            case TknType::sof: break;

            case TknType::i8_kw: std::cout << "< i8 kw > -> "; break;
            case TknType::i16_kw: std::cout << "< i16 kw > -> "; break;
            case TknType::i32_kw: std::cout << "< i32 kw > -> "; break;
            case TknType::i64_kw: std::cout << "< i64 kw > -> "; break;
            case TknType::u8_kw: std::cout << "< u8 kw > -> "; break;
            case TknType::u16_kw: std::cout << "< u16 kw > -> "; break;
            case TknType::u32_kw: std::cout << "< u32 kw > -> "; break;
            case TknType::u64_kw: std::cout << "< u64 kw > -> "; break;
            case TknType::f32_kw: std::cout << "< f32 kw > -> "; break;
            case TknType::f64_kw: std::cout << "< f64 kw > -> "; break;
            case TknType::bool_kw: std::cout << "< bool kw > -> "; break;
            case TknType::char_kw: std::cout << "< char kw > -> "; break;
            case TknType::string_kw: std::cout << "< string kw > -> "; break;
            case TknType::return_kw: std::cout << "< return kw > -> "; break;
            case TknType::export_kw: std::cout << "< export kw > -> "; break;
            case TknType::import_kw: std::cout << "< import kw > -> "; break;
            case TknType::module_kw: std::cout << "< module kw > -> "; break;
            case TknType::struct_kw: std::cout << "< struct kw > -> "; break;
            case TknType::class_kw: std::cout << "< class kw > -> "; break;
            case TknType::fn_kw: std::cout << "< function kw > -> "; break;

            case TknType::proj_kw: std::cout << "< project kw > -> "; break; 
            case TknType::build_kw: std::cout << "< build kw > -> "; break;
            case TknType::space_kw: std::cout << "< space kw > -> "; break;
            case TknType::object_kw: std::cout << "< object kw > -> "; break;
            case TknType::files_kw: std::cout << "< files kw > -> "; break;
            case TknType::name_kw: std::cout << "< name kw > -> "; break; 
            case TknType::version_kw: std::cout << "< version kw > -> "; break;
            case TknType::description_kw: std::cout << "< description kw > -> "; break;
            case TknType::author_kw: std::cout << "< author kw > -> "; break;
            case TknType::root_kw: std::cout << "< root kw > -> "; break;
            case TknType::target_kw: std::cout << "< target kw > -> "; break;
            case TknType::config_kw: std::cout << "< config kw > -> "; break;
            case TknType::type_kw: std::cout << "< type kw > -> "; break;
            case TknType::links_kw: std::cout << "< links kw > -> "; break;
            case TknType::dependencies_kw: std::cout << "< dependencies kw > -> "; break;
            case TknType::executable_kw: std::cout << "< executable kw > -> "; break;
            case TknType::library_kw: std::cout << "< library kw > -> "; break;
            case TknType::debug_kw: std::cout << "< debug kw > -> "; break;
            case TknType::release_kw: std::cout << "< release kw > -> "; break;

            case TknType::import_id: std::cout << "< import id > -> "; break;
            case TknType::module_id: std::cout << "< module id > -> "; break;
            case TknType::package_id: std::cout << "< package id > -> "; break;
            case TknType::struct_id: std::cout << "< struct id > -> "; break;
            case TknType::class_id: std::cout << "< class id > -> "; break;
            case TknType::fn_id: std::cout << "< fn id > -> "; break;
            case TknType::i8_id: std::cout << "< i8 id > -> "; break;
            case TknType::i16_id: std::cout << "< i16 id > -> "; break;
            case TknType::i32_id: std::cout << "< i32 id > -> "; break;
            case TknType::i64_id: std::cout << "< i64 id > -> "; break;
            case TknType::u8_id: std::cout << "< u8 id > -> "; break;
            case TknType::u16_id: std::cout << "< u16 id > -> "; break;
            case TknType::u32_id: std::cout << "< u32 id > -> "; break;
            case TknType::u64_id: std::cout << "< u64 id > -> "; break;
            case TknType::f32_id: std::cout << "< f32 id > -> "; break;
            case TknType::f64_id: std::cout << "< f64 id > -> "; break;
            case TknType::char_id: std::cout << "< char id > -> "; break;
            case TknType::string_id: std::cout << "< string id > -> "; break;
            case TknType::bool_id: std::cout << "< bool if > -> "; break;
            case TknType::export_id: std::cout << "< export id > -> "; break;
            case TknType::other_id: std::cout << "< other id > -> "; break;
            case TknType::fn_param_id: std::cout << "< fn param id > -> "; break;
            case TknType::fn_return_id: std::cout << "< fn return type id > -> "; break;
            case TknType::fn_call_id: std::cout << "< fn call id > -> "; break;
            case TknType::fn_call_param_id: std::cout << "< fn call param id > -> "; break;
            case TknType::var_assign_id: std::cout << "< var assign id > -> "; break;
            case TknType::var_assign_int: std::cout << "< var assign int > -> "; break;
            case TknType::var_assign_char: std::cout << "< var assign char > -> "; break;
            case TknType::var_assign_string: std::cout << "< var assign string > -> "; break;
            case TknType::var_assign_bool: std::cout << "< var assign bool > -> "; break;
            case TknType::captured_id: std::cout << "< captured id > -> "; break;
            case TknType::capture_dest_id: std::cout << "< capture dest id > -> "; break;
            case TknType::captured_fn_call: std::cout << "< captured fn call id > -> "; break;
            case TknType::scope_id: std::cout << "< scope id > -> "; break;

            case TknType::l_paren: std::cout << "< left parentheses > -> "; break;
            case TknType::r_paren: std::cout << "< right parentheses > -> "; break;
            case TknType::l_brace: std::cout << "< left brace > -> "; break;
            case TknType::r_brace: std::cout << "< right brace > -> "; break;
            case TknType::l_bracket: std::cout << "< left bracket > -> "; break;
            case TknType::r_bracket: std::cout << "< right bracket > -> "; break;
            case TknType::semi_colon: std::cout << "< semicolon > -> "; break;
            case TknType::comma: std::cout << "< comma > -> "; break;
            case TknType::dot: std::cout << "< dot > -> "; break;
            case TknType::quote: std::cout << "< quote > -> "; break;
            case TknType::colon: std::cout << "< colon > -> "; break;

            case TknType::assignment_op: std::cout << "< assignment op > -> "; break;
            case TknType::add_op: std::cout << "< add op > -> "; break;
            case TknType::sub_op: std::cout << "< sub op > -> "; break;
            case TknType::mul_op: std::cout << "< mul op > -> "; break;
            case TknType::div_op: std::cout << "< div op > -> "; break;
            case TknType::mod_op: std::cout << "< mod op > -> "; break;
            case TknType::exclamation_op: std::cout << "< exclamation op > -> "; break;
            case TknType::question_op: std::cout << "< question op > -> "; break;
            case TknType::dollar_op: std::cout << "< dollar op > -> "; break;
            case TknType::arrow_op: std::cout << "< arrow op > -> "; break;
            case TknType::eq_op: std::cout << "< eq op > -> "; break;
            case TknType::neq_op: std::cout << "< neq op > -> "; break;
            case TknType::lt_op: std::cout << "< lt op > -> "; break;
            case TknType::gt_op: std::cout << "< gt op > -> "; break;
            case TknType::leq_op: std::cout << "< lte op > -> "; break; 
            case TknType::geq_op: std::cout << "< gte op > -> "; break;
            case TknType::and_op: std::cout << "< and op > -> "; break;
            case TknType::or_op: std::cout << "< or op > -> "; break;
            case TknType::capture_op: std::cout << "< capture op > -> "; break;
            case TknType::inc_op: std::cout << "< inc op > -> "; break;
            case TknType::dec_op: std::cout << "< dec op > -> "; break;
            case TknType::add_assign_op: std::cout << "< add assign op > -> "; break;
            case TknType::sub_assign_op: std::cout << "< sub assign op > -> "; break;
            case TknType::mul_assign_op: std::cout << "< mul assign op > -> "; break;
            case TknType::div_assign_op: std::cout << "< div assign op > -> "; break;
            case TknType::mod_assign_op: std::cout << "< mod assign op > -> "; break;
            case TknType::scope_op: std::cout << "< scope op > -> "; break;

            case TknType::int_literal: std::cout << "< int literal > -> "; break;
            case TknType::string_literal: std::cout << "< string literal > -> "; break;
            case TknType::char_literal: std::cout << "< char literal > -> "; break;
            case TknType::float_literal: std::cout << "< float literal > -> "; break;
            case TknType::bool_literal: std::cout << "< bool literal > -> "; break;
            
            case TknType::fn_call: std::cout << "< fn call > -> "; break;
            case TknType::fn_call_param: std::cout << "< fn call param > -> "; break;
            case TknType::fn_param_type: std::cout << "< fn param type > -> "; break;
            
            case TknType::i8_fn_param: std::cout << "< i8 fn param > -> "; break;
            case TknType::i16_fn_param: std::cout << "< i16 fn param > -> "; break;
            case TknType::i32_fn_param: std::cout << "< i32 fn param > -> "; break;
            case TknType::i64_fn_param: std::cout << "< i64 fn param > -> "; break;
            case TknType::u8_fn_param: std::cout << "< u8 fn param > -> "; break;
            case TknType::u16_fn_param: std::cout << "< u16 fn param > -> "; break;
            case TknType::u32_fn_param: std::cout << "< u32 fn param > -> "; break;
            case TknType::u64_fn_param: std::cout << "< u64 fn param > -> "; break;
            case TknType::f32_fn_param: std::cout << "< f32 fn param > -> "; break;
            case TknType::f64_fn_param: std::cout << "< f64 fn param > -> "; break;
            case TknType::char_fn_param: std::cout << "< char fn param > -> "; break;
            case TknType::string_fn_param: std::cout << "< string fn param > -> "; break;
            case TknType::bool_fn_param: std::cout << "< bool fn param > -> "; break;
            case TknType::other_fn_param: std::cout << "< other fn param > -> "; break;
            case TknType::fn_call_param_int: std::cout << "< fn call int param > -> "; break; 
            case TknType::fn_call_param_char: std::cout << "< fn call char param > -> "; break;
            case TknType::fn_call_param_string: std::cout << "< fn call string param > -> "; break; 
            case TknType::fn_call_param_bool: std::cout << "< fn call bool param > -> "; break;
            case TknType::fn_call_param_other: std::cout << "< fn call int param > -> "; break;

            case TknType::int_fn_return: std::cout << "< i8 fn return > -> "; break;
            case TknType::i16_fn_return: std::cout << "< i16 fn return > -> "; break;
            case TknType::i32_fn_return: std::cout << "< i32 fn return > -> "; break;
            case TknType::i64_fn_return: std::cout << "< i64 fn return > -> "; break;
            case TknType::u8_fn_return: std::cout << "< u8 fn return > -> "; break;
            case TknType::u16_fn_return: std::cout << "< u16 fn return > -> "; break;
            case TknType::u32_fn_return: std::cout << "< u32 fn return > -> "; break;
            case TknType::u64_fn_return: std::cout << "< u64 fn return > -> "; break;
            case TknType::f32_fn_return: std::cout << "< f32 fn return > -> "; break;
            case TknType::char_fn_return: std::cout << "< f64 fn return > -> "; break;
            case TknType::string_fn_return: std::cout << "< string fn return > -> "; break;
            case TknType::bool_fn_return: std::cout << "< bool fn return > -> "; break;
            case TknType::other_fn_return: std::cout << "< other fn return > -> "; break;

            case TknType::i8_decl: std::cout << "< i8 decl > -> "; break;
            case TknType::i16_decl: std::cout << "< i16 decl > -> "; break;
            case TknType::i32_decl: std::cout << "< i32 decl > -> "; break;
            case TknType::i64_decl: std::cout << "< i64 decl > -> "; break;
            case TknType::u8_decl: std::cout << "< u8 decl > -> "; break;
            case TknType::u16_decl: std::cout << "< u16 decl > -> "; break;
            case TknType::u32_decl: std::cout << "< u32 decl > -> "; break;
            case TknType::u64_decl: std::cout << "< u64 decl > -> "; break;
            case TknType::f32_decl: std::cout << "< f32 decl > -> "; break;
            case TknType::f64_decl: std::cout << "< f64 decl > -> "; break;
            case TknType::char_decl: std::cout << "< char decl > -> "; break;
            case TknType::string_decl: std::cout << "< string decl > -> "; break;
            case TknType::bool_decl: std::cout << "< bool decl > -> "; break;
            case TknType::other_decl: std::cout << "< other decl > -> "; break;

            case TknType::eof: break;
            case TknType::err: return; break;

            default: std::cout << "< Error | Unknown token type >\n"; return; break;
        }

        std::cout << "< [" << tkn.value << "] | (" << tkn.line << " , " << tkn.col << ") >\n\n";

    }
    
    void PrintStatement(const Stmnt& stmnt) {
        switch (stmnt.type) {
            case StmntType::sof: std::cout << "< sof > -> "; break;
            case StmntType::import: std::cout << "< import stmnt > -> "; break;
            case StmntType::function_decl: std::cout << "< fn decl > -> "; break;
            case StmntType::function_defn: std::cout << "< fn defn > -> "; break;
            case StmntType::function_call: std::cout << "< fn call > -> "; break;
            case StmntType::function_capture: std::cout << "< function capture > -> "; break;
            case StmntType::proj_stmnt: std::cout << "< proj stmnt > -> "; break;
            case StmntType::build_stmnt: std::cout << "< build stmnt > -> "; break;
            case StmntType::space_stmnt: std::cout << "< space stmnt > -> "; break;
            case StmntType::object_stmnt: std::cout << "< object stmnt > -> "; break;
            case StmntType::eof: std::cout << "< eof > -> "; break;
            case StmntType::err: std::cout << "< error \n"; return; break;
        }

        std::cout << "< ";
        for (const auto& tkn : stmnt.tokens) {
            std::cout << tkn.value << " ";
        }
        std::cout << " >" << std::endl;
    }

    bool IsLiteral(const RawTknType& tkn) {
        return (tkn == RawTknType::int_literal || tkn == RawTknType::string_literal ||
                tkn == RawTknType::char_literal || tkn == RawTknType::bool_literal);
    }

    RawTknType IdentifyKeywordTkn(const std::string& tkn) {
        RawTknType type = RawTknType::err;

        if      (tkn == "import")                            { type = RawTknType::import_kw; }
        else if (tkn == "export")                            { type = RawTknType::export_kw; }
        else if (tkn == "module")                            { type = RawTknType::module_kw; }
        else if (tkn == "package")                           { type = RawTknType::package_kw; }
        else if (tkn == "struct")                            { type = RawTknType::struct_kw; }
        else if (tkn == "class")                             { type = RawTknType::class_kw; }
        else if (tkn == "fn")                                { type = RawTknType::fn_kw; }
        else if (tkn == "i8")                                { type = RawTknType::i8_kw; }
        else if (tkn == "i16")                               { type = RawTknType::i16_kw; }
        else if (tkn == "i32")                               { type = RawTknType::i32_kw; }
        else if (tkn == "i64")                               { type = RawTknType::i64_kw; }
        else if (tkn == "f32")                               { type = RawTknType::u8_kw; }
        else if (tkn == "f64")                               { type = RawTknType::u16_kw; }
        else if (tkn == "bool")                              { type = RawTknType::u32_kw; }
        else if (tkn == "char")                              { type = RawTknType::u64_kw; }
        else if (tkn == "string")                            { type = RawTknType::string_kw; }
        else if (tkn == "return")                            { type = RawTknType::return_kw; }            
        else if (tkn == "project")                           { type = RawTknType::proj_kw; } 
        else if (tkn == "build")                             { type = RawTknType::build_kw; }
        else if (tkn == "space")                             { type = RawTknType::space_kw; }
        else if (tkn == "files")                             { type = RawTknType::files_kw; }
        else if (tkn == "object")                            { type = RawTknType::object_kw; }
        else if (tkn == "name")                              { type = RawTknType::name_kw; } 
        else if (tkn == "version")                           { type = RawTknType::version_kw; }
        else if (tkn == "description")                       { type = RawTknType::description_kw; }
        else if (tkn == "author")                            { type = RawTknType::author_kw; }
        else if (tkn == "root")                              { type = RawTknType::root_kw; }
        else if (tkn == "target")                            { type = RawTknType::target_kw; }
        else if (tkn == "config")                            { type = RawTknType::config_kw; }
        else if (tkn == "type")                              { type = RawTknType::type_kw; }
        else if (tkn == "links")                             { type = RawTknType::links_kw; }
        else if (tkn == "dependencies")                      { type = RawTknType::dependencies_kw; }
        else if (tkn == "exe")                               { type = RawTknType::executable_kw; }
        else if (tkn == "lib")                               { type = RawTknType::library_kw; }
        else if (tkn == "debug")                             { type = RawTknType::debug_kw; }
        else if (tkn == "release")                           { type = RawTknType::release_kw; }
        else if (tkn == "true" || tkn == "false")            { type = RawTknType::keyword; }

        return type;
    }

    RawTknType IdentifyRawObjToken(const std::string& tkn) {
        RawTknType type = RawTknType::err;


        if      (tkn == "project")      { type = RawTknType::proj_kw; } 
        else if (tkn == "build")        { type = RawTknType::build_kw; }
        else if (tkn == "space")        { type = RawTknType::space_kw; }
        else if (tkn == "files")        { type = RawTknType::files_kw; }
        else if (tkn == "object")       { type = RawTknType::object_kw; }
        else if (tkn == "name")         { type = RawTknType::name_kw; } 
        else if (tkn == "version")      { type = RawTknType::version_kw; }
        else if (tkn == "description")  { type = RawTknType::description_kw; }
        else if (tkn == "author")       { type = RawTknType::author_kw; }
        else if (tkn == "root")         { type = RawTknType::root_kw; }
        else if (tkn == "target")       { type = RawTknType::target_kw; }
        else if (tkn == "config")       { type = RawTknType::config_kw; }
        else if (tkn == "type")         { type = RawTknType::type_kw; }
        else if (tkn == "links")        { type = RawTknType::links_kw; }
        else if (tkn == "dependencies") { type = RawTknType::dependencies_kw; }
        else if (tkn == "exe")          { type = RawTknType::executable_kw; }
        else if (tkn == "lib")          { type = RawTknType::library_kw; }
        else if (tkn == "debug")        { type = RawTknType::debug_kw; }
        else if (tkn == "release")      { type = RawTknType::release_kw; }

        return type;
    }

    RawTknType IdentifyRawOperator(const std::string& tkn) {
        RawTknType type = RawTknType::err;

        if      (tkn == "+")  { type = RawTknType::add; }
        else if (tkn == "-")  { type = RawTknType::sub; }
        else if (tkn == "*")  { type = RawTknType::mul; }
        else if (tkn == "/")  { type = RawTknType::div; }
        else if (tkn == "%")  { type = RawTknType::mod; }
        else if (tkn == "=")  { type = RawTknType::assign; }
        else if (tkn == "+=") { type = RawTknType::add_assign; }
        else if (tkn == "-=") { type = RawTknType::sub_assign; }
        else if (tkn == "*=") { type = RawTknType::mul_assign; }
        else if (tkn == "/=") { type = RawTknType::div_assign; }
        else if (tkn == "%=") { type = RawTknType::mod_assign; }
        else if (tkn == "==") { type = RawTknType::eq; }
        else if (tkn == "!=") { type = RawTknType::neq; }
        else if (tkn == "<")  { type = RawTknType::lt; }
        else if (tkn == ">")  { type = RawTknType::gt; }
        else if (tkn == "<=") { type = RawTknType::lte; }
        else if (tkn == ">=") { type = RawTknType::gte; }
        else if (tkn == "()") { type = RawTknType::empty_paren; }
        else if (tkn == "{}") { type = RawTknType::empty_brace; }
        else if (tkn == "[]") { type = RawTknType::empty_bracket; }
        else if (tkn == "!")  { type = RawTknType::exclamation; }
        else if (tkn == "?")  { type = RawTknType::question; }
        else if (tkn == "$")  { type = RawTknType::dollar; }
        else if (tkn == "->") { type = RawTknType::arrow; }
        else if (tkn == "=>") { type = RawTknType::arrow; }
        else if (tkn == "::") { type = RawTknType::scope; }
        else if (tkn == "\"") { type = RawTknType::quote; }
        else if (tkn == "'") { type = RawTknType::apostrophe; }

        return type;
    }
    
    RawTknType IdentifyRawPunctuator(const std::string& tkn) {
        if (tkn.length() > 1) { return RawTknType::err; }

        RawTknType type = RawTknType::err;

        switch (tkn[0]) {
            case '(':  type = RawTknType::l_paren; break;
            case ')':  type = RawTknType::r_paren; break;
            case '{':  type = RawTknType::l_brace; break;
            case '}':  type = RawTknType::r_brace; break;
            case '[':  type = RawTknType::l_bracket; break;
            case ']':  type = RawTknType::r_bracket; break;
            case ';':  type = RawTknType::semicolon; break;
            case ',':  type = RawTknType::comma; break;
            case '.':  type = RawTknType::dot; break;
            case '"': type = RawTknType::quote; break;
            case '\'': type = RawTknType::apostrophe; break;
            case ':':  type = RawTknType::colon; break;
            case '!':  type = RawTknType::exclamation; break;
            case '?':  type = RawTknType::question; break;
            case '$':  type = RawTknType::dollar; break;
            case '+':  type = RawTknType::add; break;
            case '-':  type = RawTknType::sub; break;
            case '*':  type = RawTknType::mul; break;
            case '/':  type = RawTknType::div; break;
            case '%':  type = RawTknType::mod; break;
            case '=':  type = RawTknType::assign; break;
            default: return RawTknType::err; break;
        }

        return type;
    }
    
    TknType IdentifyKeywordTkn(const RawTkn& tkn) {
        TknType type = TknType::err;

        if      (tkn.value == "import")                            { type = TknType::import_kw; }
        else if (tkn.value == "export")                            { type = TknType::export_kw; }
        else if (tkn.value == "module")                            { type = TknType::module_kw; }
        else if (tkn.value == "package")                           { type = TknType::package_kw; }
        else if (tkn.value == "struct")                            { type = TknType::struct_kw; }
        else if (tkn.value == "class")                             { type = TknType::class_kw; }
        else if (tkn.value == "fn")                                { type = TknType::fn_kw; }
        else if (tkn.value == "i8")                                { type = TknType::i8_kw; }
        else if (tkn.value == "i16")                               { type = TknType::i16_kw; }
        else if (tkn.value == "i32")                               { type = TknType::i32_kw; }
        else if (tkn.value == "i64")                               { type = TknType::i64_kw; }
        else if (tkn.value == "f32")                               { type = TknType::f32_kw; }
        else if (tkn.value == "f64")                               { type = TknType::f64_kw; }
        else if (tkn.value == "bool")                              { type = TknType::bool_kw; }
        else if (tkn.value == "char")                              { type = TknType::char_kw; }
        else if (tkn.value == "string")                            { type = TknType::string_kw; }
        else if (tkn.value == "return")                            { type = TknType::return_kw; }
        else if (tkn.value == "true" || tkn.value == "false")      { type = TknType::bool_literal; }

        return type;
    }

    TknType IdentifyFuncParamType(const RawTkn& tkn) {
        TknType type = TknType::err;

        if      (tkn.type == RawTknType::i8_kw)     { type = TknType::i8_fn_param; }
        else if (tkn.type == RawTknType::i16_kw)    { type = TknType::i16_fn_param; }
        else if (tkn.type == RawTknType::i32_kw)    { type = TknType::i32_fn_param; }
        else if (tkn.type == RawTknType::i64_kw)    { type = TknType::i64_fn_param; }
        else if (tkn.type == RawTknType::u8_kw)     { type = TknType::u8_fn_param; }
        else if (tkn.type == RawTknType::u16_kw)    { type = TknType::u16_fn_param; }
        else if (tkn.type == RawTknType::u32_kw)    { type = TknType::u32_fn_param; }
        else if (tkn.type == RawTknType::u64_kw)    { type = TknType::u64_fn_param; }
        else if (tkn.type == RawTknType::f32_kw)    { type = TknType::f32_fn_param; }
        else if (tkn.type == RawTknType::f64_kw)    { type = TknType::f64_fn_param; }
        else if (tkn.type == RawTknType::char_kw)   { type = TknType::char_fn_param; }
        else if (tkn.type == RawTknType::string_kw) { type = TknType::string_fn_param; }
        else if (tkn.type == RawTknType::bool_kw)   { type = TknType::bool_fn_param; }

        return type;
    }

    TknType IdentifyFuncReturnType(const RawTkn& tkn) {
        TknType type = TknType::err;

        if      (tkn.value == "i8")     { type = TknType::i8_fn_return; }
        else if (tkn.value == "i16")    { type = TknType::i16_fn_return; }
        else if (tkn.value == "i32")    { type = TknType::i32_fn_return; }
        else if (tkn.value == "i64")    { type = TknType::i64_fn_return; }
        else if (tkn.value == "u8")     { type = TknType::u8_fn_return; }
        else if (tkn.value == "u16")    { type = TknType::u16_fn_return; }
        else if (tkn.value == "u32")    { type = TknType::u32_fn_return; }
        else if (tkn.value == "u62")    { type = TknType::u64_fn_return; }
        else if (tkn.value == "f32")    { type = TknType::f32_fn_return; }
        else if (tkn.value == "f64")    { type = TknType::f64_fn_return; }
        else if (tkn.value == "string") { type = TknType::string_fn_return; }
        else if (tkn.value == "char")   { type = TknType::char_fn_return; }
        else if (tkn.value == "bool")   { type = TknType::bool_fn_return; }

        return type;
    }
    
    TknType IdentifyFuncRetIdType(const RawTknType& tkn) {
        TknType type = TknType::err;

        if      (tkn == RawTknType::int_literal)    { type = TknType::i32_fn_return; }
        else if (tkn == RawTknType::string_literal) { type = TknType::string_fn_return; }
        else if (tkn == RawTknType::char_literal)   { type = TknType::char_fn_return; }
        else if (tkn == RawTknType::bool_literal)   { type = TknType::bool_fn_return; }
        
        return type;
    }

    TknType IdentifyVariableTypeTkn(const RawTkn& tkn) {
        TknType type = TknType::err;

        if      (tkn.value == "i8")     { type = TknType::i8_decl; }
        else if (tkn.value == "i16")    { type = TknType::i16_decl; }
        else if (tkn.value == "i32")    { type = TknType::i32_decl; }
        else if (tkn.value == "i64")    { type = TknType::i64_decl; }
        else if (tkn.value == "u8")     { type = TknType::u8_decl; }
        else if (tkn.value == "u16")    { type = TknType::u16_decl; }
        else if (tkn.value == "u32")    { type = TknType::u32_decl; }
        else if (tkn.value == "u62")    { type = TknType::u64_decl; }
        else if (tkn.value == "f32")    { type = TknType::f32_decl; }
        else if (tkn.value == "f64")    { type = TknType::f64_decl; }
        else if (tkn.value == "char")   { type = TknType::char_decl; }
        else if (tkn.value == "string") { type = TknType::string_decl; }
        else if (tkn.value == "bool")   { type = TknType::bool_decl; }
        
        return type;
    }
    
    TknType IdentifyVarIdTypeTkn(const TknType& tkn) {
        TknType type = TknType::err;

        if      (tkn == TknType::i8_decl)     { type = TknType::i8_id; }
        else if (tkn == TknType::i16_decl)    { type = TknType::i16_id; }
        else if (tkn == TknType::i32_decl)    { type = TknType::i32_id; }
        else if (tkn == TknType::i64_decl)    { type = TknType::i64_id; }
        else if (tkn == TknType::u8_decl)     { type = TknType::u8_id; }
        else if (tkn == TknType::u16_decl)    { type = TknType::u16_id; }
        else if (tkn == TknType::u32_decl)    { type = TknType::u32_id; }
        else if (tkn == TknType::u64_decl)    { type = TknType::u64_id; }
        else if (tkn == TknType::f32_decl)    { type = TknType::f32_id; }
        else if (tkn == TknType::f64_decl)    { type = TknType::f64_id; }
        else if (tkn == TknType::char_decl)   { type = TknType::char_id; }
        else if (tkn == TknType::string_decl) { type = TknType::string_id; }
        else if (tkn == TknType::bool_decl)   { type = TknType::bool_id; }
        
        return type;
    }

    TknType IdentifyOperatorToken(const RawTkn& rt) {
        TknType type = TknType::err;

        if      (rt.value == "=")   { type = TknType::assignment_op; }
        else if (rt.value == "+")   { type = TknType::add_op; }
        else if (rt.value == "-")   { type = TknType::sub_op; }
        else if (rt.value == "*")   { type = TknType::mul_op; }
        else if (rt.value == "/")   { type = TknType::div_op; }
        else if (rt.value == "%")   { type = TknType::mod_op; }
        else if (rt.value == "!")   { type = TknType::exclamation_op; }
        else if (rt.value == "?")   { type = TknType::question_op; }
        else if (rt.value == "$")   { type = TknType::dollar_op; }
        else if (rt.value == "->")  { type = TknType::arrow_op; }
        else if (rt.value == "=>")  { type = TknType::arrow_op; }
        else if (rt.value == "==")  { type = TknType::eq_op; }
        else if (rt.value == "!=")  { type = TknType::neq_op; }
        else if (rt.value == "<")   { type = TknType::lt_op; }
        else if (rt.value == ">")   { type = TknType::gt_op; }
        else if (rt.value == ">=")  { type = TknType::geq_op; }
        else if (rt.value == "<=")  { type = TknType::leq_op; }
        else if (rt.value == "&&")  { type = TknType::and_op; }
        else if (rt.value == "||")  { type = TknType::or_op; }
        else if (rt.value == "$>")  { type = TknType::capture_op; }
        else if (rt.value == "++")  { type = TknType::inc_op; }
        else if (rt.value == "--")  { type = TknType::dec_op; }
        else if (rt.value == "+=")  { type = TknType::add_assign_op; }
        else if (rt.value == "-=")  { type = TknType::sub_assign_op; }
        else if (rt.value == "*=")  { type = TknType::mul_assign_op; }
        else if (rt.value == "/=")  { type = TknType::div_assign_op; }
        else if (rt.value == "%=")  { type = TknType::mod_assign_op; }
        else if (rt.value == "::")  { type = TknType::scope_op; }
        else if (rt.value == ";")   { type = TknType::semi_colon; }

        return type;
    }

    TknType IdentifyPunctuatorToken(const RawTkn& rt) {
        TknType type = TknType::err;

        switch (rt.value[0]) {
            case '(':  type = TknType::l_paren;  break;
            case ')':  type = TknType::r_paren;  break;
            case '{':  type = TknType::l_brace; break;
            case '}':  type = TknType::r_brace; break;
            case '[':  type = TknType::l_bracket; break;
            case ']':  type = TknType::r_bracket; break;
            case ';':  type = TknType::semi_colon;  break;
            case ',':  type = TknType::comma; break;
            case '.':  type = TknType::dot;  break;
            case '"':  type = TknType::quote;  break;
            case '\'': type = TknType::apostrophe; break;
            case ':':  type = TknType::colon;  break;
            default:   return TknType::err;
        }

        return type;
    }
    
    TknType IdentifyIdentifierToken(TknType type , const RawTkn& tkn) {
        TknType id_type = TknType::err;

        switch (type) {
            case TknType::struct_kw:  type = TknType::struct_id; break;
            case TknType::class_kw:   type = TknType::class_id; break;
            case TknType::import_kw:  type = TknType::import_id; break;
            case TknType::export_kw:  type = TknType::export_id; break;
            case TknType::package_kw: type = TknType::package_id; break;
            default: return TknType::err;
        }

        return id_type;

    }

    TknType IdentifyObjToken(const RawTkn& tkn) {
        TknType type = TknType::err;

        if      (tkn.value == "space")        { type = TknType::space_kw; } 
        else if (tkn.value == "project")      { type = TknType::proj_kw; } 
        else if (tkn.value == "build")        { type = TknType::build_kw; }
        else if (tkn.value == "space")        { type = TknType::space_kw; }
        else if (tkn.value == "files")        { type = TknType::files_kw; }
        else if (tkn.value == "object")       { type = TknType::object_kw; }
        else if (tkn.value == "name")         { type = TknType::name_kw; } 
        else if (tkn.value == "version")      { type = TknType::version_kw; }
        else if (tkn.value == "description")  { type = TknType::description_kw; }
        else if (tkn.value == "author")       { type = TknType::author_kw; }
        else if (tkn.value == "root")         { type = TknType::root_kw; }
        else if (tkn.value == "target")       { type = TknType::target_kw; }
        else if (tkn.value == "config")       { type = TknType::config_kw; }
        else if (tkn.value == "type")         { type = TknType::type_kw; }
        else if (tkn.value == "links")        { type = TknType::links_kw; }
        else if (tkn.value == "dependencies") { type = TknType::dependencies_kw; }
        else if (tkn.value == "exe")          { type = TknType::executable_kw; }
        else if (tkn.value == "lib")          { type = TknType::library_kw; }
        else if (tkn.value == "debug")        { type = TknType::debug_kw; }
        else if (tkn.value == "release")      { type = TknType::release_kw; }

        return type;
    }

}