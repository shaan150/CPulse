#ifndef FUNCTION_NODE_EVALUATOR_H
#define FUNCTION_NODE_EVALUATOR_H

#include "Value/Value.h"

class ExprNode;
class CodeGenerator;
class FunctionCallNode;
class FunctionDefNode;

/**
 * @class FunctionNodeEvaluator
 * @brief Evaluator for function nodes in the AST.
 */
class FunctionNodeEvaluator {
public:
    /**
     * @brief Evaluates a function call node in the AST.
     * @param generator The code generator used for evaluating the node.
     * @param functionCallNode The function call node to evaluate.
     * @return The result of the evaluation.
     */
    Value evaluateFunctionCallNode(CodeGenerator* generator, const FunctionCallNode* functionCallNode);

    /**
     * @brief Evaluates a function definition node in the AST.
     * @param generator The code generator used for evaluating the node.
     * @param functionNode The function definition node to evaluate.
     * @return The result of the evaluation.
     */
    Value evaluateFunctionDefNode(CodeGenerator* generator, const FunctionDefNode* functionNode);
};

#endif // FUNCTION_NODE_EVALUATOR_H
