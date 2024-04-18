#pragma once

#include <memory>
#include <string>
#include <vector>

// Base class for all AST nodes.
class ASTNode {
public:
    virtual ~ASTNode() = default;  // Ensure proper cleanup with a virtual destructor.
};

// Expression node base class for all kinds of expressions.
class ExprNode : public ASTNode {
public:
    virtual ~ExprNode() = default;
};

// Represents a binary operation (e.g., addition, multiplication).
class BinaryExprNode : public ExprNode {
public:
    std::unique_ptr<ExprNode> left;  // The left operand
    std::unique_ptr<ExprNode> right; // The right operand
    std::string op;                  // The operator

    BinaryExprNode(std::unique_ptr<ExprNode> left, std::string op, std::unique_ptr<ExprNode> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}
};

// Represents a unary operation (e.g., negation).
class UnaryExprNode : public ExprNode {
public:
    std::unique_ptr<ExprNode> operand; // The operand
    std::string op;                           // The operator

    UnaryExprNode(std::string op, std::unique_ptr<ExprNode> operand)
        : operand(std::move(operand)), op(op) {}
};

// Represents numeric literals (e.g., "123", "3.14").
class NumberNode : public ExprNode {
public:
    double value; // The numeric value

    explicit NumberNode(double value) : value(value) {}
};

// Represents boolean literals (e.g., "true", "false").
class BooleanNode : public ExprNode {
public:
    bool value; // The boolean value

    explicit BooleanNode(bool value) : value(value) {}
};
