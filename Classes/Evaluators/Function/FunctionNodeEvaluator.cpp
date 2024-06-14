#include "FunctionNodeEvaluator.h"
#include "CodeGenerator.h"
#include "Structs/Functions/Function.h"
#include "Evaluators/Handler/FunctionHandler.h"

Value FunctionNodeEvaluator::evaluateFunctionDefNode(CodeGenerator* generator, const FunctionDefNode* functionDefNode) {
    std::vector<Parameter> params;
    for (const auto& param : functionDefNode->getParameters()) {
        params.emplace_back(param.first, param.second);
    }

    auto function = std::make_unique<Function>(
        functionDefNode->getName(),
        functionDefNode->getReturnType(),
        params,
        std::make_unique<BlockNode>(std::move(*functionDefNode->getBody())) // Move BlockNode
    );

    generator->functionHandler->addFunction(functionDefNode->getName(), std::move(function));
    return std::monostate();
}

Value FunctionNodeEvaluator::evaluateFunctionCallNode(CodeGenerator* generator, const FunctionCallNode* functionCallNode) {
    return generator->functionHandler->callFunction(functionCallNode, *generator);
}
