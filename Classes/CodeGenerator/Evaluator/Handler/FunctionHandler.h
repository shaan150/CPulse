#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <Function/FunctionContext.h>
#include <stack>
#include <AST/AST.h>
#include <Function/Function.h>
#include <Value/Value.h>

class CodeGenerator; // Forward declaration

class FunctionHandler {
public:
    void addFunction(const std::string& name, std::unique_ptr<Function> function);
    Value callFunction(const FunctionCallNode* functionCallNode, CodeGenerator& generator);

private:
    std::unordered_map<std::string, std::unique_ptr<Function>> functions;
    std::stack<FunctionContext> currentFunctionContext;

    friend Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
    friend Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);
    friend Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);
    friend Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode);
    friend Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token);
};

#endif // FUNCTIONHANDLER_H