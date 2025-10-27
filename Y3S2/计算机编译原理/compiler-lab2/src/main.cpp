#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./Compilerlab1 <source file path>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();

    try {
        // 词法分析
        std::vector<Token> tokens = tokenize(sourceCode);
/*
        // ✅ 打印 token 列表，方便调试
        std::cout << "=== Token List ===" << std::endl;
        for (const auto& token : tokens) {
            std::cout << token.toString() << std::endl;
        }
        std::cout << "==================" << std::endl;
*/
        // 语法分析
        auto ast = parseProgram(tokens);

        // 汇编生成
        generateAssembly(ast, std::cout);
    }
    catch (const std::exception& ex) {
        std::cerr << "Parser error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

