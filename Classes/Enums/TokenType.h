// Purpose: Define the TokenType enum class and a function to convert TokenType to a readable string.
// TokenTypes.h
#pragma once
#include <string>

enum class TokenType {
    INTEGER,
    DOUBLE,
    STRING,
    BOOLEAN,
    TYPE,
    COLON,
    COMMA,
    FUNCTION,
    METHOD_ACCESS,
    LPARENTHESIS,
    RPARENTHESIS,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    ARITHMETIC,
    COMPARISON,
    LOGICAL,
    BITWISE,
    IF_CONDITION,
    ELSE_CONDITION,
    WHILE_LOOP,
    RETURN,
    EQUAL,
    IDENTIFIER,
    EOL,
    EOFI,
    UNKNOWN
};

// Optional: Function to convert TokenType to a readable string
std::string tokenTypeToString(TokenType type);
