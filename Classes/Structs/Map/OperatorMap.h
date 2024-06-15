#pragma once
#include "TokenType.h"
#include <unordered_map>
#include <string>

/**
 * @struct OperatorMap
 * @brief Holds a static map of operator characters to their corresponding TokenType.
 */
struct OperatorMap {
    /**
     * @brief A static unordered map that associates operator characters with their corresponding TokenType.
     *
     * The map includes common operators used in programming languages such as arithmetic operators ('+', '-', '*', '/'),
     * comparison operators ('<', '>', '=', '!', etc.), and logical operators ('&', '|', '^', etc.).
     */
    static const std::unordered_map<char, TokenType> map;
};
