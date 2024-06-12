#pragma once
#include <variant>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "AST.h"
#include "Value.h"

class CodeGenerator {
public:
    // Executes the AST and outputs the result
    void execute(const ExprNode* root);


private:
    std::unordered_map<std::string, Value> variables;
    void executeBlock(const BlockNode* blockNode);
    Value evaluate(const ExprNode* node);
    Value performBinaryOperation(auto binNode, const Value& left, const Value& right);
    Value performArithmeticOperation(const Token token, const std::string& op, const double left, const double right);
    Value performStringOperation(const Token token, const std::string& op, const Value& left, const Value& right);
    Value performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right);
    Value performLogicalOperation(const Token token, const std::string& op, bool left, bool right);
    Value performUnaryOperation(const Token& token, const std::string& op, const Value& operand);
    void printValue(const Value& value);
};