#pragma once
#include "AST.h"
#include "TokenTypes.h"
#include <memory>
#include <iostream>

class CodeGenerator {
public:
    // Executes the AST and outputs the result
    void execute(const ExprNode* root);

private:
    double evaluate(const ExprNode* node);
    double performBinaryOperation(const std::string& op, double left, double right);
    double evaluate(const NumberNode* node);
    double evaluate(const BinaryExprNode* node);
    double evaluate(const UnaryExprNode* node);
    double evaluate(const BooleanNode* node);
};
