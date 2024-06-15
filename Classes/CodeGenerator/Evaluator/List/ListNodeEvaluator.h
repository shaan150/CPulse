#pragma once

#include <CodeGenerator/CodeGenerator.h>
#include <Value/ValueHelper.h>
#include <AST/AST.h>

/**
 * @brief Evaluates a node that initializes a list.
 * @param generator The code generator used for evaluation.
 * @param listNode The list initialization node.
 * @return A Value representing the result of the list initialization.
 *
 * This function initializes a list with a specified element type and stores it
 * in the appropriate context.
 */
Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode);

/**
 * @brief Evaluates a node that appends an element to a list.
 * @param generator The code generator used for evaluation.
 * @param listAppendNode The list append node.
 * @return A Value representing the result of the list append operation.
 *
 * This function appends an element to a list, ensuring type compatibility.
 */
Value evaluateListAppendNode(CodeGenerator& generator, const ListAppendNode* listAppendNode);

/**
 * @brief Evaluates a node that pops an element from a list.
 * @param generator The code generator used for evaluation.
 * @param listPopNode The list pop node.
 * @return A Value representing the element that was popped from the list.
 *
 * This function removes an element from a list at the specified index and returns it.
 */
Value evaluateListPopNode(CodeGenerator& generator, const ListPopNode* listPopNode);

/**
 * @brief Evaluates a node that gets the length of a list.
 * @param generator The code generator used for evaluation.
 * @param listLengthNode The list length node.
 * @return A Value representing the length of the list.
 *
 * This function returns the number of elements in a list.
 */
Value evaluateListLengthNode(CodeGenerator& generator, const ListLengthNode* listLengthNode);

/**
 * @brief Evaluates a node that accesses an element in a list by index.
 * @param generator The code generator used for evaluation.
 * @param listIndexNode The list index node.
 * @return A Value representing the element at the specified index in the list.
 *
 * This function accesses an element in a list by its index and returns it.
 */
Value evaluateListIndexNode(CodeGenerator& generator, const ListIndexNode* listIndexNode);

/**
 * @brief Evaluates a node that replaces an element in a list at a specified index.
 * @param generator The code generator used for evaluation.
 * @param listReplaceNode The list replace node.
 * @return A Value representing the result of the list replace operation.
 *
 * This function replaces an element in a list at the specified index with a new value.
 */
Value evaluateListReplaceNode(CodeGenerator& generator, const ListReplaceNode* listReplaceNode);

/**
 * @brief Retrieves the value of a list from the code generator.
 * @param generator The code generator used for evaluation.
 * @param name The name of the list.
 * @param token The token associated with the list.
 * @return The value of the list.
 *
 * This function retrieves the value of a list from the code generator's context, throwing an error if the list is undefined.
 */
Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token);
