#include "FunctionNodeEvaluator.h"
#include "CodeGenerator.h"
#include "Evaluator.h"
#include <stdexcept>

void FunctionNodeEvaluator::registerFunction(CodeGenerator& generator, std::unique_ptr<Function> function) {
    generator.functions[function->name] = std::move(function);
}

Value FunctionNodeEvaluator::callFunction(CodeGenerator& generator, const std::string& name, const std::vector<Value>& args) {
    auto it = generator.functions.find(name);
    if (it == generator.functions.end()) {
        throw std::runtime_error("Function not found: " + name);
    }
    generator.currentFunctionContext.push(FunctionContext());

    // Set up function parameters in the context
    const auto& function = it->second;
    for (size_t i = 0; i < args.size(); ++i) {
//        generator.currentFunctionContext.top().locals[function->params[i]->getName()] = args[i];
    }

    // Execute the function's block
    evaluate(function->block.get(), generator);
    Value returnValue = generator.currentFunctionContext.top().returnValue;
    generator.currentFunctionContext.pop();
    return returnValue;
}

void FunctionNodeEvaluator::setReturnValue(CodeGenerator& generator, const Value& value) {
    if (generator.currentFunctionContext.empty()) {
        throw std::runtime_error("Return statement not inside a function");
    }
    generator.currentFunctionContext.top().returnValue = value;
}

Value FunctionNodeEvaluator::getReturnValue(const CodeGenerator& generator) const {
    if (generator.currentFunctionContext.empty()) {
        throw std::runtime_error("No function context available");
    }
    return generator.currentFunctionContext.top().returnValue;
}
