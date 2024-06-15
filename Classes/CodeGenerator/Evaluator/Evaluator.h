#pragma once
#include "CodeGenerator/CodeGenerator.h"
#include "CodeGenerator/Evaluator/Primitive/PrimitiveNodeEvaluator.h"

/**
 * @brief Evaluates the given expression node.
 *
 * This function evaluates various types of expression nodes, including literals, variables,
 * lists, assignments, binary and unary expressions, print and input statements, control flow
 * statements, type casts, function definitions, and function calls. It delegates the evaluation
 * to specific functions based on the type of node.
 *
 * @param node Pointer to the expression node to be evaluated.
 * @param generator Reference to the CodeGenerator.
 * @return The evaluated value of the expression node.
 * @throws std::runtime_error if the node type is unsupported or if there is a syntax error.
 */
Value evaluate(const ExprNode* node, CodeGenerator& generator);