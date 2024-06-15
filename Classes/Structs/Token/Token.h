#pragma once
#include <string>
#include "TokenType.h"

/**
 * @struct Token
 * @brief Represents a token in the input source code, holding its type, value, line number, and column number.
 */
struct Token {
    TokenType type;    ///< The type of the token (e.g., INTEGER, STRING, IDENTIFIER).
    std::string value; ///< The value of the token as a string.
    size_t line;       ///< The line number where the token appears in the source code.
    size_t column;     ///< The column number where the token appears in the source code.

    /**
     * @brief Constructs a Token with the given type, value, line number, and column number.
     * @param type The type of the token.
     * @param value The value of the token as a string.
     * @param line The line number where the token appears (default is 0).
     * @param column The column number where the token appears (default is 0).
     */
    Token(TokenType type, std::string value, size_t line = 0, size_t column = 0)
        : type(type), value(std::move(value)), line(line), column(column) {}

    /**
     * @brief Checks if two tokens are equal.
     * @param other The other token to compare with.
     * @return True if the tokens are equal, false otherwise.
     */
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value && line == other.line && column == other.column;
    }

    /**
     * @brief Checks if two tokens are not equal.
     * @param other The other token to compare with.
     * @return True if the tokens are not equal, false otherwise.
     */
    bool operator!=(const Token& other) const {
        return !(*this == other);
    }

    /**
     * @brief Copy constructor for Token.
     * @param other The other token to copy from.
     */
    Token(const Token& other) = default;
};
