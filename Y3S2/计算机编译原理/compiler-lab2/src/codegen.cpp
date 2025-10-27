#include "codegen.h"
#include <unordered_map>

static int labelOffset = 0;
static int stackOffset = 0;
static std::unordered_map<std::string, int> varOffsets;
static std::vector<std::string> breakLabels;
static std::vector<std::string> continueLabels;


static void emitPrologue(std::ostream& out) {
    out << ".intel_syntax noprefix\n";
    out << ".global main\n";
    out << ".extern printf\n";
    out << ".data\n";
    out << "format_str:\n";
    out << ".asciz \"%d\\n\"\n";
    out << ".text\n";
    out << "main:\n";
    out << "  push ebp\n";
    out << "  mov ebp, esp\n";
    out << "  sub esp, 0x100\n";  // 分配栈空间
}

static void emitEpilogue(std::ostream& out) {
    out << "  mov eax, 0\n";
    out << "  leave\n";
    out << "  ret\n";
}

static void generateExpr(const std::shared_ptr<ASTNode>& node, std::ostream& out) {
    if (node->type == NodeType::Constant) {
        out << "  mov eax, " << node->value << "\n";
    } else if (node->type == NodeType::Variable) {
        int offset = varOffsets[node->value];
        out << "  mov eax, DWORD PTR [ebp" << offset << "]\n";
    } else if (node->type == NodeType::BinaryOp) {
        generateExpr(node->children[0], out);   // left
        out << "  push eax\n";
        generateExpr(node->children[1], out);   // right
        out << "  pop ebx\n";              // ebx = left, eax = right

        if (node->value == "+") {
            out << "  add eax, ebx\n"; // eax = right + left
        }
        else if (node->value == "-") {
            out << "  sub ebx, eax\n";
            out << "  mov eax, ebx\n";     // eax = left - right
        }
        else if (node->value == "*") {
            out << "  imul eax, ebx\n";    // eax = right * left
        }
        else if (node->value == "/") {
            out << "  xchg eax, ebx\n";    // eax = left, ebx = right
            out << "  mov edx, 0\n";
            out << "  div ebx\n";
        }
        else if (node->value == "%") {
            out << "  xchg eax, ebx\n";
            out << "  mov edx, 0\n";
            out << "  div ebx\n";
            out << "  mov eax, edx\n";
        }
        else if (node->value == "|") out << "  or eax, ebx\n";
        else if (node->value == "&") out << "  and eax, ebx\n";
        else if (node->value == "^") out << "  xor eax, ebx\n";
        else if (node->value == "<") {
            out << "  cmp ebx, eax\n";
            out << "  jl true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        else if (node->value == "<=") {
            out << "  cmp ebx, eax\n";
            out << "  jle true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        else if (node->value == ">") {
            out << "  cmp ebx, eax\n";
            out << "  jg true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        else if (node->value == ">=") {
            out << "  cmp ebx, eax\n";
            out << "  jge true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        else if (node->value == "==") {
            out << "  cmp eax, ebx\n";
            out << "  je true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        else if (node->value == "!=") {
            out << "  cmp eax, ebx\n";
            out << "  jne true" << labelOffset << "\n";
            out << "  mov eax, 0\n";
            out << "  jmp done" << labelOffset << "\n";
            out << "true" << labelOffset << ":\n";
            out << "  mov eax, 1\n";
            out << "done" << labelOffset << ":\n";
            labelOffset++;
        }
        // 可扩展更多操作符
    } else if (node->type == NodeType::UnaryOp) {
        generateExpr(node->children[0], out);
        if (node->value == "-") {
            out << "  neg eax\n";
        } else if (node->value == "!") {
            out << "  cmp eax, 0\n";
            out << "  mov eax, 0\n";
            out << "  sete al\n";
        } else if (node->value == "~") {
            out << "  not eax\n";
        }
    }
}

static void generateStmt(const std::shared_ptr<ASTNode>& stmt, std::ostream& out) {
    if (stmt->type == NodeType::Declaration) {
        stackOffset -= 4;
        varOffsets[stmt->value] = stackOffset;
        out << "  mov DWORD PTR [ebp" << stackOffset << "], 0\n";
    } else if (stmt->type == NodeType::Assignment) {
        generateExpr(stmt->children[0], out);
        int offset = varOffsets[stmt->value];
        out << "  mov DWORD PTR [ebp" << offset << "], eax\n";
    } else if (stmt->type == NodeType::FunctionCall) {
        if (stmt->children.size() == 0) {
            // println_int(a);
            int offset = varOffsets[stmt->value];
            out << "  push DWORD PTR [ebp" << offset << "]\n";
            out << "  push offset format_str\n";
            out << "  call printf\n";
            out << "  add esp, 8\n";
        } else {
            // 通用函数调用（支持参数）
            for (int i = stmt->children.size() - 1; i >= 0; --i)
                generateExpr(stmt->children[i], out); // push 参数
            for (int i = stmt->children.size() - 1; i >= 0; --i)
                out << "  push eax\n";
            out << "  call " << stmt->value << "\n";
            out << "  add esp, " << stmt->children.size() * 4 << "\n";
        }
    } else if (stmt->type == NodeType::ReturnStmt) {
        if (!stmt->children.empty()) {
            generateExpr(stmt->children[0], out);  // 将表达式结果放入 eax
        }
        out << "  mov esp, ebp\n";
        out << "  pop ebp\n";
        out << "  ret\n";
    } else if (stmt->type == NodeType::Block) {
        for (auto& child : stmt->children) {
            generateStmt(child, out);
        }
    } else if (stmt->type == NodeType::IfStmt) {
        int id = labelOffset++;
        generateExpr(stmt->children[0], out); // condition
        out << "  cmp eax, 0\n";
        out << "  je else_" << id << "\n";

        // then block
        for (auto& s : stmt->children[1]->children)
            generateStmt(s, out);

        if (stmt->children.size() == 3) {
            out << "  jmp endif_" << id << "\n";
            out << "else_" << id << ":\n";
            for (auto& s : stmt->children[2]->children)
                generateStmt(s, out);
            out << "endif_" << id << ":\n";
        } else {
            out << "else_" << id << ":\n";
        }
    } else if (stmt->type == NodeType::WhileStmt) {
        int id = labelOffset++;
        std::string beginLabel = "while_begin_" + std::to_string(id);
        std::string endLabel = "while_end_" + std::to_string(id);

        continueLabels.push_back(beginLabel);
        breakLabels.push_back(endLabel);

        out << beginLabel << ":\n";
        generateExpr(stmt->children[0], out);
        out << "  cmp eax, 0\n";
        out << "  je " << endLabel << "\n";

        for (auto& s : stmt->children[1]->children)
            generateStmt(s, out);

        out << "  jmp " << beginLabel << "\n";
        out << endLabel << ":\n";

        continueLabels.pop_back();
        breakLabels.pop_back();
    } else if (stmt->type == NodeType::BreakStmt) {
        if (!breakLabels.empty())
            out << "  jmp " << breakLabels.back() << "\n";
    } else if (stmt->type == NodeType::ContinueStmt) {
        if (!continueLabels.empty())
            out << "  jmp " << continueLabels.back() << "\n";
    }



}

void generateFunction(const std::shared_ptr<ASTNode>& func, std::ostream& out) {
    std::string funcName = func->value;
    out << ".global " << funcName << "\n";
    out << funcName << ":\n";

    out << "  push ebp\n";
    out << "  mov ebp, esp\n";
    out << "  sub esp, 0x100\n";

    varOffsets.clear();
    stackOffset = 0;

    // 处理参数（倒序模拟栈压入）
    int argOffset = 8;
    for (auto& param : func->children) {
        if (param->type != NodeType::Parameter) break;
        varOffsets[param->value] = argOffset;
        argOffset += 4;
    }

    // 处理函数体
    auto body = func->children.back();
    for (auto& stmt : body->children)
        generateStmt(stmt, out);

    out << "  mov eax, 0\n"; // 默认返回值
    out << "  leave\n";
    out << "  ret\n";
}


void generateAssembly(const std::shared_ptr<ASTNode>& root, std::ostream& out) {
    varOffsets.clear();
    stackOffset = 0;
    labelOffset = 0;

    out << ".intel_syntax noprefix\n";
    out << ".extern printf\n";
    out << ".data\n";
    out << "format_str:\n";
    out << ".asciz \"%d\\n\"\n";
    out << ".text\n";

    for (auto& child : root->children) {
        if (child->type == NodeType::FunctionDef) {
            generateFunction(child, out);
        }
    }
}

