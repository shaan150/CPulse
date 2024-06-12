#include "OperatorMap.h"

const std::unordered_map<char, TokenType> OperatorMap::map = {
    {'+', TokenType::ARITHMETIC},
    {'-', TokenType::ARITHMETIC},
    {'*', TokenType::ARITHMETIC},
    {'/', TokenType::ARITHMETIC},
    {'=', TokenType::EQUAL},
    {'!', TokenType::COMPARISON},
    {'<', TokenType::COMPARISON},
    {'>', TokenType::COMPARISON},
    {'%', TokenType::ARITHMETIC},
    {'(', TokenType::LPARENTHESIS},
    {')', TokenType::RPARENTHESIS},
    {'[', TokenType::LBRACKET},
    {']', TokenType::RBRACKET},
    {'{', TokenType::LBRACE},
    {'}', TokenType::RBRACE}
};