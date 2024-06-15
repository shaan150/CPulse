#include "ControlFlowEvaluator.h"

Value evaluateIfNode(CodeGenerator& generator, const IfNode* ifNode) {
    Value condition = evaluate(ifNode->getCondition().get(), generator);
    auto thenBlock = ifNode->getThenBlock().get();
    auto elseBlock = ifNode->getElseBlock().get();
    if (ValueHelper::asBool(condition)) {
        return evaluate(thenBlock, generator);
    }
    else if (elseBlock) {
        return evaluate(elseBlock, generator);
    }
    return std::monostate();
}

Value evaluateWhileNode(CodeGenerator& generator, const WhileNode* whileNode) {
    while (ValueHelper::asBool(evaluate(whileNode->getCondition().get(), generator))) {
        for (const auto& statement : whileNode->getBlock()->getStatements()) {
            evaluate(statement.get(), generator);
            auto condition = evaluate(whileNode->getCondition().get(), generator);
            bool isTrue = ValueHelper::asBool(condition);
            if (!ValueHelper::asBool(evaluate(whileNode->getCondition().get(), generator))) {
                break;
            }
        }
        if (!ValueHelper::asBool(evaluate(whileNode->getCondition().get(), generator))) {
            break;
        }
    }
    return std::monostate();
}

Value evaluateBlockNode(CodeGenerator& generator, const BlockNode* blockNode)
{
    generator.executeBlock(blockNode);
    return std::monostate();
}
