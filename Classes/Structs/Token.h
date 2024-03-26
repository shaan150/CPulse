// Token.h
#pragma once
#include <string>
#include "../Enums/TokenTypes.h"

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}
};