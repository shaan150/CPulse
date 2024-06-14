#include "PrimitiveNodeEvaluator.h"

Value evaluateStringNode(const StringNode* strNode) {
    return strNode->getValue();
}

Value evaluateDoubleNode(const DoubleNode* doubleNode) {
    return doubleNode->getValue();
}

Value evaluateBooleanNode(const BooleanNode* boolNode) {
    return boolNode->getValue();
}

Value evaluateIntegerNode(const IntegerNode* intNode) {
    return intNode->getValue();
}