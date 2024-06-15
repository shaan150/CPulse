#ifndef FUNCTION_NODE_EVALUATOR_H
#define FUNCTION_NODE_EVALUATOR_H

#include "Value/Value.h"

class ExprNode;
class CodeGenerator;
class FunctionCallNode;
class FunctionDefNode;

class FunctionNodeEvaluator {
public:
    Value evaluateFunctionCallNode(CodeGenerator* generator, const FunctionCallNode* functionCallNode);
    Value evaluateFunctionDefNode(CodeGenerator* generator, const FunctionDefNode* functionNode);
};

#endif // FUNCTION_NODE_EVALUATOR_H