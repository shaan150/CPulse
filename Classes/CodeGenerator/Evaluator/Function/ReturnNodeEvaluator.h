#ifndef RETURNNODEEVALUATOR_H
#define RETURNNODEEVALUATOR_H

#include "CodeGenerator/Evaluator/Evaluator.h"
#include "AST/AST.h"
#include "Value/Value.h"

/**
 * @brief Evaluates a return node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param returnNode The return node to evaluate.
 * @return The result of the evaluation.
 *
 * This function checks if the return statement is valid within the context of a function,
 * ensures that the return type matches the expected function return type, sets the return
 * flag, and stores the return value in the function context.
 *
 * @throws std::runtime_error If there is any error related to the return statement, such as
 * missing value, return statement outside of a function, multiple return statements, or type mismatch.
 */
Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);

#endif // RETURNNODEEVALUATOR_H
