#pragma once
#include <variant>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <stack>
#include "AST.h"
#include "Value.h"
#include "Structs/Functions/Function.h"
#include <Functions/FunctionContext.h>

// Forward declaration to avoid cyclic dependency
class CodeGenerator;

#include "Evaluator.h"


class CodeGenerator {
public:
    // Executes the AST and outputs the result
    void execute(const ExprNode* root);


private:
    std::unordered_map<std::string, Value> variables;
    std::unordered_map<std::string, std::unique_ptr<Function>> functions;
    std::stack<FunctionContext> currentFunctionContext;
    
    void executeBlock(const BlockNode* blockNode);

    Value performBinaryOperation(const BinaryExprNode* binNode, const Value& left, const Value& right);
    Value performArithmeticOperation(const Token token, const std::string& op, const double left, const double right);
    Value performStringOperation(const Token token, const std::string& op, const Value& left, const Value& right);
    Value performComparisonOperation(const Token& token, const std::string& op, const Value& left, const Value& right);
    Value performLogicalOperation(const Token token, const std::string& op, bool left, bool right);
    Value performUnaryOperation(const Token& token, const std::string& op, const Value& operand);
    void printValue(const Value& value);

    // grant access to private members
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

    friend class FunctionNodeEvaluator;

};