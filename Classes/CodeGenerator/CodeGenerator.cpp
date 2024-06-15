#include "CodeGenerator/CodeGenerator.h"
#include "Evaluator/Handler/FunctionHandler.h"
#include "Value/ValueHelper.h"

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
    return OperationDispatcher::dispatchOperation(binNode, left, right);
}

Value CodeGenerator::performUnaryOperation(const Token& token, const std::string& op, const Value& operand) {
    return UnaryOperations::performUnaryOperation(token, op, operand);
}

void CodeGenerator::printValue(const Value& value) {
    PrintOperations::printValue(value);
}