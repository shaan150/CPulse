#pragma once
#include <unordered_map>
#include <Value.h>

struct FunctionContext {
    std::unordered_map<std::string, Value> locals;
    Value returnValue;
};