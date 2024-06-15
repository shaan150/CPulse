#include "ListNodeEvaluator.h"
#include "Function/Function.h"
#include "CodeGenerator/Evaluator/Handler/FunctionHandler.h"
#include <stdexcept>

Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode) {
    std::string type = listNode->getElementType();
    std::string name = listNode->getName();
    std::string line = std::to_string(listNode->getToken().line);
    if (type != "int" && type != "double" && type != "bool" && type != "string") {
        throw std::runtime_error("List Init Error: Invalid list type " + type + " at line " + line);
    }
    // check if the list already exists in the function context

    if (!generator.functionHandler->currentFunctionContext.empty()) {
        auto& context = generator.functionHandler->currentFunctionContext.top().variables;
        auto it = context.find(name);
        if (it != context.end()) {
            throw std::runtime_error("List Init Error: List " + name + " already exists at line " + line);
        }

        context.insert({ name, std::make_shared<TypedVector>(type) });
        return std::monostate();
    }

    std::shared_ptr<TypedVector> list = std::make_shared<TypedVector>(type);
    if (generator.variables.find(listNode->getName()) != generator.variables.end()) {
        throw std::runtime_error("List Init Error: List " + name + " already exists at line " + line);
    }
    generator.variables.insert({ listNode->getName(), list });
    return std::monostate();
}

Value evaluateListAppendNode(CodeGenerator& generator, const ListAppendNode* listAppendNode) {
    std::string line = std::to_string(listAppendNode->getToken().line);
    std::string name = listAppendNode->getListName();
    Value value = evaluate(listAppendNode->getValue().get(), generator);

    const Value& list = getListValue(generator, name, listAppendNode->getToken());

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (vec->getElementType() != ValueHelper::type(value)) {
            throw std::runtime_error("List Append Error: Type mismatch in list " + name + " at line " + line);
        }
        vec->push_back(value);
    }
    else {
        throw std::runtime_error("List Append Error: Variable " + name + " is not a list at line " + line);
    }

    return std::monostate();
}

Value evaluateListPopNode(CodeGenerator& generator, const ListPopNode* listPopNode) {
    std::string line = std::to_string(listPopNode->getToken().line);
    std::string name = listPopNode->getListName();
    int index = ValueHelper::asInt(evaluate(listPopNode->getIndex().get(), generator));

    const Value& list = getListValue(generator, name, listPopNode->getToken());
    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("List Pop Error: Index out of bounds for list " + name + " at line " + line);
        }
        Value value = vec->getValues()[index];
        vec->pop(index);
        return value;
    }
    else {
        throw std::runtime_error("List Pop Error: Variable " + name + " is not a list at line " + line);
    }
}

Value evaluateListLengthNode(CodeGenerator& generator, const ListLengthNode* listLengthNode) {
    std::string line = std::to_string(listLengthNode->getToken().line);
    std::string name = listLengthNode->getListName();
    int length = 0;

    const Value& list = getListValue(generator, name, listLengthNode->getToken());

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        length = vec->getValues().size();
    }
    else {
        throw std::runtime_error("List Length Error: Variable " + name + " is not a list at line " + line);
    }

    return length;
}

Value evaluateListIndexNode(CodeGenerator& generator, const ListIndexNode* listIndexNode) {
    std::string line = std::to_string(listIndexNode->getToken().line);
    std::string name = listIndexNode->getListName();
    int index = ValueHelper::asInt(evaluate(listIndexNode->getIndex().get(), generator));

    const Value& list = getListValue(generator, name, listIndexNode->getToken());

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("List Index Error: Index out of bounds for list " + name + " at line " + line);
        }
        return vec->getValues()[index];
    }
    else {
        throw std::runtime_error("List Index Error: Variable " + name + " is not a list at line " + line);
    }
}

Value evaluateListReplaceNode(CodeGenerator& generator, const ListReplaceNode* listReplaceNode) {
    const std::string& line = std::to_string(listReplaceNode->getToken().line);
    const std::string& name = listReplaceNode->getListName();
    const Value& value = evaluate(listReplaceNode->getValue().get(), generator);
    int index = ValueHelper::asInt(evaluate(listReplaceNode->getIndex().get(), generator));

    const Value& list = getListValue(generator, name, listReplaceNode->getToken());

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("List Replace Error: Index out of bounds for list " + name + " at line " + line);
        }
        if (vec->getElementType() != ValueHelper::type(value)) {
            throw std::runtime_error("List Replace Error: Type mismatch in list " + name + " at line " + line);
        }
        vec->replace(index, value);
    }
    else {
        throw std::runtime_error("List Replace Error: Variable " + name + " is not a list at line " + line);
    }

    return std::monostate();
}


// get the value of the list from the generator
Value getListValue(CodeGenerator& generator, const std::string& name, const Token& token) {
	auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
		throw std::runtime_error("List Error: Undefined list " + name + " at line " + std::to_string(token.line));
	}
	return it->second;
}