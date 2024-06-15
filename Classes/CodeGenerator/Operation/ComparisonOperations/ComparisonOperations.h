#ifndef COMPARISONOPERATIONS_H
#define COMPARISONOPERATIONS_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"

/**
 * @class ComparisonOperations
 * @brief Provides functionality to perform comparison operations on values.
 */
class ComparisonOperations {
public:
    /**
     * @brief Performs a comparison operation on two values based on the given operator.
     * @param token The token representing the comparison operator.
     * @param op The comparison operator as a string (e.g., "==", "!=", "<", "<=", ">", ">=").
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the comparison operation as a Value (boolean).
     * @throws std::runtime_error if the operator is unsupported or the comparison is invalid.
     */
    static Value performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right);
};

#endif // COMPARISONOPERATIONS_H
