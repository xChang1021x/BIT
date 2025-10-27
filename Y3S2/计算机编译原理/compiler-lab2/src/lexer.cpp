#include "lexer.h"
#include <cctype>
#include <unordered_set>

namespace {
    const std::unordered_set<std::string> keywords = {"int", "return"};
    const std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "%", "=", "<", "<=", ">", ">=", "==", "!=", "&", "|", "^"
    };
}

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t pos = 0;

    auto skipWhitespace = [&]() {
        while (pos < input.size() && std::isspace(input[pos])) ++pos;
    };

    while (pos < input.size()) {
        skipWhitespace();
        if (pos >= input.size()) break;
        char ch = input[pos];

        if (std::isalpha(ch) || ch == '_') {
            size_t start = pos;
            while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '_')) ++pos;
            std::string word = input.substr(start, pos - start);
            if (keywords.count(word)) tokens.push_back({TokenType::Keyword, word});
            else tokens.push_back({TokenType::Identifier, word});
        } else if (std::isdigit(ch)) {
            size_t start = pos;
            while (pos < input.size() && std::isdigit(input[pos])) ++pos;
            tokens.push_back({TokenType::Number, input.substr(start, pos - start)});
        } else {
            bool matched = false;
            for (int len = 2; len >= 1 && pos + len <= input.size(); --len) {
                std::string op = input.substr(pos, len);
                if (operators.count(op)) {
                    tokens.push_back({TokenType::Operator, op});
                    pos += len;
                    matched = true;
                    break;
                }
            }
            if (matched) continue;

            // 单字符符号
            char c = input[pos++];
            TokenType type = TokenType::Unknown;
            if (c == ';') type = TokenType::Semicolon;
            else if (c == ',') type = TokenType::Comma;
            else if (c == '(') type = TokenType::LParen;
            else if (c == ')') type = TokenType::RParen;
            else if (c == '{') type = TokenType::LBrace;
            else if (c == '}') type = TokenType::RBrace;

            tokens.push_back({type, std::string(1, c)});
        }
    }

    tokens.push_back({TokenType::End, ""});
    return tokens;
}

