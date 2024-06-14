#pragma once
#include "ValueHelper.h"
#include "CodeGenerator.h"

Value evaluatePrintNode(CodeGenerator& generator, const PrintNode* prNode);
Value evaluateInputNode(CodeGenerator& generator, const InputNode* inNode);