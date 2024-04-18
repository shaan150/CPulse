#include "CodeGenerator.h"
#include <stdexcept>
#include <iostream>

void CodeGenerator::execute(const ExprNode* root) {
    try {
        double result = evaluate(root);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
}

double CodeGenerator::evaluate(const ExprNode* node) {
    if (auto numNode = dynamic_cast<const NumberNode*>(node)) {
        return numNode->value;
    }
    else if (auto binNode = dynamic_cast<const BinaryExprNode*>(node)) {
        double left = evaluate(binNode->left.get());
        double right = evaluate(binNode->right.get());
        return performBinaryOperation(binNode->op, left, right);
    }
    else if (auto unNode = dynamic_cast<const UnaryExprNode*>(node)) {
        double operand = evaluate(unNode->operand.get());
        return unNode->op == tokenTypeToString(TokenType::MINUS) ? -operand : unNode->op == tokenTypeToString(TokenType::NOT) ? !operand : throw std::runtime_error("Unsupported unary operator");
    }
    else if (auto boolNode = dynamic_cast<const BooleanNode*>(node)) {
        return static_cast<double>(boolNode->value); // Convert boolean to double
    }
    throw std::runtime_error("Unknown expression type in AST with node type: " + std::string(typeid(*node).name()));
}

double CodeGenerator::performBinaryOperation(const std::string& op, double left, double right) {
    // Arithmetic operations
    if (op == tokenTypeToString(TokenType::PLUS)) return left + right;
    else if (op == tokenTypeToString(TokenType::MINUS)) return left - right;
    else if (op == tokenTypeToString(TokenType::MULTIPLY)) return left * right;
    else if (op == tokenTypeToString(TokenType::DIVIDE)) {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }

    // Comparison operations
    else if (op == tokenTypeToString(TokenType::EQUAL_TO)) return left == right;
    else if (op == tokenTypeToString(TokenType::NOT_EQUAL)) return left != right;
    else if (op == tokenTypeToString(TokenType::LESS_THAN)) return left < right;
    else if (op == tokenTypeToString(TokenType::GREATER_THAN)) return left > right;
    else if (op == tokenTypeToString(TokenType::LESS_EQUAL)) return left <= right;
    else if (op == tokenTypeToString(TokenType::GREATER_EQUAL)) return left >= right;

    // Logical operations (assuming operands are already coerced to boolean)
    else if (op == tokenTypeToString(TokenType::LOGICAL_AND)) return left && right;
    else if (op == tokenTypeToString(TokenType::LOGICAL_OR)) return left || right;

    throw std::runtime_error("Unsupported binary operator: " + op);
}
