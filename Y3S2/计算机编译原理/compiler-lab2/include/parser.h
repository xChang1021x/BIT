#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <memory>
#include <vector>
#include <string>

enum class NodeType {
    Program,
    Function,
    Declaration,
    Assignment,
    ReturnStmt,
    FunctionCall,
    Expression,
    BinaryOp,
    Variable,
    Constant,
    UnaryOp,
    IfStmt,
    WhileStmt,
    BreakStmt,
    ContinueStmt,
    Block,         // 已用于声明组
    FunctionDef,
    Parameter,
};

struct ASTNode {
    NodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(NodeType t, const std::string& v = "") : type(t), value(v) {}
};

std::shared_ptr<ASTNode> parseProgram(const std::vector<Token>& tokens);

#endif
