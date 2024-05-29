#include "ScopeTypes.h"

std::string scopeTypeToString(ScopeType type)
{
	switch (type) {
		case ScopeType::Global:
			return "Global";
		case ScopeType::Function:
			return "Function";
		case ScopeType::Block:
			return "Block";
		default:
			return "Unknown";
	}
}
