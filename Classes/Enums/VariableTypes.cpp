#include "VariableTypes.h"
#include <vector>
#include <stdexcept>

std::string VariableTypesToString(VariableType type)
{
	switch (type) {
	case VariableType::STRING: return "string";
	case VariableType::BOOLEAN: return "bool";
	case VariableType::NUMBER: return "num";
	case VariableType::NONE: return "none";
	default: return "Undefined";
	}
}

VariableType StringToVariableType(std::string type)
{
	if (type == "string") {
		return VariableType::STRING;
	}
	else if (type == "bool") {
		return VariableType::BOOLEAN;
	}
	else if (type == "num") {
		return VariableType::NUMBER;
	}
	else {
		return VariableType::NONE;
	}
}

bool isVariableType(std::string type)
{
	for (VariableType varType : All) {
		if (VariableTypesToString(varType) == type) {
			return true;
		}
	}

	return false;
}

bool checkVariableType(VariableType type, std::string value)
{
	switch (type) {
		case VariableType::STRING:
			// Check if the value is a string
			return value.front() == '"' && value.back() == '"';
		case VariableType::BOOLEAN:
			// Check if the value is a boolean
			return value == "true" || value == "false";
		case VariableType::NUMBER:
			// Check if the value is a number
			try {
				std::stod(value);
				return true;
			}
			catch (std::invalid_argument arg) {
				return false;
			}
		default:
			return false;
	}
}
