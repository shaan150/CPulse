#include "CodeGenerator.h"
#include <ValueHelper.h>

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
        throw std::runtime_error("Syntax Error: Undefined variable " + varNode->getName() + " at line " + std::to_string(varNode->getToken().line));
    }
    else if (auto listNode = dynamic_cast<const ListInitNode*>(node)) {
        // Get the type of the list
        std::string type = listNode->getElementType();

        if (type != "int" && type != "double" && type != "bool" && type != "string") {
            throw std::runtime_error("Syntax Error: Unsupported type for list at line " + std::to_string(listNode->getToken().line));
        }

        // Create the TypedVector
        std::shared_ptr<TypedVector> list = std::make_shared<TypedVector>(type);

        // Check if the list already exists in the variables map
        if (variables.find(listNode->getName()) != variables.end()) {
            throw std::runtime_error("Syntax Error: List " + listNode->getName() + " already exists at line " + std::to_string(listNode->getToken().line));
        }

        // Add the list to the variables map
        variables.insert({ listNode->getName(), list });

        return std::monostate();
    }
    else if (auto listAppendNode = dynamic_cast<const ListAppendNode*>(node)) {
        std::string line = std::to_string(listAppendNode->getToken().line);
        std::string name = listAppendNode->getListName();
        auto it = variables.find(name);
        if (it == variables.end()) {
            throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
        }

        Value& list = it->second;
        Value value = evaluate(listAppendNode->getValue().get());

        if (ValueHelper::isVector(list)) {
            std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
            if (vec->getElementType() != ValueHelper::type(value)) {
                throw std::runtime_error("Syntax Error: Type mismatch in list " + name + " at line " + line);
            }
            vec->push_back(value);
        }
        else {
            throw std::runtime_error("Syntax Error: " + name + " is not a list at line " + line);
        }

        return std::monostate();
    }
    else if (auto listPopNode = dynamic_cast<const ListPopNode*>(node)) {
        std::string line = std::to_string(listPopNode->getToken().line);
        std::string name = listPopNode->getListName();
        int index = ValueHelper::asInt(evaluate(listPopNode->getIndex().get()));
        auto it = variables.find(name);
        if (it == variables.end()) {
            throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
        }

        Value& list = it->second;

        // Check if the list is a TypedVector
        if (ValueHelper::isVector(list)) {
            std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);

            // Check if the index is out of bounds or list is empty
            if (index < 0 || index >= vec->getValues().size()) {
                throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
            }

            // Get the value to be removed
            Value value = vec->getValues()[index];
            vec->pop(index);
            return value;
        }
        else {
            throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
        }
    }
    else if (auto listLengthNode = dynamic_cast<const ListLengthNode*>(node)) {
		std::string line = std::to_string(listLengthNode->getToken().line);
		std::string name = listLengthNode->getListName();
		auto it = variables.find(name);
        if (it == variables.end()) {
			throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
		}

        int length = 0;

        Value& list = it->second;

        if (ValueHelper::isVector(list)) {
			std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
			length = vec->getValues().size();
		}
        else {
			throw std::runtime_error("Syntax Error: " + name + " is not a list at line " + line);
		}

        return length;
	}
    else if (auto listIndexNode = dynamic_cast<const ListIndexNode*>(node)) {
		std::string line = std::to_string(listIndexNode->getToken().line);
		std::string name = listIndexNode->getListName();
		int index = ValueHelper::asInt(evaluate(listIndexNode->getIndex().get()));
		auto it = variables.find(name);
        if (it == variables.end()) {
			throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
		}

		Value& list = it->second;

        if (ValueHelper::isVector(list)) {
			std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);

            if (index < 0 || index >= vec->getValues().size()) {
				throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
			}

			return vec->getValues()[index];
		}
        else {
			throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
		}
	}
    else if (auto listReplaceNode = dynamic_cast<const ListReplaceNode*>(node)) {
        std::string line = std::to_string(listReplaceNode->getToken().line);
        std::string name = listReplaceNode->getListName();

        // Evaluate the index and value expressions
        int index = ValueHelper::asInt(evaluate(listReplaceNode->getIndex().get()));
        Value value = evaluate(listReplaceNode->getValue().get());

        // Find the list variable
        auto it = variables.find(name);
        if (it == variables.end()) {
            throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
        }

        Value& list = it->second;

        // replace the value using TypedVector replace method

        if (ValueHelper::isVector(list)) {
			std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);

            if (index < 0 || index >= vec->getValues().size()) {
				throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
			}

            if (vec->getElementType() != ValueHelper::type(value)) {
				throw std::runtime_error("Syntax Error: Type mismatch in list " + name + " at line " + line);
			}

			vec->replace(index, value);
		}
        else {
			throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
		}

        return std::monostate();
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
        while (ValueHelper::asBool(evaluate(whileNode->getCondition().get()))) {
            for (const auto& statement : whileNode->getBlock()->getStatements()) {
                evaluate(statement.get());

                // Recheck the while condition after each statement
                if (!ValueHelper::asBool(evaluate(whileNode->getCondition().get()))) {
                    break;
                }
            }

            // If the condition is no longer true, break out of the outer while loop
            if (!ValueHelper::asBool(evaluate(whileNode->getCondition().get()))) {
                break;
            }
        }
        return std::monostate();
        }
    else if (auto blockNode = dynamic_cast<const BlockNode*>(node)) {
		executeBlock(blockNode);
		return std::monostate();
	}
    else if (auto typeCastNode = dynamic_cast<const TypeCastNode*>(node)) {
		Value value = evaluate(typeCastNode->getValue().get());
		std::string type = typeCastNode->getType();
        std::string line = std::to_string(typeCastNode->getToken().line);
        if (type == "int") {
            // convert the value to an integer
            try {
                // check if the value is a double if it is throw an error
                if (ValueHelper::isDouble(value)) {
					throw std::runtime_error("Syntax Error: Cannot convert double to int at line " + line);
				}
				return std::stoi(ValueHelper::asString(value));
			}
            catch (const std::invalid_argument&) {
				throw std::runtime_error("Syntax Error: Cannot convert value to integer at line " + line);
			}
        }
        else if (type == "double") {
			// convert the value to a double
            try {
                return std::stod(ValueHelper::asString(value));
            }
            catch (const std::invalid_argument&) {
				throw std::runtime_error("Syntax Error: Cannot convert value to double at line " + line);
			}

        }
        else if (type == "bool") {
            try {
                // convert the value to a boolean
                return ValueHelper::asBool(value);
            }
            catch (const std::invalid_argument&) {
				throw std::runtime_error("Syntax Error: Cannot convert value to boolean at line " + line);
			}
        }
        else if (type == "string") {
			// convert the value to a string
			return ValueHelper::asString(value);
		}
        else {
			throw std::runtime_error("Syntax Error: Unsupported type cast at line " + line);
		}
    }

    throw std::runtime_error("Syntax Error: Unsupported node type at line " + std::to_string(node->getToken().line));
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
            throw std::runtime_error("Arithmetic Operation Error: Unsupported operation " + op + " with types " + ValueHelper::type(left)
                + " and " + ValueHelper::type(right) + " at line " + line);
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
    double result;

    if (op == "+") result = left + right;
    else if (op == "-") result = left - right;
    else if (op == "*") result = left * right;
    else if (op == "/") {
        if (right == 0) throw std::runtime_error("Arithmetic Operation Error: Division by zero at line " + line);
        result = left / right;
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
