#include "ReturnNodeEvaluator.h"
#include "ValueHelper.h"
#include "FunctionNodeEvaluator.h"
#include "CodeGenerator.h"
#include "Structs/Functions/Function.h"
#include "Evaluators/Handler/FunctionHandler.h"

Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode) {

    Token token = returnNode->getToken();

    std::string line = std::to_string(token.line);
    if (!returnNode->getValue()) {
        throw std::runtime_error("Runtime Error: Return statement missing value at line " + line);
    }

    // check if function context is empty
    if (generator.functionHandler->currentFunctionContext.empty()) {
		throw std::runtime_error("Runtime Error: Return statement outside of function at line " + line);
	}

    // Get the current function context
    FunctionContext& context = generator.functionHandler->currentFunctionContext.top();

    // check if function return flag is set
    if (context.returnFlag) {
		throw std::runtime_error("Runtime Error: Multiple return statements in function at line " + line);
	}

    // Set the return flag
    context.returnFlag = true;

    if (*context.returnType == "void") {
		throw std::runtime_error("Runtime Error: Return statement with value in void function at line " + line);
	}

    // check if return type matches function return type
    Value returnValue = evaluate(returnNode->getValue().get(), generator);

    if (*context.returnType != ValueHelper::type(returnValue)) {
        throw std::runtime_error("Type Error: Return type mismatch in function at line " + line);
    }

    // save the return value to the function context

    context.returnValue = returnValue;


    return returnValue;
}