#include "FunctionHandler.h"
#include <stdexcept>
#include <CodeGenerator/Evaluator/Evaluator.h>


void FunctionHandler::addFunction(const std::string& name, std::unique_ptr<Function> function) {
    functions[name] = std::move(function);
}

Value FunctionHandler::callFunction(const FunctionCallNode* functionCallNode, CodeGenerator& generator) {
    auto it = functions.find(functionCallNode->getName());
    if (it == functions.end()) {
        throw std::runtime_error("Runtime Error: Undefined function " + functionCallNode->getName());
    }

    Function* function = it->second.get();
    const auto& params = function->getParameters();
    const auto& args = functionCallNode->getArgs();

    if (params.size() != args.size()) {
        throw std::runtime_error("Runtime Error: Argument count mismatch in function call " + functionCallNode->getName());
    }

    // Create a new function context and push it onto the stack
    FunctionContext context;
    for (size_t i = 0; i < params.size(); ++i) {
        context.variables[params[i].name] = evaluate(args[i].get(), generator);
    }
    context.returnType = &function->getReturnType();
    context.functionName = &function->getName();
    currentFunctionContext.push(context);


    // Execute the function body
    evaluate(function->getBody().get(), generator);

    // get return value from currentFunctionContext
    Value result = currentFunctionContext.top().returnValue;

    // Pop the function context from the stack
    currentFunctionContext.pop();

    return result;
}