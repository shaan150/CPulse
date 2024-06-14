#include "FunctionHandler.h"
#include <Evaluator.h>
#include <stdexcept>
#include <ValueHelper.h>

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
    currentFunctionContext.push(context);

    // Execute the function body
    Value result = evaluate(function->getBody().get(), generator);

    // Validate return type
    if (function->getReturnType() != "void") {
        bool hasReturnStatement = false;
        for (const auto& statement : function->getBody()->getStatements()) {
            if (auto returnNode = dynamic_cast<ReturnNode*>(statement.get())) {
                hasReturnStatement = true;
                std::string actualReturnType = ValueHelper::type(result);
                if (function->getReturnType() != actualReturnType) {
                    throw std::runtime_error("Type Error: Return type mismatch in function '" + functionCallNode->getName() + "'");
                }
            }
        }

        if (!hasReturnStatement) {
            throw std::runtime_error("Runtime Error: Missing return statement in function '" + functionCallNode->getName() + "'");
        }
    }

    // Pop the function context from the stack
    currentFunctionContext.pop();

    return result;
}