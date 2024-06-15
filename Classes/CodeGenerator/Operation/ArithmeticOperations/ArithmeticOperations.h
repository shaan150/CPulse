#ifndef ARITHMETICOPERATIONS_H
#define ARITHMETICOPERATIONS_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"
#include <cmath>
#include <unordered_map>
#include <functional>

/**
 * @class ArithmeticOperations
 * @brief Provides functionality to perform arithmetic operations on values.
 */
class ArithmeticOperations {
public:
    /**
     * @brief Performs an arithmetic operation on two double values based on the given operator.
     * @param token The token representing the arithmetic operator.
     * @param op The arithmetic operator as a string (e.g., "+", "-", "*", "/", "%").
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the arithmetic operation.
     * @throws std::runtime_error if the operator is invalid or if there is a division/modulo by zero.
     */
    static Value performArithmeticOperation(const Token& token, const std::string& op, const double left, const double right);

    private:
        static const std::unordered_map<std::string, std::function<double(double, double)>> operations;

};

#endif // ARITHMETICOPERATIONS_H
