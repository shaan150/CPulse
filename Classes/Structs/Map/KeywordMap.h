#pragma once
#include "TokenType.h"
#include <unordered_map>
#include <string>

/**
 * @struct KeywordMap
 * @brief Holds a static map of keywords to their corresponding TokenType.
 */
struct KeywordMap
{
    /**
     * @brief A static unordered map that associates keyword strings with their corresponding TokenType.
     *
     * The map includes common programming language keywords such as "if", "else", "while", "true", "false", and data types
     * like "int", "double", "string", and "bool". It also includes logical operators "and", "or", "not", as well as
     * function-related keywords "func" and "return".
     */
    static const std::unordered_map<std::string, TokenType> map;
};
