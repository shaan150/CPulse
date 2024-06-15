// Purpose: Define the TokenType enum class and a function to convert TokenType to a readable string.
// TokenTypes.h
#pragma once
#include <string>

/**
 * @enum TokenType
 * @brief Defines various token types that are used in the language parser and interpreter.
 */
enum class TokenType {
    INTEGER,           ///< Represents an integer literal.
    DOUBLE,            ///< Represents a double (floating point) literal.
    STRING,            ///< Represents a string literal.
    BOOLEAN,           ///< Represents a boolean literal (true/false).
    TYPE,              ///< Represents a type identifier (e.g., int, double).
    COLON,             ///< Represents a colon ':' character.
    COMMA,             ///< Represents a comma ',' character.
    FUNCTION,          ///< Represents a function keyword.
    METHOD_ACCESS,     ///< Represents a method access operator '.'.
    LPARENTHESIS,      ///< Represents a left parenthesis '(' character.
    RPARENTHESIS,      ///< Represents a right parenthesis ')' character.
    LBRACKET,          ///< Represents a left bracket '[' character.
    RBRACKET,          ///< Represents a right bracket ']' character.
    LBRACE,            ///< Represents a left brace '{' character.
    RBRACE,            ///< Represents a right brace '}' character.
    ARITHMETIC,        ///< Represents an arithmetic operator (+, -, *, /, %).
    COMPARISON,        ///< Represents a comparison operator (==, !=, <, <=, >, >=).
    LOGICAL,           ///< Represents a logical operator (and, or, not).
    BITWISE,           ///< Represents a bitwise operator (&, |, ^, ~, <<, >>).
    IF_CONDITION,      ///< Represents an 'if' condition keyword.
    ELSE_CONDITION,    ///< Represents an 'else' condition keyword.
    WHILE_LOOP,        ///< Represents a 'while' loop keyword.
    RETURN,            ///< Represents a 'return' keyword.
    EQUAL,             ///< Represents an assignment operator '='.
    IDENTIFIER,        ///< Represents an identifier (variable/function name).
    EOL,               ///< Represents an end-of-line token.
    EOFI,              ///< Represents the end of file/input token.
    UNKNOWN            ///< Represents an unknown or unrecognized token.
};

/**
 * @brief Converts a TokenType enum value to a readable string.
 * @param type The TokenType value to convert.
 * @return A string representation of the TokenType.
 */
std::string tokenTypeToString(TokenType type);
