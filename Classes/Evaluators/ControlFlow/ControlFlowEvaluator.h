#pragma once
#include "ValueHelper.h"
#include "CodeGenerator.h"

Value evaluateIfNode(CodeGenerator& generator, const IfNode* ifNode);
Value evaluateWhileNode(CodeGenerator& generator, const WhileNode* whileNode);
Value evaluateBlockNode(CodeGenerator& generator, const BlockNode* blockNode);