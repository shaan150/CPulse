// Purpose: Define the TokenType enum class and a function to convert TokenType to a readable string.
// TokenTypes.h
#pragma once
#include <string>

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    EOL,
    EOFI,
};

// Optional: Function to convert TokenType to a readable string
std::string tokenTypeToString(TokenType type);
