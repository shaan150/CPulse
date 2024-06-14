#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include "CodeGenerator.h"
#include "Value.h"
#include <Evaluators/Function/FunctionNodeEvaluator.h>

Value evaluateFunctionCallNode(CodeGenerator& generator, const FunctionCallNode* functionCallNode);


#endif // FUNCTION_HANDLER_H
