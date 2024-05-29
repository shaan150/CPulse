// Purpose: Define the TokenType enum class and a function to convert TokenType to a readable string.
// TokenTypes.h
#pragma once
#include <string>

enum class TokenType {
    NUMBER,
    STRING,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    TRUE,
    FALSE,
    EQUAL_TO,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,
    LOGICAL_AND,
    LOGICAL_OR,
    NOT,
    PRINT,
    IDENTIFIER,
    ASSIGN,
    EOL,
    EOFI
};

// Optional: Function to convert TokenType to a readable string
std::string tokenTypeToString(TokenType type);
