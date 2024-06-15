#pragma once
#include "CodeGenerator/CodeGenerator.h"

Value evaluateStringNode(const StringNode* strNode);
Value evaluateDoubleNode(const DoubleNode* doubleNode);
Value evaluateBooleanNode(const BooleanNode* boolNode);
Value evaluateIntegerNode(const IntegerNode* intNode);