// AST.cpp
#include "AST.h"

BinaryExprNode::BinaryExprNode(std::unique_ptr<ExprNode> left, char op, std::unique_ptr<ExprNode> right)
    : left(std::move(left)), op(op), right(std::move(right)) {}

UnaryExprNode::UnaryExprNode(char op, std::unique_ptr<ExprNode> operand)
    : op(op), operand(std::move(operand)) {}

NumberNode::NumberNode(double value)
    : value(value) {}