#ifndef TYPEDVECTOR_H
#define TYPEDVECTOR_H

#pragma once
#include <vector>
#include <string>
#include "Value/Value.h"

/**
 * @class TypedVector
 * @brief A class that represents a typed vector, ensuring all elements are of the specified type.
 */
class TypedVector {
public:
    /**
     * @brief Constructor that initializes the TypedVector with a specific element type.
     * @param type The type of elements that this vector will hold.
     */
    TypedVector(const std::string& type) : elementType(type) {}

    /**
     * @brief Adds a value to the end of the vector.
     * @param value The value to add.
     * @throws std::runtime_error if the value type does not match the element type of the vector.
     */
    void push_back(const Value& value);

    /**
     * @brief Removes the element at the specified index.
     * @param index The index of the element to remove.
     * @throws std::runtime_error if the index is out of bounds.
     */
    void pop(int index);

    /**
     * @brief Returns a reference to the element at the specified index.
     * @param index The index of the element to access.
     * @return A reference to the value at the specified index.
     * @throws std::runtime_error if the index is out of bounds.
     */
    Value& at(int index);

    /**
     * @brief Replaces the element at the specified index with a new value.
     * @param index The index of the element to replace.
     * @param value The new value to set at the specified index.
     * @throws std::runtime_error if the index is out of bounds or the value type does not match the element type of the vector.
     */
    void replace(int index, const Value& value);

    /**
     * @brief Gets a constant reference to the underlying values vector.
     * @return A constant reference to the vector of values.
     */
    const std::vector<Value>& getValues() const {
        return values;
    }

    /**
     * @brief Gets the element type of the vector.
     * @return A string representing the element type.
     */
    std::string getElementType() const {
        return elementType;
    }

private:
    std::string elementType; ///< The type of elements that this vector holds.
    std::vector<Value> values; ///< The underlying vector of values.
};

#endif // TYPEDVECTOR_H
