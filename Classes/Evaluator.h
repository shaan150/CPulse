#pragma once
#include "CodeGenerator.h"
#include "Evaluators/Primitive/PrimitiveNodeEvaluator.h"


Value evaluate(const ExprNode* node, CodeGenerator& generator);