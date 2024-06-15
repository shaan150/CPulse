#include "ArithmeticOperations.h"

Value ArithmeticOperations::performArithmeticOperation(const Token& token, const std::string& op, const double left, const double right) {
    std::string line = std::to_string(token.line);
    double result;

    if (op == "+") result = left + right;
    else if (op == "-") result = left - right;
    else if (op == "*") result = left * right;
    else if (op == "/") {
        if (right == 0) throw std::runtime_error("Arithmetic Operation Error: Division by zero at line " + line);
        result = left / right;
    }
    else if (op == "%") {
        if (right == 0) throw std::runtime_error("Arithmetic Operation Error: Modulo by zero at line " + line);
        result = std::fmod(left, right);
    }
    else {
        throw std::runtime_error("Arithmetic Operation Error: Invalid Operator " + op + " at line " + line);
    }

    // Check if result is an integer
    if (std::floor(result) == result) {
        return static_cast<int>(result);
    }

    return result;
}
