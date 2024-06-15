#ifndef VARIABLENODEEVALUATOR_H
#define VARIABLENODEEVALUATOR_H

#include "Value/Value.h"
#include "AST/AST.h"

class CodeGenerator;
class VariableNode;

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);

#endif // VARIABLENODEEVALUATOR_H