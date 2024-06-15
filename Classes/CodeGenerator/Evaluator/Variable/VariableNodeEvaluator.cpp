#include "VariableNodeEvaluator.h"
#include "CodeGenerator/CodeGenerator.h"
#include "Function/Function.h"
#include "CodeGenerator/Evaluator/Handler/FunctionHandler.h"
#include <stdexcept>

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode) {
    std::string name = varNode->getName();
    std::string line = std::to_string(varNode->getToken().line);
    // Check the current function context first
    if (!generator.functionHandler->currentFunctionContext.empty()) {
        auto& context = generator.functionHandler->currentFunctionContext.top().variables;
        auto it = context.find(name);
        if (it != context.end()) {
            return it->second;
        }
    }

    // Fall back to global variables if not found in the function context
    auto it = generator.variables.find(name);
    if (it != generator.variables.end()) {
        return it->second;
    }

    throw std::runtime_error("Variable Error: Undefined variable " + name);
}

Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode) {
    // Check the current function context first

    const std::string name = assignNode->getName();
    const std::string line = std::to_string(assignNode->getToken().line);
    const Value value = evaluate(assignNode->getValue().get(), generator);

    if (!generator.functionHandler->currentFunctionContext.empty()) {
		auto& context = generator.functionHandler->currentFunctionContext.top().variables;
		auto it = context.find(name);
        if (it != context.end()) {
			it->second = value;
			return value;
		}
	}

    generator.variables[name] = value;
    return value;
}