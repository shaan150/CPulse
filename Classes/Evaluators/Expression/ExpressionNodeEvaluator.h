#pragma 
#include "CodeGenerator.h"
#include "ValueHelper.h"

Value evaluateBinaryExprNode(CodeGenerator& generator, const BinaryExprNode* binNode);
Value evaluateUnaryExprNode(CodeGenerator& generator, const UnaryExprNode* unNode);
Value evaluateTypeCastNode(CodeGenerator& generator, const TypeCastNode* typeCastNode);
Value evaluateFunctionCallNode(CodeGenerator* generator, const FunctionCallNode* functionCallNode);
Value evaluateFunctionDefNode(CodeGenerator* generator, const FunctionDefNode* functionNode);
