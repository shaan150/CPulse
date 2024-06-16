#include "ComparisonOperations.h"

Value ComparisonOperations::performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
        // check if the values are of type double or int
    if (ValueHelper::isDouble(left) || ValueHelper::isDouble(right) || ValueHelper::isInt(left) || ValueHelper::isInt(right)) {
        double l = ValueHelper::isDouble(left) ? ValueHelper::asDouble(left) : ValueHelper::asInt(left);
        double r = ValueHelper::isDouble(right) ? ValueHelper::asDouble(right) : ValueHelper::asInt(right);
        if (op == "==") return l == r;
        if (op == "!=") return l != r;
        if (op == "<") return l < r;
        if (op == "<=") return l <= r;
        if (op == ">") return l > r;
        if (op == ">=") return l >= r;
    }
    else {
        if (op == "==") return left == right;
        if (op == "!=") return left != right;
    }
    throw std::runtime_error("Comparison Operation Error: Unsupported comparison operator " + op);
}
