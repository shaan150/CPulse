#pragma once

#include "Value/ValueHelper.h"
#include "CodeGenerator/CodeGenerator.h"

/**
 * @brief Evaluates an if-node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param ifNode The if-node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateIfNode(CodeGenerator& generator, const IfNode* ifNode);

/**
 * @brief Evaluates a while-node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param whileNode The while-node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateWhileNode(CodeGenerator& generator, const WhileNode* whileNode);

/**
 * @brief Evaluates a block-node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param blockNode The block-node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateBlockNode(CodeGenerator& generator, const BlockNode* blockNode);
