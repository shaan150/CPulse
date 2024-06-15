#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"

/**
 * @class StringOperations
 * @brief Provides functionality to perform string operations on values.
 */
class StringOperations {
public:
    /**
     * @brief Performs a string operation on two values based on the given operator.
     * @param token The token representing the string operator.
     * @param op The string operator as a string (e.g., "+").
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the string operation as a Value (string).
     * @throws std::runtime_error if the operator is invalid.
     */
    static Value performStringOperation(const Token& token, const std::string& op, const Value& left, const Value& right);
};

#endif // STRINGOPERATIONS_H
