#pragma once
#include "TokenType.h"
#include <unordered_map>
#include <string>

struct KeywordMap
{
	static const std::unordered_map<std::string, TokenType> map;
};