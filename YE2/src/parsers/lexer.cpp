#include "parsers/lexer.hpp"

namespace YE {
namespace parsing {
    
    void PrintToken(Token token) {
        std::string str1 = "Token: " + token.value + " ";
        size_t len1 = str1.size();

        std::string str2 = "| Type: ";
        switch (token.type) {
            case Token::Type::none: str2 += "none"; break;
            case Token::Type::identifier: str2 += "identifier"; break;
            case Token::Type::number: str2 += "number"; break;
            case Token::Type::string: str2 += "string"; break;
            case Token::Type::keyword: str2 += "keyword"; break;
            case Token::Type::op: str2 += "op"; break;
            case Token::Type::punctuation: str2 +=  "punctuation"; break;
            case Token::Type::func: str2 += "func"; break;
            case Token::Type::obj_param: str2 += "obj_param"; break;
        }

        size_t len2 = str2.size();

        int padding = 37 - static_cast<uint32_t>(len1);

        std::cout << str1;
        for (int i = 0; i < padding; i++) { std::cout << " "; }
        std::cout << str2;

        std::cout << std::endl;
    }

    std::vector<Token> LexTokens(const std::string& source) {
        std::vector<Token> tokens{};

        int index = 0;
        while (source[index] != '\0') {
            Token token{};
            
            if (IsAlpha(source[index])) {
                token.type = Token::Type::identifier;
                token.value += source[index];
                index++;
                while (IsAlphaNumeric(source[index])) {
                    token.value += source[index];
                    index++;
                }

                if (IsKeyword(token.value)) {
                    if (tokens.back().value.length() >= 2) {
                        if (tokens.back().value.substr(tokens.back().value.length() - 2 , 2) == "::") {
                            tokens.back().value += token.value;
                            continue;
                        }
                    }
                    token.type = Token::Type::keyword;
                } else if (IsBuiltInFunc(token.value)) {
                    token.type = Token::Type::func;
                } else {
                    token.type = Token::Type::identifier;
                }

                tokens.push_back(token);

            } else if (IsDigit(source[index])) {
                token.type = Token::Type::number;
                token.value += source[index];
                index++;
                while (IsDigit(source[index])) {
                    token.value += source[index];
                    index++;
                }

                tokens.push_back(token);

            } else if (IsOperator(source[index])) {
                
                // if (source[index] == '/' && index < source.size() - 1) {
                //     if (source[index + 1] == '/') {
                //         index += 2;
                //         while (source[index] != '\n') {

                //             if (index == source.size() - 1) {
                //                 std::cout << "LexTokens: Comment not closed!" << std::endl;
                //                 return std::vector<Token>{};
                //             }

                //             index++;
                //         }
                //         index++;
                //         continue;
                //     } else if (source[index + 1] == '*') {
                //         index += 2;
                //         while (source[index] != '*' && source[index + 1] != '/') {
                            
                //             if (index == source.size() - 1) {
                //                 std::cout << "LexTokens: Comment not closed!" << std::endl;
                //                 return std::vector<Token>{};
                //             }
                            
                //             index++;
                //         }
                //         index += 2;
                //         continue;
                //     }
                // }

                if (source[index] == '"') {
                    token.type = Token::Type::string;
                    index++;
                    while (source[index] != '"') {
                        token.value += source[index];
                        index++;
                    }
                    index++;
                    tokens.push_back(token);
                    continue;
                }

                if (source[index] == ':' && index < source.size() - 1) {
                    if (source[index + 1] == ':') {
                        tokens.back().value += "::";
                        index += 2;
                        continue;
                    }
                }

                token.type = Token::Type::op;
                token.value += source[index];
                index++;

                if (tokens.size() > 0) {
                    if (tokens.back().value.length() >= 2) {
                        if (tokens.back().value.substr(tokens.back().value.length() - 2 , 2) == "::" && token.value == "{") {
                            std::string temp = token.value;
                            while (index < source.length() && source[index] != ';') {
                                temp += source[index];
                                index++;
                            }

                            if (index == source.length() && temp[temp.length() - 1] != ';') {
                                std::cout << "LexTokens: Invalid Object Parameters\n";
                                return std::vector<Token>{};
                            } else {
                                temp += ';';
                                index++;
                                tokens.back().value += temp;
                                tokens.back().type = Token::Type::obj_param;
                            }
                            continue;
                        }
                    }
                }

                tokens.push_back(token);

            } else if (IsWhitespace(source[index])) {
                index++;
                while (IsWhitespace(source[index])) {
                    index++;
                }
            } else if (source[index] == '"') {
                token.type = Token::Type::string;
                index++;
                while (source[index] != '"') {
                    token.value += source[index];
                    index++;
                }
                index++;
            } else {
                token.type = Token::Type::none;
                token.value += source[index];
                index++;
            }

        }

        return tokens;
    }

}
}