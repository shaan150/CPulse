#ifndef RETURNNODEEVALUATOR_H
#define RETURNNODEEVALUATOR_H

#include "Evaluator.h"
#include "AST.h"
#include "Value.h"

Value evaluateReturnNode(CodeGenerator& generator, const ReturnNode* returnNode);

#endif // RETURNNODEEVALUATOR_H