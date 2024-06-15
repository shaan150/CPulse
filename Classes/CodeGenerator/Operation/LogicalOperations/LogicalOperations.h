#ifndef LOGICALOPERATIONS_H
#define LOGICALOPERATIONS_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"

/**
 * @class LogicalOperations
 * @brief Provides functionality to perform logical operations on values.
 */
class LogicalOperations {
public:
    /**
     * @brief Performs a logical operation on two values based on the given operator.
     * @param token The token representing the logical operator.
     * @param op The logical operator as a string (e.g., "and", "or").
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the logical operation as a Value (boolean).
     * @throws std::runtime_error if the operator is unsupported or the operation is invalid.
     */
    static Value performLogicalOperation(const Token& token, const std::string& op, const Value& left, const Value& right);
};

#endif // LOGICALOPERATIONS_H
