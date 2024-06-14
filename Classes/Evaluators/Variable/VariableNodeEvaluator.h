#pragma once
#include "CodeGenerator.h"

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);