#include "VariableNodeEvaluator.h"
#include "CodeGenerator.h"
#include "Structs/Functions/Function.h"
#include "Evaluators/Handler/FunctionHandler.h"
#include <stdexcept>

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode) {
    // Check the current function context first
    if (!generator.functionHandler->currentFunctionContext.empty()) {
        auto& context = generator.functionHandler->currentFunctionContext.top().variables;
        auto it = context.find(varNode->getName());
        if (it != context.end()) {
            return it->second;
        }
    }

    // Fall back to global variables if not found in the function context
    auto it = generator.variables.find(varNode->getName());
    if (it != generator.variables.end()) {
        return it->second;
    }

    throw std::runtime_error("Syntax Error: Undefined variable " + varNode->getName() + " at line " + std::to_string(varNode->getToken().line));
}

Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode) {
    // Check the current function context first

    if (!generator.functionHandler->currentFunctionContext.empty()) {
		auto& context = generator.functionHandler->currentFunctionContext.top().variables;
		auto it = context.find(assignNode->getName());
        if (it != context.end()) {
			Value value = evaluate(assignNode->getValue().get(), generator);
			it->second = value;
			return value;
		}
	}
    Value value = evaluate(assignNode->getValue().get(), generator);
    generator.variables[assignNode->getName()] = value;
    return value;
}