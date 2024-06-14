#include "FunctionHandler.h"
#include "Evaluator.h"
#include "ValueHelper.h"


Value evaluateFunctionCallNode(CodeGenerator& generator, const FunctionCallNode* functionCallNode) {
    FunctionNodeEvaluator evaluator;
    std::vector<Value> args;
    return evaluator.callFunction(generator, functionCallNode->getName(), args);
}