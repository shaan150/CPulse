#pragma once
#include <string>
#include "TokenTypes.h"
#include "Token.h"
#include <VariableTypes.h>
#include <ScopeTypes.h>

struct VariableToken : public Token {
    VariableType dataType;
    ScopeType scope;

    VariableToken(std::string value, ScopeType scope, size_t line = 0, size_t column = 0)
        : Token(TokenType::VARIABLE, std::move(value), line, column), dataType(dataType), scope(scope) {}

    // To be able to compare the variable token
    bool operator==(const VariableToken& other) const {
        return Token::operator==(other) && dataType == other.dataType && scope == other.scope;
    }

    bool operator!=(const VariableToken& other) const {
        return !(*this == other);
    }

    // To be able to copy the variable token
    VariableToken(const VariableToken& other) = default;
};