#include "CodeGenerator.h"

void CodeGenerator::execute(const ExprNode* node) {
    auto value = evaluate(node);
}

Value CodeGenerator::evaluate(const ExprNode* node) {
    if (!node) {
        throw std::runtime_error("Node is empty");
    }

    if (auto strNode = dynamic_cast<const StringNode*>(node)) {
        return strNode->value;
    }
    else if (auto numNode = dynamic_cast<const NumberNode*>(node)) {
        return numNode->value;
    }
    else if (auto boolNode = dynamic_cast<const BooleanNode*>(node)) {
        return boolNode->value;
    }
    else if (auto varNode = dynamic_cast<const VariableNode*>(node)) {
        auto it = variables.find(varNode->name);
        if (it != variables.end()) {
            return it->second;
        }
        throw std::runtime_error("Undefined variable: " + varNode->name);
    }
    else if (auto assignNode = dynamic_cast<const AssignNode*>(node)) {
        Value value = evaluate(assignNode->value.get());
        variables[assignNode->name] = value;
        return value;
    }
    else if (auto binNode = dynamic_cast<const BinaryExprNode*>(node)) {
        Value left = evaluate(binNode->left.get());
        Value right = evaluate(binNode->right.get());
        return performBinaryOperation(binNode->op, left, right);
    }
    else if (auto unNode = dynamic_cast<const UnaryExprNode*>(node)) {
        Value operand = evaluate(unNode->operand.get());
        return performUnaryOperation(unNode->op, operand);
    }
    else if (auto prNode = dynamic_cast<const PrintNode*>(node)) {
        Value value = evaluate(prNode->expression.get());
		printValue(value);
		return value;
    }
    throw std::runtime_error("Unsupported node type");
}

Value CodeGenerator::performBinaryOperation(const std::string& op, const Value& left, const Value& right) {
    if (op == tokenTypeToString(TokenType::PLUS) || op == tokenTypeToString(TokenType::MINUS) || op == tokenTypeToString(TokenType::MULTIPLY) || op == tokenTypeToString(TokenType::DIVIDE)) {
        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            return performArithmeticOperation(op, std::get<double>(left), std::get<double>(right));
        }
    }

    if (op == tokenTypeToString(TokenType::PLUS)) {
        if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
            return std::get<std::string>(left) + std::get<std::string>(right);
        }
    }

    if (op == tokenTypeToString(TokenType::EQUAL_TO) || op == tokenTypeToString(TokenType::NOT_EQUAL) || op == tokenTypeToString(TokenType::LESS_THAN) || op == tokenTypeToString(TokenType::GREATER_THAN) || op == tokenTypeToString(TokenType::LESS_EQUAL) || op == tokenTypeToString(TokenType::GREATER_EQUAL)) {
        return performComparisonOperation(op, left, right);
    }

    if (op == tokenTypeToString(TokenType::LOGICAL_AND) || op == tokenTypeToString(TokenType::LOGICAL_OR)) {
        if (std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right)) {
            return performLogicalOperation(op, std::get<bool>(left), std::get<bool>(right));
        }
    }

    throw std::runtime_error("Type mismatch or unsupported operation: " + op);
}

Value CodeGenerator::performArithmeticOperation(const std::string& op, double left, double right) {
    if (op == tokenTypeToString(TokenType::PLUS)) return left + right;
    if (op == tokenTypeToString(TokenType::MINUS)) return left - right;
    if (op == tokenTypeToString(TokenType::MULTIPLY)) return left * right;
    if (op == tokenTypeToString(TokenType::DIVIDE)) {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }
    throw std::runtime_error("Unsupported arithmetic operator: " + op);
}

Value CodeGenerator::performComparisonOperation(const std::string& op, const Value& left, const Value& right) {
    if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
        double l = std::get<double>(left);
        double r = std::get<double>(right);
        if (op == tokenTypeToString(TokenType::EQUAL_TO)) return l == r;
        if (op == tokenTypeToString(TokenType::NOT_EQUAL)) return l != r;
        if (op == tokenTypeToString(TokenType::LESS_THAN)) return l < r;
        if (op == tokenTypeToString(TokenType::GREATER_THAN)) return l > r;
        if (op == tokenTypeToString(TokenType::LESS_EQUAL)) return l <= r;
        if (op == tokenTypeToString(TokenType::GREATER_EQUAL)) return l >= r;
    }
    else if (std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right)) {
        bool l = std::get<bool>(left);
        bool r = std::get<bool>(right);
        if (op == tokenTypeToString(TokenType::EQUAL_TO)) return l == r;
        if (op == tokenTypeToString(TokenType::NOT_EQUAL)) return l != r;
    }
    else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
        std::string l = std::get<std::string>(left);
        std::string r = std::get<std::string>(right);
        if (op == tokenTypeToString(TokenType::EQUAL_TO)) return l == r;
        if (op == tokenTypeToString(TokenType::NOT_EQUAL)) return l != r;
    }
    throw std::runtime_error("Type mismatch or unsupported comparison operator: " + op);
}

Value CodeGenerator::performLogicalOperation(const std::string& op, bool left, bool right) {
    if (op == tokenTypeToString(TokenType::LOGICAL_AND)) return left && right;
    if (op == tokenTypeToString(TokenType::LOGICAL_OR)) return left || right;
    throw std::runtime_error("Unsupported logical operator: " + op);
}

Value CodeGenerator::performUnaryOperation(const std::string& op, const Value& operand) {
    if (op == tokenTypeToString(TokenType::MINUS) && std::holds_alternative<double>(operand)) {
        return -std::get<double>(operand);
    }
    if (op == tokenTypeToString(TokenType::NOT) && std::holds_alternative<bool>(operand)) {
        return !std::get<bool>(operand);
    }
    throw std::runtime_error("Unsupported unary operator: " + op);
}

void CodeGenerator::printValue(const Value& value) {
    if (std::holds_alternative<double>(value)) {
        std::cout << std::get<double>(value) << std::endl;
    }
    else if (std::holds_alternative<bool>(value)) {
        std::cout << std::boolalpha << std::get<bool>(value) << std::endl;
    }
    else if (std::holds_alternative<std::string>(value)) {
        std::cout << std::get<std::string>(value) << std::endl;
    }
    else if (std::holds_alternative<std::monostate>(value)) {
        std::cout << "None" << std::endl;
    }
    else {
        throw std::runtime_error("Unsupported value type");
    }
}
