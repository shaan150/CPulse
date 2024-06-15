#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <Function/FunctionContext.h>
#include <stack>
#include <AST/AST.h>
#include <Function/Function.h>
#include <Value/Value.h>
#include <unordered_map>
#include <memory>
#include <string>

class CodeGenerator; // Forward declaration

/**
 * @class FunctionHandler
 * @brief Manages function definitions and calls.
 */
class FunctionHandler {
public:
    /**
     * @brief Adds a function to the handler.
     * @param name The name of the function.
     * @param function The function to add.
     */
    void addFunction(const std::string& name, std::unique_ptr<Function> function);

    /**
     * @brief Calls a function.
     * @param functionCallNode The function call node containing the function name and arguments.
     * @param generator The code generator used for evaluating the function.
     * @return The result of the function call.
     *
     * This function looks up the function by name, checks the argument count,
     * sets up the function context, evaluates the function body, and returns
     * the result.
     *
     * @throws std::runtime_error If the function is undefined or there is an argument count mismatch.
     */
    Value callFunction(const FunctionCallNode* functionCallNode, CodeGenerator& generator);

private:
    std::unordered_map<std::string, std::unique_ptr<Function>> functions; ///< Map of function names to function objects
    std::stack<FunctionContext> currentFunctionContext; ///< Stack of function contexts for nested function calls

    friend Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
    friend Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);
    friend Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);
    friend Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode);
    friend Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token);
};

#endif // FUNCTIONHANDLER_H
