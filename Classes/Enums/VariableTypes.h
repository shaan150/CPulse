// Purpose: Define the TokenType enum class and a function to convert TokenType to a readable string.
// TokenTypes.h
#pragma once
#include <string>

enum class VariableType {
    STRING, // "string"
    NUMBER, // 123
    BOOLEAN, // true or false
    NONE // undefined

};

static const VariableType All[] = {VariableType::STRING, VariableType::NUMBER, VariableType::BOOLEAN};

std::string VariableTypesToString(VariableType type);

VariableType StringToVariableType(std::string type);

bool isVariableType(std::string type);

bool checkVariableType(VariableType type, std::string value);