#pragma once

#include "Value/ValueHelper.h"
#include "CodeGenerator/CodeGenerator.h"

/**
 * @brief Evaluates a print node and outputs the result.
 * @param generator The code generator used for evaluation.
 * @param prNode The print node to evaluate.
 * @return The value that was printed.
 *
 * This function evaluates the expression within the print node, prints its value,
 * and then returns the value.
 */
Value evaluatePrintNode(CodeGenerator& generator, const PrintNode* prNode);

/**
 * @brief Evaluates an input node and captures user input.
 * @param generator The code generator used for evaluation.
 * @param inNode The input node to evaluate.
 * @return The value entered by the user.
 *
 * This function evaluates the expression within the input node, prompts the user for input,
 * and then returns the input as a string value.
 */
Value evaluateInputNode(CodeGenerator& generator, const InputNode* inNode);
