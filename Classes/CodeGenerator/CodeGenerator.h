#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#include <Value/Value.h>
#include <AST/AST.h>
#include "Operation/OperationDispatcher/OperationDispatcher.h"
#include "Operation/UnaryOperations/UnaryOperations.h"
#include "Utility/PrintOperations.h"

class FunctionHandler;

/**
 * @class CodeGenerator
 * @brief Generates and executes code based on the AST nodes.
 */
class CodeGenerator {
public:
    /**
     * @brief Executes the AST and outputs the result.
     * @param root The root node of the AST.
     */
    void execute(const ExprNode* root);

    /**
     * @brief Constructor for the CodeGenerator class.
     */
    CodeGenerator();

    /**
     * @brief Destructor for the CodeGenerator class.
     */
    ~CodeGenerator();

private:
    std::unordered_map<std::string, Value> variables;
    std::unique_ptr<FunctionHandler> functionHandler;

    /**
     * @brief Executes a block of statements.
     * @param blockNode The block node containing the statements.
     */
    void executeBlock(const BlockNode* blockNode);

    /**
     * @brief Performs a binary operation based on the given binary expression node.
     * @param binNode Pointer to the binary expression node.
     * @param left The left operand value.
     * @param right The right operand value.
     * @return The result of the binary operation.
     */
    Value performBinaryOperation(const BinaryExprNode* binNode, const Value& left, const Value& right);

    /**
     * @brief Performs a unary operation based on the given token and operand.
     * @param token The token representing the unary operator.
     * @param op The unary operator as a string.
     * @param operand The operand value.
     * @return The result of the unary operation.
     */
    Value performUnaryOperation(const Token& token, const std::string& op, const Value& operand);

    /**
     * @brief Prints the given value to the standard output.
     * @param value The value to be printed.
     */
    void printValue(const Value& value);

    // Grant access to private members
    friend Value evaluate(const ExprNode* node, CodeGenerator& generator);
    friend Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
    friend Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);
    friend Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode);
    friend Value evaluateListAppendNode(CodeGenerator& generator, const ListAppendNode* listAppendNode);
    friend Value evaluateListPopNode(CodeGenerator& generator, const ListPopNode* listPopNode);
    friend Value evaluateListLengthNode(CodeGenerator& generator, const ListLengthNode* listLengthNode);
    friend Value evaluateListIndexNode(CodeGenerator& generator, const ListIndexNode* listIndexNode);
    friend Value evaluateListReplaceNode(CodeGenerator& generator, const ListReplaceNode* listReplaceNode);
    friend Value evaluateBinaryExprNode(CodeGenerator& generator, const BinaryExprNode* binNode);
    friend Value evaluateUnaryExprNode(CodeGenerator& generator, const UnaryExprNode* unNode);
    friend Value evaluatePrintNode(CodeGenerator& generator, const PrintNode* prNode);
    friend Value evaluateInputNode(CodeGenerator& generator, const InputNode* inNode);
    friend Value evaluateIfNode(CodeGenerator& generator, const IfNode* ifNode);
    friend Value evaluateWhileNode(CodeGenerator& generator, const WhileNode* whileNode);
    friend Value evaluateBlockNode(CodeGenerator& generator, const BlockNode* blockNode);
    friend Value evaluateTypeCastNode(CodeGenerator& generator, const TypeCastNode* typeCastNode);
    friend Value evaluateFunctionCallNode(CodeGenerator& generator, const FunctionCallNode* functionCallNode);
    friend Value evaluateFunctionDefNode(CodeGenerator& generator, const FunctionDefNode* functionDefNode);
    friend Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);
    friend Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token);

    friend class FunctionNodeEvaluator;
};
