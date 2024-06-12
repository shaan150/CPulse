#pragma once
#include <string>
#include "TokenType.h"

struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;

    Token(TokenType type, std::string value, size_t line = 0, size_t column = 0)
        : type(type), value(std::move(value)), line(line), column(column) {}

    // To be able to compare the token
    bool operator==(const Token& other) const {
		return type == other.type && value == other.value && line == other.line && column == other.column;
	}

    bool operator!=(const Token& other) const {
		return !(*this == other);
	}

    // To be able to copy the token
    Token(const Token& other) = default;
};

