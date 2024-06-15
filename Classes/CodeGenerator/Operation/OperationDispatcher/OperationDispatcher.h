#ifndef OPERATIONDISPATCHER_H
#define OPERATIONDISPATCHER_H

#include "Token/Token.h"
#include "Value/ValueHelper.h"
#include "AST/AST.h"
#include <CodeGenerator/Operation/ArithmeticOperations/ArithmeticOperations.h>
#include <CodeGenerator/Operation/StringOperations/StringOperations.h>
#include <CodeGenerator/Operation/ComparisonOperations/ComparisonOperations.h>
#include <CodeGenerator/Operation/LogicalOperations/LogicalOperations.h>

/**
 * @class OperationDispatcher
 * @brief Dispatches and performs operations based on the type of the token.
 */
class OperationDispatcher {
public:
    /**
     * @brief Dispatches the appropriate operation based on the binary expression node and operand values.
     * @param binNode Pointer to the binary expression node.
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the dispatched operation.
     * @throws std::runtime_error if the operation type is unsupported or if there is a type mismatch.
     */
    static Value dispatchOperation(const BinaryExprNode* binNode, const Value& left, const Value& right);
};

#endif // OPERATIONDISPATCHER_H
