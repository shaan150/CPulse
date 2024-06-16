#include "StringOperations.h"

Value StringOperations::performStringOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
    if (op == "+") return ValueHelper::asString(left) + ValueHelper::asString(right);
    throw std::runtime_error("String Operation Error: Invalid Operator " + op);
}
