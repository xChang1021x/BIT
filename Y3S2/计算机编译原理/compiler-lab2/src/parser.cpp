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
    // 一元运算符支持
    if (current().type == TokenType::Operator &&
        (current().value == "-" || current().value == "!" || current().value == "~")) {
        std::string op = current().value;
        advance();
        auto operand = parsePrimary();
        auto node = std::make_shared<ASTNode>(NodeType::UnaryOp, op);
        node->children.push_back(operand);
        return node;
    }

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

        std::vector<std::shared_ptr<ASTNode>> declarations;

        while (true) {
            std::string var = current().value;
            expect(TokenType::Identifier, "Expected variable name");

            auto decl = std::make_shared<ASTNode>(NodeType::Declaration, var);

            if (current().type == TokenType::Operator && current().value == "=") {
                advance();  // skip '='
                auto initExpr = parseExpression();
                decl->children.push_back(initExpr);  // 初始化表达式
            }

            declarations.push_back(decl);

            if (current().type == TokenType::Semicolon) {
                advance();
                break;
            } else if(current().type == TokenType::Comma) {
                advance();  // skip ','
            } 
            else if (current().type == TokenType::Operator && current().value == ",") {
                advance();  // skip ','
            } else {
                throw std::runtime_error("Expected ',' or ';' in declaration");
            }
        }

        // 合并为一个 Block 节点
        auto block = std::make_shared<ASTNode>(NodeType::Block);
        block->children = declarations;
        return block;
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

    // if-else 语句
    if (current().type == TokenType::Keyword && current().value == "if") {
        advance(); // skip 'if'
        expect(TokenType::LParen);
        auto cond = parseExpression();
        expect(TokenType::RParen);
        expect(TokenType::LBrace);

        auto ifBlock = std::make_shared<ASTNode>(NodeType::Block);
        while (current().type != TokenType::RBrace)
            ifBlock->children.push_back(parseStatement());
        expect(TokenType::RBrace);

        auto node = std::make_shared<ASTNode>(NodeType::IfStmt);
        node->children.push_back(cond);
        node->children.push_back(ifBlock);

        // optional else
        if (current().type == TokenType::Keyword && current().value == "else") {
            advance(); // skip 'else'
            expect(TokenType::LBrace);
            auto elseBlock = std::make_shared<ASTNode>(NodeType::Block);
            while (current().type != TokenType::RBrace)
                elseBlock->children.push_back(parseStatement());
            expect(TokenType::RBrace);
            node->children.push_back(elseBlock);
        }

        return node;
    }

    // while 语句
    if (current().type == TokenType::Keyword && current().value == "while") {
        advance(); // skip 'while'
        expect(TokenType::LParen);
        auto cond = parseExpression();
        expect(TokenType::RParen);
        expect(TokenType::LBrace);

        auto body = std::make_shared<ASTNode>(NodeType::Block);
        while (current().type != TokenType::RBrace)
            body->children.push_back(parseStatement());
        expect(TokenType::RBrace);

        auto node = std::make_shared<ASTNode>(NodeType::WhileStmt);
        node->children.push_back(cond);
        node->children.push_back(body);
        return node;
    }

    // break 语句
    if (current().type == TokenType::Keyword && current().value == "break") {
        advance();
        expect(TokenType::Semicolon);
        return std::make_shared<ASTNode>(NodeType::BreakStmt);
    }

    // continue 语句
    if (current().type == TokenType::Keyword && current().value == "continue") {
        advance();
        expect(TokenType::Semicolon);
        return std::make_shared<ASTNode>(NodeType::ContinueStmt);
    }


    throw std::runtime_error("Unknown statement: " + current().value);
}

static std::shared_ptr<ASTNode> parseFunctionDefinition() {
    std::string returnType = current().value;  // "int" 或 "void"
    expect(TokenType::Keyword);

    std::string funcName = current().value;
    expect(TokenType::Identifier);

    expect(TokenType::LParen);
    auto funcNode = std::make_shared<ASTNode>(NodeType::FunctionDef, funcName);

    // 参数列表
    if (current().type != TokenType::RParen) {
        while (true) {
            expect(TokenType::Keyword); // int
            std::string paramName = current().value;
            expect(TokenType::Identifier);
            auto param = std::make_shared<ASTNode>(NodeType::Parameter, paramName);
            funcNode->children.push_back(param);

            if (current().type == TokenType::Comma) {
                advance();  // skip ','
            } else {
                break;
            }
        }
    }
    expect(TokenType::RParen);
    expect(TokenType::LBrace);

    auto body = std::make_shared<ASTNode>(NodeType::Block);
    while (current().type != TokenType::RBrace) {
        body->children.push_back(parseStatement());
    }
    expect(TokenType::RBrace);

    funcNode->children.push_back(body);
    return funcNode;
}



// 主函数解析入口
std::shared_ptr<ASTNode> parseProgram(const std::vector<Token>& tokens) {
    toks = tokens;
    pos = 0;

    auto root = std::make_shared<ASTNode>(NodeType::Program);

    while (current().type != TokenType::End) {
        if (current().type == TokenType::Keyword &&
            (current().value == "int" || current().value == "void")) {
            root->children.push_back(parseFunctionDefinition());
        } else {
            throw std::runtime_error("Top-level must be function definition");
        }
    }

    return root;
}


