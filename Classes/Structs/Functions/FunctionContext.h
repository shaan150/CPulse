#pragma once
#include <unordered_map>
#include <Value.h>

struct FunctionContext {
    std::unordered_map<std::string, Value> variables;
    // save the return value of the function
    const std::string* returnType;
    bool returnFlag = false;
    Value returnValue;
    const std::string* functionName;
};