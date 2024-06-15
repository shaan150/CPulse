#pragma once

#include <CodeGenerator/CodeGenerator.h>
#include <AST/AST.h>
#include <Value/ValueHelper.h>

/**
 * @brief Evaluates a binary expression node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param binNode The binary expression node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateBinaryExprNode(CodeGenerator& generator, const BinaryExprNode* binNode);

/**
 * @brief Evaluates a unary expression node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param unNode The unary expression node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateUnaryExprNode(CodeGenerator& generator, const UnaryExprNode* unNode);

/**
 * @brief Evaluates a type cast node in the AST.
 * @param generator The code generator used for evaluating the node.
 * @param typeCastNode The type cast node to evaluate.
 * @return The result of the evaluation.
 */
Value evaluateTypeCastNode(CodeGenerator& generator, const TypeCastNode* typeCastNode);

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
