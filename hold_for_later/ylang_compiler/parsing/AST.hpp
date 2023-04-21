#ifndef AST_HPP
#define AST_HPP

#include <memory>

#include "validator.hpp"

#include "llvm/IR/Value.h"

namespace ylang {

    class ASTNode;
    class PrototypeAST;
    class FunctionAST;

}

using ASTPtr = std::unique_ptr<ylang::ASTNode>;
using PrototypeASTPtr = std::unique_ptr<ylang::PrototypeAST>;
using FunctionASTPtr = std::unique_ptr<ylang::FunctionAST>;

namespace ylang {

    enum class ASTType {
        SOP ,

        EOP ,
        err
    };

    class ASTNode {
        public:
            ASTType m_Type = ASTType::err;

            virtual ~ASTNode() {}
            virtual llvm::Value* codegen() = 0;
    };

    class SOP : public ASTNode {
        public:
            SOP() { m_Type = ASTType::SOP; }
            ~SOP() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class EOPNode : public ASTNode {
        public:
            EOPNode() { m_Type = ASTType::EOP; }
            ~EOPNode() {}

            llvm::Value* codegen() override { return nullptr; }
    };
    
    class ImportAST : public ASTNode {
        Token m_Module;

        public:
            ImportAST(Token module) : m_Module(module) {}
            ~ImportAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class IntLiteralAST : public ASTNode {
        Token m_Token;

        public:
            IntLiteralAST(Token tkn) : m_Token(tkn) {}
            ~IntLiteralAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class CharLiteralAST : public ASTNode {
        Token m_Token;

        public:
            CharLiteralAST(Token tkn) : m_Token(tkn) {}
            ~CharLiteralAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class StringLiteralAST : public ASTNode {
        Token m_Token;

        public:
            StringLiteralAST(Token tkn) : m_Token(tkn) {}
            ~StringLiteralAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class VariableAST : public ASTNode {
        Token m_Token;

        public:
            VariableAST(Token tkn) : m_Token(tkn) {}
            ~VariableAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class BinaryOpAST : public ASTNode {
        Token m_Operator;
        ASTPtr m_LHS;
        ASTPtr m_RHS;

        public:
            BinaryOpAST(Token op , ASTPtr lhs , ASTPtr rhs) : m_Operator(op) , m_LHS(std::move(lhs)) , m_RHS(std::move(rhs)) {}
            ~BinaryOpAST() {}

            llvm::Value* codegen() override { return nullptr; }
    }; 

    class FuncCallAST : public ASTNode {
        Token m_Name;
        std::vector<ASTPtr> m_Args;

        public:
            FuncCallAST(Token name , std::vector<ASTPtr> args) : m_Name(name) , m_Args(std::move(args)) {}
            ~FuncCallAST() {}

            llvm::Value* codegen() override { return nullptr; }
    };

    class PrototypeAST {
        Token m_Name;
        std::vector<ASTPtr> m_Args;
        ASTPtr m_Body;

        public:
            PrototypeAST(Token name , std::vector<ASTPtr> args , ASTPtr body) : m_Name(name) , m_Args(std::move(args)) , m_Body(std::move(body)) {}
            ~PrototypeAST() {}

            llvm::Value* codegen() { return nullptr; }
    };

    class FunctionAST {
        PrototypeASTPtr m_Prototype;
        ASTPtr m_Body;

        public:
            FunctionAST(PrototypeASTPtr proto , ASTPtr body) : m_Prototype(std::move(proto)) , m_Body(std::move(body)) {}
            ~FunctionAST() {}

            llvm::Value* codegen() { return nullptr; }
    };

    // class

}

#endif