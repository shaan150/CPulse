#include "ReturnNodeEvaluator.h"
#include "ValueHelper.h"
#include "FunctionNodeEvaluator.h"
#include "CodeGenerator.h"
#include "Structs/Functions/Function.h"
#include "Evaluators/Handler/FunctionHandler.h"

Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode) {
    if (!returnNode->getValue()) {
        throw std::runtime_error("Runtime Error: Return statement missing value at line " + std::to_string(returnNode->getToken().line));
    }

    // Evaluate the expression in the return statement
    Value returnValue = evaluate(returnNode->getValue().get(), generator);

    return returnValue;
}