#ifndef FUNCTION_NODE_EVALUATOR_H
#define FUNCTION_NODE_EVALUATOR_H

#include <unordered_map>
#include <string>
#include <memory>
#include <stack>
#include "Value.h"
#include <stdexcept>

class CodeGenerator;

class FunctionNodeEvalator;
#include <Functions/Function.h>

class FunctionNodeEvaluator {
public:
    void registerFunction(CodeGenerator& generator, std::unique_ptr<Function> function);
    Value callFunction(CodeGenerator& generator, const std::string& name, const std::vector<Value>& args);
    void setReturnValue(CodeGenerator& generator, const Value& value);
    Value getReturnValue(const CodeGenerator& generator) const;

};

#endif FUNCTION_NODE_EVALUATOR_H