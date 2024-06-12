#pragma once

#include <string>

enum class ScopeType
{
	Global,
	Function,
	Block
};

std::string scopeTypeToString(ScopeType type);