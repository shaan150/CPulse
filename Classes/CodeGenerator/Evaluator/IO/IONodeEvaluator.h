#pragma once
#include "Value/ValueHelper.h"
#include "CodeGenerator/CodeGenerator.h"

Value evaluatePrintNode(CodeGenerator& generator, const PrintNode* prNode);
Value evaluateInputNode(CodeGenerator& generator, const InputNode* inNode);