#include "CodeGenerator/CodeGenerator.h"
#include "Evaluator/Handler/FunctionHandler.h"
#include "Value/ValueHelper.h"
#include <stdexcept>
#include <iostream>
#include <stack>
#include <memory>
#include <vector>

CodeGenerator::CodeGenerator() {
    functionHandler = std::make_unique<FunctionHandler>();
}

CodeGenerator::~CodeGenerator() {
    // Destructor code if needed (unique_ptr will handle the deletion automatically)
}

void CodeGenerator::execute(const ExprNode* node) {
    functionHandler = std::make_unique<FunctionHandler>();
    if (auto blockNode = dynamic_cast<const BlockNode*>(node)) {
        executeBlock(blockNode);
    }
    else {
        evaluate(node, *this);
    }
}

void CodeGenerator::executeBlock(const BlockNode* blockNode) {
    for (const auto& statement : blockNode->getStatements()) {
        evaluate(statement.get(), *this);
    }
}

Value CodeGenerator::performBinaryOperation(const BinaryExprNode* binNode, const Value& left, const Value& right) {
    const std::string& op = binNode->getOp();
    // get the type of token
    Token token = binNode->getToken();
    std::string line = std::to_string(token.line);

    if (token.type == TokenType::ARITHMETIC) {
        if (ValueHelper::isDouble(left) && ValueHelper::isDouble(right)) {
            double leftValue = ValueHelper::isDouble(left) ? ValueHelper::asDouble(left) : ValueHelper::asInt(left);
            double rightValue = ValueHelper::isDouble(right) ? ValueHelper::asDouble(right) : ValueHelper::asInt(right);
            return performArithmeticOperation(token, op, leftValue, rightValue);
        }
        else if (ValueHelper::isInt(left) && ValueHelper::isInt(right)) {
            return performArithmeticOperation(token, op, ValueHelper::asInt(left), ValueHelper::asInt(right));
        }
        else if (ValueHelper::isDouble(left) && ValueHelper::isInt(right)) {
            return performArithmeticOperation(token, op, ValueHelper::asDouble(left), ValueHelper::asInt(right));
        }
        else if (ValueHelper::isInt(left) && ValueHelper::isDouble(right)) {
            return performArithmeticOperation(token, op, ValueHelper::asInt(left), ValueHelper::asDouble(right));
        }
        else if (ValueHelper::isString(left) && ValueHelper::isString(right)) {
            return performStringOperation(token, op, left, right);
        }
        else if (ValueHelper::isString(left) && ValueHelper::isInt(right)) {
            return performStringOperation(token, op, left, right);
        }
        else if (ValueHelper::isString(left) && ValueHelper::isDouble(right)) {
            return performStringOperation(token, op, left, right);
        }
        else if (ValueHelper::isString(left) && ValueHelper::isBool(right)) {
			return performStringOperation(token, op, left, right);
		}
        else {
            throw std::runtime_error("Arithmetic Operation Error: Unsupported operation " + op + " with types " + ValueHelper::type(left)
                + " and " + ValueHelper::type(right) + " at line " + line);
        }
    }


    if (token.type == TokenType::COMPARISON) {
        return performComparisonOperation(token, op, left, right);
    }

    if (token.type == TokenType::LOGICAL) {
       return performLogicalOperation(token, op, left, right);
    }

    throw std::runtime_error("Arithmetic Operation Error: Type mismatch or unsupported operation " + op + " at line " + line);
}

Value CodeGenerator::performArithmeticOperation(const Token token, const std::string& op, const double left, const double right) {
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

Value CodeGenerator::performStringOperation(const Token token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);
    if (op == "+") return ValueHelper::asString(left) + ValueHelper::asString(right);
    throw std::runtime_error("String Operation Error: Invalid Operator " + op + " at line " + line);
}

Value CodeGenerator::performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);

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
    throw std::runtime_error("Comparison Operation Error: Unsupported comparison operator " + op + " at line " + line);
}

Value CodeGenerator::performLogicalOperation(const Token token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);

    bool leftBool;
    bool rightBool;

    // Check for direct boolean types
    if (std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right)) {
        leftBool = std::get<bool>(left);
        rightBool = std::get<bool>(right);
    }
    // Check for string representations of boolean values
    else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
        leftBool = (std::get<std::string>(left) == "true");
        rightBool = (std::get<std::string>(right) == "true");
    }
    // Mixed case: one boolean and one string
    else if (std::holds_alternative<std::string>(left) && std::holds_alternative<bool>(right)) {
        leftBool = (std::get<std::string>(left) == "true");
        rightBool = std::get<bool>(right);
    }
    else if (std::holds_alternative<bool>(left) && std::holds_alternative<std::string>(right)) {
        leftBool = std::get<bool>(left);
        rightBool = (std::get<std::string>(right) == "true");
    }
    else {
        throw std::runtime_error("Logical Operation Error: Type mismatch or unsupported operation " + op + " at line " + line);
    }

    if (op == "and") return leftBool && rightBool;
    if (op == "or") return leftBool || rightBool;

    throw std::runtime_error("Logical Operation Error: Unsupported logical operator " + op + " at line " + line);
}
Value CodeGenerator::performUnaryOperation(const Token& token, const std::string& op, const Value& operand) {
    std::string line = std::to_string(token.line);


    // Check for integer and double types
    if (ValueHelper::isInt(operand)) {
        int o = ValueHelper::asInt(operand);
        if (op == "-") {
            return -o;
        }
    }
    else if (ValueHelper::isDouble(operand)) {
        double o = ValueHelper::asDouble(operand);
        if (op == "-") {
            return -o;
        }
    }

    // Check for boolean type
    if (op == "!" && std::holds_alternative<bool>(operand)) {
        return !std::get<bool>(operand);
    }

    throw std::runtime_error("Unary Operation Error: Unsupported unary operator " + op + " at line " + line);
}

void CodeGenerator::printValue(const Value& value) {
    std::string output;
    // Convert value to string properly
    if (std::holds_alternative<int>(value)) {
        output = std::to_string(std::get<int>(value));
    }
    else if (std::holds_alternative<double>(value)) {
        output = std::to_string(std::get<double>(value));
    }
    else if (std::holds_alternative<bool>(value)) {
        output = std::get<bool>(value) ? "true" : "false";
    }
    else if (std::holds_alternative<std::string>(value)) {
        output = std::get<std::string>(value);
    }
    else if (std::holds_alternative<std::monostate>(value)) {
        output = "None";
    }
    else if (std::holds_alternative<std::shared_ptr<TypedVector>>(value)) {
        const auto& vec = std::get<std::shared_ptr<TypedVector>>(value);
        const auto& values = vec->getValues();
        // Create string representation of vector
        output = "[";
        for (size_t i = 0; i < values.size(); i++) {
            if (std::holds_alternative<int>(values[i])) {
                output += std::to_string(std::get<int>(values[i]));
            }
            else if (std::holds_alternative<double>(values[i])) {
                output += std::to_string(std::get<double>(values[i]));
            }
            else if (std::holds_alternative<bool>(values[i])) {
                output += std::to_string(std::get<bool>(values[i]));
            }
            else if (std::holds_alternative<std::string>(values[i])) {
                output += std::get<std::string>(values[i]);
            }
            if (i != values.size() - 1) {
                output += ", ";
            }
        }
        output += "]";
    }
    else {
        throw std::runtime_error("Print Error: Unsupported type " + ValueHelper::type(value));
    }

    std::cout << output << std::endl;
}