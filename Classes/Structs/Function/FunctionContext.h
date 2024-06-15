#pragma once
#include <unordered_map>
#include "Value/Value.h"

/**
 * @struct FunctionContext
 * @brief Represents the context of a function during its execution, including variables, return value, and control flags.
 */
struct FunctionContext {
    std::unordered_map<std::string, Value> variables; ///< Variables defined within the function's scope.

    const std::string* returnType; ///< Pointer to the function's return type.
    bool returnFlag = false; ///< Flag indicating if a return statement has been executed.
    Value returnValue; ///< The value to be returned by the function.
    const std::string* functionName; ///< Pointer to the function's name.
};
