#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>

enum class TokenType {
    Keyword,
    Identifier,
    Number,
    Operator,
    Punctuation,
    Comma,
    Semicolon,
    LParen,
    RParen,
    LBrace,
    RBrace,
    End,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;

    std::string toString() const {
        std::string typeStr;
        switch (type) {
            case TokenType::Keyword: typeStr = "Keyword"; break;
            case TokenType::Identifier: typeStr = "Identifier"; break;
            case TokenType::Number: typeStr = "Number"; break;
            case TokenType::Operator: typeStr = "Operator"; break;
            case TokenType::Punctuation: typeStr = "Punctuation"; break;
            case TokenType::Comma: typeStr = "Comma"; break;
            case TokenType::Semicolon: typeStr = "Semicolon"; break;
            case TokenType::LParen: typeStr = "LParen"; break;
            case TokenType::RParen: typeStr = "RParen"; break;
            case TokenType::LBrace: typeStr = "LBrace"; break;
            case TokenType::RBrace: typeStr = "RBrace"; break;
            case TokenType::End: typeStr = "End"; break;
            default: typeStr = "Unknown";
        }
        return typeStr + ": " + value;
    }
};

std::vector<Token> tokenize(const std::string& input);

#endif
