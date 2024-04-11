#pragma once
#include <string>
#include "TokenTypes.h"

struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;

    Token(TokenType type, std::string value, size_t line = 0, size_t column = 0)
        : type(type), value(std::move(value)), line(line), column(column) {}
};

