#include "ExpressionNodeEvaluator.h"

Value evaluateBinaryExprNode(CodeGenerator& generator, const BinaryExprNode* binNode) {
    Value left = evaluate(binNode->getLeft().get(), generator);
    Value right = evaluate(binNode->getRight().get(), generator);
    return generator.performBinaryOperation(binNode, left, right);
}

Value evaluateUnaryExprNode(CodeGenerator& generator, const UnaryExprNode* unNode) {
    Value operand = evaluate(unNode->getOperand().get(), generator);
    return generator.performUnaryOperation(unNode->getToken(), unNode->getOp(), operand);
}

Value evaluateTypeCastNode(CodeGenerator& generator, const TypeCastNode* typeCastNode) {
    Value value = evaluate(typeCastNode->getValue().get(), generator);
    std::string type = typeCastNode->getType();
    std::string line = std::to_string(typeCastNode->getToken().line);
    if (type == "int") {
        try {
            if (ValueHelper::isDouble(value)) {
                throw std::runtime_error("Type Cast Error: Cannot convert double to int at line " + line);
            }
            return std::stoi(ValueHelper::asString(value));
        }
        catch (const std::invalid_argument&) {
            throw std::runtime_error("Type Cast Error: Cannot convert value to int at line " + line);
        }
    }
    else if (type == "double") {
        try {
            return std::stod(ValueHelper::asString(value));
        }
        catch (const std::invalid_argument&) {
            throw std::runtime_error("Type Cast Error: Cannot convert value to double at line " + line);
        }
    }
    else if (type == "bool") {
        try {
            return ValueHelper::asBool(value);
        }
        catch (const std::invalid_argument&) {
            throw std::runtime_error("Type Cast Error: Cannot convert value to bool at line " + line);
        }
    }
    else if (type == "string") {
        return ValueHelper::asString(value);
    }
    else {
        throw std::runtime_error("Type Cast Error: Invalid type " + type + " at line " + line);
    }
}
