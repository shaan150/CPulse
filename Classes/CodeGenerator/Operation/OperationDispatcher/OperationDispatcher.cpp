#include "OperationDispatcher.h"

Value OperationDispatcher::dispatchOperation(const BinaryExprNode* binNode, const Value& left, const Value& right) {
    const std::string& op = binNode->getOp();
    Token token = binNode->getToken();
    std::string line = std::to_string(token.line);
    try {
        if (token.type == TokenType::ARITHMETIC) {

            if (ValueHelper::isDouble(left) && ValueHelper::isDouble(right)) {
                double leftValue = ValueHelper::isDouble(left) ? ValueHelper::asDouble(left) : ValueHelper::asInt(left);
                double rightValue = ValueHelper::isDouble(right) ? ValueHelper::asDouble(right) : ValueHelper::asInt(right);
                return ArithmeticOperations::performArithmeticOperation(token, op, leftValue, rightValue);
            }
            else if (ValueHelper::isInt(left) && ValueHelper::isInt(right)) {
                return ArithmeticOperations::performArithmeticOperation(token, op, ValueHelper::asInt(left), ValueHelper::asInt(right));
            }
            else if (ValueHelper::isDouble(left) && ValueHelper::isInt(right)) {
                return ArithmeticOperations::performArithmeticOperation(token, op, ValueHelper::asDouble(left), ValueHelper::asInt(right));
            }
            else if (ValueHelper::isInt(left) && ValueHelper::isDouble(right)) {
                return ArithmeticOperations::performArithmeticOperation(token, op, ValueHelper::asInt(left), ValueHelper::asDouble(right));
            }
            else if (ValueHelper::isString(left) && ValueHelper::isString(right)) {
                return StringOperations::performStringOperation(token, op, left, right);
            }
            else if (ValueHelper::isString(left) && ValueHelper::isInt(right)) {
                return StringOperations::performStringOperation(token, op, left, right);
            }
            else if (ValueHelper::isString(left) && ValueHelper::isDouble(right)) {
                return StringOperations::performStringOperation(token, op, left, right);
            }
            else if (ValueHelper::isString(left) && ValueHelper::isBool(right)) {
                return StringOperations::performStringOperation(token, op, left, right);
            }
            else {
                throw std::runtime_error("Arithmetic Operation Error: Unsupported operation " + op + " with types " + ValueHelper::type(left)
                    + " and " + ValueHelper::type(right));
            }
        }

        if (token.type == TokenType::COMPARISON) {
            return ComparisonOperations::performComparisonOperation(token, op, left, right);
        }

        if (token.type == TokenType::LOGICAL) {
            return LogicalOperations::performLogicalOperation(token, op, left, right);
        }

        throw std::runtime_error("Arithmetic Operation Error: Type mismatch or unsupported operation " + op);
    }
    catch (const std::runtime_error& e) {
        throw std::runtime_error(std::string(e.what()) + " at line " + line);
    }
    catch (const std::exception& e) {
		throw std::runtime_error("Exception: " + std::string(e.what()) + " at line " + line);
	}
}
