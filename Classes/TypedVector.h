#ifndef TYPEDVECTOR_H
#define TYPEDVECTOR_H

#pragma once
#include <vector>
#include <string>
#include "Value.h"

class TypedVector {
public:
    TypedVector(const std::string& type) : elementType(type) {}

    void push_back(const Value& value);

    void pop(int index);

    Value& at(int index);

    void replace(int index, const Value& value);

    const std::vector<Value>& getValues() const {
        return values;
    }

    std::string getElementType() const {
        return elementType;
    }

private:
    std::string elementType;
    std::vector<Value> values;
};

#endif // TYPEDVECTOR_H