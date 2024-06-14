#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <memory>
#include "AST.h"

struct Function {
    std::string name;
    std::string returnType;
    std::unique_ptr<BlockNode> block;

    Function(std::string name, std::string returnType, std::unique_ptr<BlockNode> block)
        : name(std::move(name)), returnType(std::move(returnType)), block(std::move(block)) {}
};

#endif // FUNCTION_H