#ifndef VARIABLENODEEVALUATOR_H
#define VARIABLENODEEVALUATOR_H

#include "Value/Value.h"
#include "AST/AST.h"

class CodeGenerator;
class VariableNode;

/**
 * @brief Evaluates a variable node.
 *
 * This function retrieves the value of a variable from either the current function context
 * or the global variables if the variable is not found in the function context.
 *
 * @param generator Reference to the CodeGenerator.
 * @param varNode Pointer to the VariableNode to be evaluated.
 * @return The value of the variable.
 * @throws std::runtime_error if the variable is undefined.
 */
Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);

/**
 * @brief Evaluates an assignment node.
 *
 * This function assigns a value to a variable, either in the current function context or
 * in the global variables if the variable is not found in the function context.
 *
 * @param generator Reference to the CodeGenerator.
 * @param assignNode Pointer to the AssignNode to be evaluated.
 * @return The assigned value.
 */
Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);

#endif // VARIABLENODEEVALUATOR_H
