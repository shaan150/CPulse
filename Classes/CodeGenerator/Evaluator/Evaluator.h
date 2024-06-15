#pragma once
#include "CodeGenerator/CodeGenerator.h"
#include "CodeGenerator/Evaluator/Primitive/PrimitiveNodeEvaluator.h"


Value evaluate(const ExprNode* node, CodeGenerator& generator);