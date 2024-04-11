// AST.h
#pragma once
#include <memory>
#include <string>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// Base class for expression nodes
class ExprNode : public ASTNode {
};

class BinaryExprNode : public ExprNode {
public:
    std::unique_ptr<ExprNode> left;
    std::unique_ptr<ExprNode> right;
    char op; // Operator as char for simplicity

    BinaryExprNode(std::unique_ptr<ExprNode> left, char op, std::unique_ptr<ExprNode> right);
};

class UnaryExprNode : public ExprNode {
public:
    char op; // Operator as char for simplicity
    std::unique_ptr<ExprNode> operand;

    UnaryExprNode(char op, std::unique_ptr<ExprNode> operand);
};

class NumberNode : public ExprNode {
public:
    double value;

    NumberNode(double value);
};
