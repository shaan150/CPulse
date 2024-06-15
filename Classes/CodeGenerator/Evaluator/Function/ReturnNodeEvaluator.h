#ifndef RETURNNODEEVALUATOR_H
#define RETURNNODEEVALUATOR_H

#include "CodeGenerator/Evaluator/Evaluator.h"
#include "AST/AST.h"
#include "Value/Value.h"

Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);

#endif // RETURNNODEEVALUATOR_H