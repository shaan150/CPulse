#ifndef UNARYOPERATIONS_H
#define UNARYOPERATIONS_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"

/**
 * @class UnaryOperations
 * @brief Provides functionality to perform unary operations on values.
 */
class UnaryOperations {
public:
    /**
     * @brief Performs a unary operation on a value based on the given operator.
     * @param token The token representing the unary operator.
     * @param op The unary operator as a string (e.g., "-", "!").
     * @param operand The operand value.
     * @return The result of the unary operation as a Value.
     * @throws std::runtime_error if the operator is unsupported or the operation is invalid.
     */
    static Value performUnaryOperation(const Token& token, const std::string& op, const Value& operand);
};

#endif // UNARYOPERATIONS_H
