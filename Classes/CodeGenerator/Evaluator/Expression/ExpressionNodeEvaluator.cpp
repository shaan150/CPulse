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
    std::string valType = ValueHelper::type(value);
    std::string type = typeCastNode->getType();
    std::string line = std::to_string(typeCastNode->getToken().line);
    try {
        if (type == "int") {
            if (valType == "string") {
                return ValueHelper::asInt(value);
            }
        }
        else if (type == "double") {
            return ValueHelper::asDouble(value);
        }
        else if (type == "bool") {
            return ValueHelper::asBool(value);
        }
        else if (type == "string") {
            return ValueHelper::asString(value);
        }
        else {
            throw;
        }
    }
    catch (const std::runtime_error& e) {
		throw std::runtime_error("Type Cast Error: " + std::string(e.what()) + " at line " + line);
	}
    catch (const std::exception& e) {
		throw std::runtime_error("Type Cast Error: Invalid type cast with exception " + std::string(e.what()) + " at line " + line);
	}
}
