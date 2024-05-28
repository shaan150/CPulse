#pragma once
#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "AST.h"
#include "TokenTypes.h"

using Value = std::variant<double, bool, std::string>;

class CodeGenerator {
public:
    // Executes the AST and outputs the result
    void execute(const ExprNode* root);

private:

    Value evaluate(const ExprNode* node);
    Value performBinaryOperation(const std::string& op, const Value& left, const Value& right);
    Value performArithmeticOperation(const std::string& op, double left, double right);
    Value performComparisonOperation(const std::string& op, const Value& left, const Value& right);
    Value performLogicalOperation(const std::string& op, bool left, bool right);
    Value performUnaryOperation(const std::string& op, const Value& operand);
};
