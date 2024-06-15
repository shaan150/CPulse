#pragma once
#include "TokenType.h"
#include <unordered_map>
#include <string>

struct OperatorMap {
    static const std::unordered_map<char, TokenType> map;
};