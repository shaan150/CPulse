#include "ArithmeticOperations.h"

const std::unordered_map<std::string, std::function<double(double, double)>> ArithmeticOperations::operations = {
    {"+", [](double a, double b) { return a + b; }},
    {"-", [](double a, double b) { return a - b; }},
    {"*", [](double a, double b) { return a * b; }},
    {"/", [](double a, double b) { 
        if (b == 0) throw std::runtime_error("Arithmetic Operation Error: Division by zero");
        return a / b; 
    }},
    {"%", [](double a, double b) { 
        if (b == 0) throw std::runtime_error("Arithmetic Operation Error: Modulo by zero");
        return std::fmod(a, b); 
    }}
};

Value ArithmeticOperations::performArithmeticOperation(const Token& token, const std::string& op, double left, double right) {
    auto it = operations.find(op);
    if (it == operations.end()) {
        throw std::runtime_error("Arithmetic Operation Error: Invalid Operator " + op + " at line " + std::to_string(token.line));
    }

    double result = it->second(left, right);

    // Check if result is an integer
    if (std::floor(result) == result) {
        return static_cast<int>(result);
    }

    return result;
}
