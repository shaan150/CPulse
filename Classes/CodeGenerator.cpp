#include "CodeGenerator.h"

void CodeGenerator::execute(const ExprNode* node) {
    if (auto blockNode = dynamic_cast<const BlockNode*>(node)) {
        executeBlock(blockNode);
    }
    else {
        evaluate(node);
    }
}

void CodeGenerator::executeBlock(const BlockNode* blockNode) {
    for (const auto& statement : blockNode->getStatements()) {
        evaluate(statement.get());
    }
}

Value CodeGenerator::evaluate(const ExprNode* node) {
    // check if node is empty and return None
    if (!node) {
		return std::monostate();
	}


    if (auto strNode = dynamic_cast<const StringNode*>(node)) {
        return strNode->getValue();
    }
    else if (auto doubleNode = dynamic_cast<const DoubleNode*>(node)) {
        return doubleNode->getValue();
    }
    else if (auto boolNode = dynamic_cast<const BooleanNode*>(node)) {
        return boolNode->getValue();
    }
    else if (auto intNode = dynamic_cast<const IntegerNode*>(node)) {
        return intNode->getValue();
    }
    else if (auto varNode = dynamic_cast<const VariableNode*>(node)) {
        auto it = variables.find(varNode->getName());
        if (it != variables.end()) {
            return it->second;
        }
        throw std::runtime_error("Undefined variable: " + varNode->getName());
    }
    else if (auto assignNode = dynamic_cast<const AssignNode*>(node)) {
        Value value = evaluate(assignNode->getValue().get());
        variables[assignNode->getName()] = value;
        return value;
    }
    else if (auto binNode = dynamic_cast<const BinaryExprNode*>(node)) {
        Value left = evaluate(binNode->getLeft().get());
        Value right = evaluate(binNode->getRight().get());
        return performBinaryOperation(binNode, left, right);
    }
    else if (auto unNode = dynamic_cast<const UnaryExprNode*>(node)) {
        Value operand = evaluate(unNode->getOperand().get());
        return performUnaryOperation(unNode->getToken(), unNode->getOp(), operand);
    }
    else if (auto prNode = dynamic_cast<const PrintNode*>(node)) {
        Value value = evaluate(prNode->getExpression().get());
		printValue(value);
		return value;
    }
    else if (auto inNode = dynamic_cast<const InputNode*>(node)) {
        Value value = evaluate(inNode->getExpression().get());
        std::string input;
        std::getline(std::cin, input);
		return input;
	}
    else if (auto ifNode = dynamic_cast<const IfNode*>(node)) {
        Value condition = evaluate(ifNode->getCondition().get());
        auto thenBlock = ifNode->getThenBlock().get();
        auto elseBlock = ifNode->getElseBlock().get();
        if (ValueHelper::asBool(condition)) {
			return evaluate(thenBlock);
		}
        else if (elseBlock) {
			return evaluate(elseBlock);
		}

        return std::monostate();
    }
    else if (auto whileNode = dynamic_cast<const WhileNode*>(node)) {
        while (true) {
            Value condition = evaluate(whileNode->getCondition().get());
            if (!ValueHelper::asBool(condition)) {
                break;
            }
            evaluate(whileNode->getBlock().get());

            // Re-evaluate condition immediately after executing the block
            condition = evaluate(whileNode->getCondition().get());
            if (!ValueHelper::asBool(condition)) {
                break;
            }
        }
        return std::monostate();
    }
    else if (auto blockNode = dynamic_cast<const BlockNode*>(node)) {
		executeBlock(blockNode);
		return std::monostate();
	}

    throw std::runtime_error("Unsupported node type");
}

Value CodeGenerator::performBinaryOperation(auto binNode, const Value& left, const Value& right) {
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
        else {
            throw std::runtime_error("Arithmetic Operation Error: Unsupported for types " + ValueHelper::type(left) + " and " + ValueHelper::type(right) +
            " at line " + line);
        }
    }


    if (token.type == TokenType::COMPARISON) {
        return performComparisonOperation(token, op, left, right);
    }

    if (token.type == TokenType::LOGICAL) {
        if (std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right)) {
            return performLogicalOperation(token, op, std::get<bool>(left), std::get<bool>(right));
        }
    }

    throw std::runtime_error("Arithmetic Operation Error: Type mismatch or unsupported operation " + op + " at line " + line);
}

Value CodeGenerator::performArithmeticOperation(const Token token, const std::string& op, const double left, const double right) {
    std::string line = std::to_string(token.line);
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if (right == 0) throw std::runtime_error("Arithmetic Operation Error: Division by zero at line " + line);
        return left / right;
    }
    throw std::runtime_error("Arithmetic Operation Error: Invalid Operator " + op + " at line " + line);
}

Value CodeGenerator::performStringOperation(const Token token, const std::string& op, const Value& left, const Value& right) {
	std::string line = std::to_string(token.line);
	if (op == "+") return ValueHelper::asString(left) + ValueHelper::asString(right);
	throw std::runtime_error("String Operation Error: Invalid Operator " + op + " at line " + line);
}

Value CodeGenerator::performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right) {
    std::string line = std::to_string(token.line);
    if (op == "==") return left == right;
    if (op == "!=") return left != right;
    // check if the values are of type double or int
    if (ValueHelper::isDouble(left) || ValueHelper::isDouble(right) || ValueHelper::isInt(left) || ValueHelper::isInt(right)) {
        double l = ValueHelper::isDouble(left) ? ValueHelper::asDouble(left) : ValueHelper::asInt(left);
        double r = ValueHelper::isDouble(right) ? ValueHelper::asDouble(right) : ValueHelper::asInt(right);

        if (op == "<") return l < r;
        if (op == "<=") return l <= r;
        if (op == ">") return l > r;
        if (op == ">=") return l >= r;
	}
    throw std::runtime_error("Comparison Operation Error: Unsupported comparison operator " + op + " at line " + line);
}

Value CodeGenerator::performLogicalOperation(const Token token, const std::string& op, bool left, bool right) {
    std::string line = std::to_string(token.line);
    if (op == "and") return left && right;
    if (op == "or") return left || right;

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
    if (std::holds_alternative<int>(value)) 
    {
		std::cout << std::get<int>(value) << std::endl;
	}
    else if (std::holds_alternative<double>(value)) 
    {
        std::cout << std::get<double>(value) << std::endl;
    }
    else if (std::holds_alternative<bool>(value)) {
        std::cout << std::boolalpha << std::get<bool>(value) << std::endl;
    }
    else if (std::holds_alternative<std::string>(value)) {
        std::cout << std::get<std::string>(value) << std::endl;
    }
    else if (std::holds_alternative<std::monostate>(value)) {
        std::cout << "None" << std::endl;
    }
    else {
        throw std::runtime_error("Unsupported value type");
    }
}
