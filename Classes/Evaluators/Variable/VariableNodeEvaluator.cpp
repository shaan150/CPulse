#include "VariableNodeEvaluator.h"

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode) {
    auto it = generator.variables.find(varNode->getName());
    if (it != generator.variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Syntax Error: Undefined variable " + varNode->getName() + " at line " + std::to_string(varNode->getToken().line));
}

Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode) {
    Value value = evaluate(assignNode->getValue().get(), generator);
    generator.variables[assignNode->getName()] = value;
    return value;
}