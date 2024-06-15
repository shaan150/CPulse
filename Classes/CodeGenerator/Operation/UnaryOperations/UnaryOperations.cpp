#include "UnaryOperations.h"

Value UnaryOperations::performUnaryOperation(const Token& token, const std::string& op, const Value& operand) {
    std::string line = std::to_string(token.line);

    // Check for integer and double types
    if (ValueHelper::isInt(operand)) {
        int o = ValueHelper::asInt(operand);
        if (op == "-") {
            return -o;
        }
    }
    else if (ValueHelper::isDouble(operand)) {
        double o = ValueHelper::asDouble(operand);
        if (op == "-") {
            return -o;
        }
    }

    // Check for boolean type
    if (op == "!" && std::holds_alternative<bool>(operand)) {
        return !std::get<bool>(operand);
    }

    throw std::runtime_error("Unary Operation Error: Unsupported unary operator " + op + " at line " + line);
}
