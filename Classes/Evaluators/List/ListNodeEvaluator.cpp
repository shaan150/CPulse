#include "ListNodeEvaluator.h"

Value evaluateListInitNode(CodeGenerator& generator, const ListInitNode* listNode) {
    std::string type = listNode->getElementType();
    if (type != "int" && type != "double" && type != "bool" && type != "string") {
        throw std::runtime_error("Syntax Error: Unsupported type for list at line " + std::to_string(listNode->getToken().line));
    }

    std::shared_ptr<TypedVector> list = std::make_shared<TypedVector>(type);
    if (generator.variables.find(listNode->getName()) != generator.variables.end()) {
        throw std::runtime_error("Syntax Error: List " + listNode->getName() + " already exists at line " + std::to_string(listNode->getToken().line));
    }
    generator.variables.insert({ listNode->getName(), list });
    return std::monostate();
}

Value evaluateListAppendNode(CodeGenerator& generator, const ListAppendNode* listAppendNode) {
    std::string line = std::to_string(listAppendNode->getToken().line);
    std::string name = listAppendNode->getListName();
    auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
        throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
    }

    Value& list = it->second;
    Value value = evaluate(listAppendNode->getValue().get(), generator);

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (vec->getElementType() != ValueHelper::type(value)) {
            throw std::runtime_error("Syntax Error: Type mismatch in list " + name + " at line " + line);
        }
        vec->push_back(value);
    }
    else {
        throw std::runtime_error("Syntax Error: " + name + " is not a list at line " + line);
    }

    return std::monostate();
}

Value evaluateListPopNode(CodeGenerator& generator, const ListPopNode* listPopNode) {
    std::string line = std::to_string(listPopNode->getToken().line);
    std::string name = listPopNode->getListName();
    int index = ValueHelper::asInt(evaluate(listPopNode->getIndex().get(), generator));
    auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
        throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
    }

    Value& list = it->second;
    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
        }
        Value value = vec->getValues()[index];
        vec->pop(index);
        return value;
    }
    else {
        throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
    }
}

Value evaluateListLengthNode(CodeGenerator& generator, const ListLengthNode* listLengthNode) {
    std::string line = std::to_string(listLengthNode->getToken().line);
    std::string name = listLengthNode->getListName();
    auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
        throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
    }
    int length = 0;

    Value& list = it->second;

    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        length = vec->getValues().size();
    }
    else {
        throw std::runtime_error("Syntax Error: " + name + " is not a list at line " + line);
    }

    return length;
}

Value evaluateListIndexNode(CodeGenerator& generator, const ListIndexNode* listIndexNode) {
    std::string line = std::to_string(listIndexNode->getToken().line);
    std::string name = listIndexNode->getListName();
    int index = ValueHelper::asInt(evaluate(listIndexNode->getIndex().get(), generator));
    auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
        throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
    }

    Value& list = it->second;
    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
        }
        return vec->getValues()[index];
    }
    else {
        throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
    }
}

Value evaluateListReplaceNode(CodeGenerator& generator, const ListReplaceNode* listReplaceNode) {
    std::string line = std::to_string(listReplaceNode->getToken().line);
    std::string name = listReplaceNode->getListName();
    int index = ValueHelper::asInt(evaluate(listReplaceNode->getIndex().get(), generator));
    Value value = evaluate(listReplaceNode->getValue().get(), generator);
    auto it = generator.variables.find(name);
    if (it == generator.variables.end()) {
        throw std::runtime_error("Syntax Error: Undefined list " + name + " at line " + line);
    }

    Value& list = it->second;
    if (ValueHelper::isVector(list)) {
        std::shared_ptr<TypedVector> vec = ValueHelper::asVector(list);
        if (index < 0 || index >= vec->getValues().size()) {
            throw std::runtime_error("Syntax Error: Index out of bounds for list " + name + " at line " + line);
        }
        if (vec->getElementType() != ValueHelper::type(value)) {
            throw std::runtime_error("Syntax Error: Type mismatch in list " + name + " at line " + line);
        }
        vec->replace(index, value);
    }
    else {
        throw std::runtime_error("Syntax Error: Variable " + name + " is not a list at line " + line);
    }

    return std::monostate();
}