#include "IONodeEvaluator.h"

Value evaluatePrintNode(CodeGenerator& generator, const PrintNode* prNode) {
    Value value = evaluate(prNode->getExpression().get(), generator);
    generator.printValue(value);
    return value;
}

Value evaluateInputNode(CodeGenerator& generator, const InputNode* inNode) {
    Value value = evaluate(inNode->getExpression().get(), generator);
    std::string input;
    std::getline(std::cin, input);
    return input;
}