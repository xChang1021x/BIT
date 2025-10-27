#include "parser.h"
#include <stdexcept>

static size_t pos = 0;
static std::vector<Token> toks;
static std::shared_ptr<ASTNode> parseExpression();

static const Token& current() {
    if (pos < toks.size()) return toks[pos];
    static Token dummy{TokenType::End, ""};
    return dummy;
}

static const Token& advance() { return toks[pos++]; }

static bool match(TokenType type) {
    if (current().type == type) { advance(); return true; }
    return false;
}

static void expect(TokenType type, const std::string& hint = "") {
    if (!match(type)) {
        throw std::runtime_error("Expected token type " + std::to_string((int)type) +
                                 " but got " + current().value +
                                 (hint.empty() ? "" : (" - " + hint)));
    }
}

// 支持简单二元表达式，如 a + b, 3 * c 等// 优先级表（越大优先级越高）
int getPrecedence(const std::string& op) {
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// 解析基本单元：数字、变量、括号表达式
static std::shared_ptr<ASTNode> parsePrimary() {
    if (current().type == TokenType::Number) {
        auto node = std::make_shared<ASTNode>(NodeType::Constant, current().value);
        advance();
        return node;
    }
    if (current().type == TokenType::Identifier) {
        auto node = std::make_shared<ASTNode>(NodeType::Variable, current().value);
        advance();
        return node;
    }
    if (current().type == TokenType::LParen) {
        advance(); // skip '('
        auto expr = parseExpression();
        expect(TokenType::RParen, "Expected ')'");
        return expr;
    }
    throw std::runtime_error("Invalid expression: " + current().value);
}

// 解析带优先级的二元表达式
static std::shared_ptr<ASTNode> parseBinaryOpRHS(int exprPrec, std::shared_ptr<ASTNode> lhs) {
    while (true) {
        if (current().type != TokenType::Operator)
            return lhs;

        std::string op = current().value;
        int prec = getPrecedence(op);
        if (prec < exprPrec)
            return lhs;

        advance(); // consume operator

        auto rhs = parsePrimary();

        // 检查下一运算符优先级（右结合）
        if (current().type == TokenType::Operator) {
            int nextPrec = getPrecedence(current().value);
            if (prec < nextPrec) {
                rhs = parseBinaryOpRHS(prec + 1, rhs);
            }
        }

        auto binNode = std::make_shared<ASTNode>(NodeType::BinaryOp, op);
        binNode->children.push_back(lhs);
        binNode->children.push_back(rhs);
        lhs = binNode;
    }
}

static std::shared_ptr<ASTNode> parseExpression() {
    auto lhs = parsePrimary();
    return parseBinaryOpRHS(0, lhs);
}


// 解析语句
static std::shared_ptr<ASTNode> parseStatement() {
    // 变量声明：int a;
    if (current().type == TokenType::Keyword && current().value == "int") {
        advance();  // skip 'int'
        std::string var = current().value;
        expect(TokenType::Identifier, "Expected variable name after 'int'");
        expect(TokenType::Semicolon, "Expected ';' after declaration");
        return std::make_shared<ASTNode>(NodeType::Declaration, var);
    }

    // 函数调用：println_int(a);
    if (current().type == TokenType::Identifier && current().value == "println_int") {
        advance(); // println_int
        expect(TokenType::LParen);
        std::string arg = current().value;
        expect(TokenType::Identifier);
        expect(TokenType::RParen);
        expect(TokenType::Semicolon);
        return std::make_shared<ASTNode>(NodeType::FunctionCall, arg);
    }

    // 赋值语句：a = 1;
    if (current().type == TokenType::Identifier) {
        std::string var = current().value;
        advance();
        expect(TokenType::Operator, "Expected '='");
        auto expr = parseExpression();
        expect(TokenType::Semicolon, "Expected ';' after assignment");
        auto node = std::make_shared<ASTNode>(NodeType::Assignment, var);
        node->children.push_back(expr);
        return node;
    }

    // return 语句
    if (current().type == TokenType::Keyword && current().value == "return") {
        advance(); // skip 'return'
        auto expr = parseExpression();
        expect(TokenType::Semicolon, "Expected ';' after return expression");
        auto node = std::make_shared<ASTNode>(NodeType::ReturnStmt);
        node->children.push_back(expr);
        return node;
    }


    throw std::runtime_error("Unknown statement: " + current().value);
}


// 主函数解析入口
std::shared_ptr<ASTNode> parseProgram(const std::vector<Token>& tokens) {
    toks = tokens;
    pos = 0;

    auto root = std::make_shared<ASTNode>(NodeType::Program);

    
    expect(TokenType::Keyword, "Expected 'int'");
    expect(TokenType::Identifier, "Expected 'main'");
    expect(TokenType::LParen);
    // 处理参数列表
    if (current().type != TokenType::RParen) {
        // 第一个参数
        expect(TokenType::Keyword, "Expected type specifier");
        expect(TokenType::Identifier, "Expected parameter name");
        
        
        advance();
        expect(TokenType::Keyword, "Expected type specifier");
        expect(TokenType::Identifier, "Expected parameter name");
        
    }

    expect(TokenType::RParen);
    expect(TokenType::LBrace);

    while (current().type != TokenType::RBrace && current().type != TokenType::End) {
        root->children.push_back(parseStatement());
    }

    expect(TokenType::RBrace);
    return root;
}

