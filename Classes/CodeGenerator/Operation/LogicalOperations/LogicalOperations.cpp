#include "LogicalOperations.h"

Value LogicalOperations::performLogicalOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);

    bool leftBool;
    bool rightBool;

    // Check for direct boolean types
    if (std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right)) {
        leftBool = std::get<bool>(left);
        rightBool = std::get<bool>(right);
    }
    // Check for string representations of boolean values
    else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
        leftBool = (std::get<std::string>(left) == "true");
        rightBool = (std::get<std::string>(right) == "true");
    }
    // Mixed case: one boolean and one string
    else if (std::holds_alternative<std::string>(left) && std::holds_alternative<bool>(right)) {
        leftBool = (std::get<std::string>(left) == "true");
        rightBool = std::get<bool>(right);
    }
    else if (std::holds_alternative<bool>(left) && std::holds_alternative<std::string>(right)) {
        leftBool = std::get<bool>(left);
        rightBool = (std::get<std::string>(right) == "true");
    }
    else {
        throw std::runtime_error("Logical Operation Error: Type mismatch or unsupported operation " + op);
    }

    if (op == "and") return leftBool && rightBool;
    if (op == "or") return leftBool || rightBool;

    throw std::runtime_error("Logical Operation Error: Unsupported logical operator " + op);
}
