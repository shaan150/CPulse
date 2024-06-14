#include "KeywordMap.h"

const std::unordered_map<std::string, TokenType> KeywordMap::map = {
	{"and", TokenType::LOGICAL},
	{"or", TokenType::LOGICAL},
	{"not", TokenType::COMPARISON},
	{"if", TokenType::IF_CONDITION},
	{"else", TokenType::ELSE_CONDITION},
	{"while", TokenType::WHILE_LOOP},
	{"return", TokenType::RETURN},
	{"true", TokenType::BOOLEAN},
	{"false", TokenType::BOOLEAN},
	{"int", TokenType::TYPE},
	{"double", TokenType::TYPE},
	{"string", TokenType::TYPE},
	{"bool", TokenType::TYPE},
	{"void", TokenType::TYPE},
	{"func", TokenType::FUNCTION}
};