#pragma once
#include "CodeGenerator/CodeGenerator.h"

/**
 * @brief Evaluates a string node.
 * @param strNode The string node to evaluate.
 * @return A Value representing the string value of the node.
 *
 * This function retrieves the string value from a StringNode and returns it as a Value.
 */
Value evaluateStringNode(const StringNode* strNode);

/**
 * @brief Evaluates a double node.
 * @param doubleNode The double node to evaluate.
 * @return A Value representing the double value of the node.
 *
 * This function retrieves the double value from a DoubleNode and returns it as a Value.
 */
Value evaluateDoubleNode(const DoubleNode* doubleNode);

/**
 * @brief Evaluates a boolean node.
 * @param boolNode The boolean node to evaluate.
 * @return A Value representing the boolean value of the node.
 *
 * This function retrieves the boolean value from a BooleanNode and returns it as a Value.
 */
Value evaluateBooleanNode(const BooleanNode* boolNode);

/**
 * @brief Evaluates an integer node.
 * @param intNode The integer node to evaluate.
 * @return A Value representing the integer value of the node.
 *
 * This function retrieves the integer value from an IntegerNode and returns it as a Value.
 */
Value evaluateIntegerNode(const IntegerNode* intNode);
