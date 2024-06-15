#include "CodeGenerator/Evaluator/Evaluator.h"
#include <stdexcept>
#include "CodeGenerator/Evaluator/Function/FunctionNodeEvaluator.h"
#include "CodeGenerator/Evaluator/Function/ReturnNodeEvaluator.h"

Value evaluate(const ExprNode* node, CodeGenerator& generator) {
    if (!node) {
        return std::monostate();
    }

    if (auto strNode = dynamic_cast<const StringNode*>(node)) {
        return evaluateStringNode(strNode);
    }
    else if (auto doubleNode = dynamic_cast<const DoubleNode*>(node)) {
        return evaluateDoubleNode(doubleNode);
    }
    else if (auto boolNode = dynamic_cast<const BooleanNode*>(node)) {
        return evaluateBooleanNode(boolNode);
    }
    else if (auto intNode = dynamic_cast<const IntegerNode*>(node)) {
        return evaluateIntegerNode(intNode);
    }
    else if (auto varNode = dynamic_cast<const VariableNode*>(node)) {
        return evaluateVariableNode(generator, varNode);
    }
    else if (auto listNode = dynamic_cast<const ListInitNode*>(node)) {
        return evaluateListInitNode(generator, listNode);
    }
    else if (auto listAppendNode = dynamic_cast<const ListAppendNode*>(node)) {
        return evaluateListAppendNode(generator, listAppendNode);
    }
    else if (auto listPopNode = dynamic_cast<const ListPopNode*>(node)) {
        return evaluateListPopNode(generator, listPopNode);
    }
    else if (auto listLengthNode = dynamic_cast<const ListLengthNode*>(node)) {
        return evaluateListLengthNode(generator, listLengthNode);
    }
    else if (auto listIndexNode = dynamic_cast<const ListIndexNode*>(node)) {
        return evaluateListIndexNode(generator, listIndexNode);
    }
    else if (auto listReplaceNode = dynamic_cast<const ListReplaceNode*>(node)) {
        return evaluateListReplaceNode(generator, listReplaceNode);
    }
    else if (auto assignNode = dynamic_cast<const AssignNode*>(node)) {
        return evaluateAssignNode(generator, assignNode);
    }
    else if (auto binNode = dynamic_cast<const BinaryExprNode*>(node)) {
        return evaluateBinaryExprNode(generator, binNode);
    }
    else if (auto unNode = dynamic_cast<const UnaryExprNode*>(node)) {
        return evaluateUnaryExprNode(generator, unNode);
    }
    else if (auto prNode = dynamic_cast<const PrintNode*>(node)) {
        return evaluatePrintNode(generator, prNode);
    }
    else if (auto inNode = dynamic_cast<const InputNode*>(node)) {
        return evaluateInputNode(generator, inNode);
    }
    else if (auto ifNode = dynamic_cast<const IfNode*>(node)) {
        return evaluateIfNode(generator, ifNode);
    }
    else if (auto whileNode = dynamic_cast<const WhileNode*>(node)) {
        return evaluateWhileNode(generator, whileNode);
    }
    else if (auto blockNode = dynamic_cast<const BlockNode*>(node)) {
        return evaluateBlockNode(generator, blockNode);
    }
    else if (auto typeCastNode = dynamic_cast<const TypeCastNode*>(node)) {
        return evaluateTypeCastNode(generator, typeCastNode);
    }
    else if (auto functionDefNode = dynamic_cast<const FunctionDefNode*>(node)) {
         FunctionNodeEvaluator evaluator;
         return evaluator.evaluateFunctionDefNode(&generator, functionDefNode);
        }
    else if (auto functionCallNode = dynamic_cast<const FunctionCallNode*>(node)) {
         FunctionNodeEvaluator evaluator;
         return evaluator.evaluateFunctionCallNode(&generator, functionCallNode);
    }
    else if (auto returnNode = dynamic_cast<const ReturnNode*>(node)) {
		return evaluateReturnNode(generator, returnNode);
	}

    throw std::runtime_error("Syntax Error: Unsupported node type at line " + std::to_string(node->getToken().line));
}