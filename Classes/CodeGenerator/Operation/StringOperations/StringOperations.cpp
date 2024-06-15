#include "StringOperations.h"

Value StringOperations::performStringOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);
    if (op == "+") return ValueHelper::asString(left) + ValueHelper::asString(right);
    throw std::runtime_error("String Operation Error: Invalid Operator " + op + " at line " + line);
}
