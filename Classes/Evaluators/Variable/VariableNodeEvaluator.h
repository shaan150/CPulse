#ifndef VARIABLENODEEVALUATOR_H
#define VARIABLENODEEVALUATOR_H

#include "Value.h"
#include "AST.h"

class CodeGenerator;
class VariableNode;

Value evaluateVariableNode(CodeGenerator& generator, const VariableNode* varNode);
Value evaluateAssignNode(CodeGenerator& generator, const AssignNode* assignNode);

#endif // VARIABLENODEEVALUATOR_H