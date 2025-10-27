#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include <iostream>

void generateAssembly(const std::shared_ptr<ASTNode>& root, std::ostream& out);

#endif
