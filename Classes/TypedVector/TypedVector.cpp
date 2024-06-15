#include "TypedVector/TypedVector.h"
#include "Value/Value.h"
#include <stdexcept>

void TypedVector::push_back(const Value& value) {
    std::string valueType = value.index() == 0 ? "double" :
        value.index() == 1 ? "int" :
        value.index() == 2 ? "bool" :
        value.index() == 3 ? "string" :
        "unknown";

    if (valueType != elementType) {
        throw std::runtime_error("Type Error: Attempt to add wrong type to the list.");
    }
    values.push_back(value);
}

void TypedVector::pop(int index) {
    if (index < 0 || index >= values.size()) {
        throw std::runtime_error("Index Error: Index out of bounds.");
    }
    values.erase(values.begin() + index);
}

Value& TypedVector::at(int index) {
    if (index < 0 || index >= values.size()) {
        throw std::runtime_error("Index Error: Index out of bounds.");
    }
    return values.at(index);
}

void TypedVector::replace(int index, const Value& value) {
    if (index < 0 || index >= values.size()) {
		throw std::runtime_error("Index Error: Index out of bounds.");
	}

	std::string valueType = value.index() == 0 ? "double" :
		value.index() == 1 ? "int" :
		value.index() == 2 ? "bool" :
		value.index() == 3 ? "string" :
		"unknown";

    if (valueType != elementType) {
		throw std::runtime_error("Type Error: Attempt to add wrong type to the list.");
	}

	values.at(index) = value;
}