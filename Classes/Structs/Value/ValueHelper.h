#pragma once
#include <variant>
#include <stdexcept>
#include <string>
#include <vector>
#include "TypedVector/TypedVector.h"

/**
 * @struct ValueHelper
 * @brief Provides utility functions to work with values of different types stored in a std::variant.
 */
struct ValueHelper {
    /**
     * @brief Checks if the value is an integer.
     * @param value The value to check.
     * @return True if the value is an integer, false otherwise.
     */
    static bool isInt(const Value& value) {
        return std::holds_alternative<int>(value);
    }

    /**
     * @brief Checks if the value is a double.
     * @param value The value to check.
     * @return True if the value is a double, false otherwise.
     */
    static bool isDouble(const Value& value) {
        return std::holds_alternative<double>(value);
    }

    /**
     * @brief Checks if the value is a string.
     * @param value The value to check.
     * @return True if the value is a string, false otherwise.
     */
    static bool isString(const Value& value) {
        return std::holds_alternative<std::string>(value);
    }

    /**
     * @brief Checks if the value is a boolean.
     * @param value The value to check.
     * @return True if the value is a boolean, false otherwise.
     */
    static bool isBool(const Value& value) {
        return std::holds_alternative<bool>(value);
    }

    /**
     * @brief Checks if the value is a vector.
     * @param value The value to check.
     * @return True if the value is a vector, false otherwise.
     */
    static bool isVector(const Value& value) {
        return std::holds_alternative<std::shared_ptr<TypedVector>>(value);
    }

    /**
     * @brief Converts the value to an integer.
     * @param value The value to convert.
     * @return The integer value.
     * @throws std::runtime_error if the value is not an integer or cannot be converted to an integer.
     */
    static int asInt(const Value& value) {
        if (!isInt(value)) {
            // Check if the value is a double and try to convert it to an int
            try {
                if (isDouble(value)) {
                    return static_cast<int>(std::get<double>(value));
                }
            }
            catch (const std::bad_variant_access&) {
                // Handle bad_variant_access exceptions by throwing a runtime_error
                throw std::runtime_error("Value is not an integer");
            }
            throw std::runtime_error("Value is not an integer");
        }
        return std::get<int>(value);
    }

    /**
     * @brief Converts the value to a double.
     * @param value The value to convert.
     * @return The double value.
     * @throws std::runtime_error if the value is not a double.
     */
    static double asDouble(const Value& value) {
        if (!isDouble(value)) throw std::runtime_error("Value is not a double");
        return std::get<double>(value);
    }

    /**
     * @brief Converts the value to a string.
     * @param value The value to convert.
     * @return The string representation of the value.
     */
    static std::string asString(const Value& value) {
        // Static empty string to return in case of errors or empty values
        static const std::string emptyString = "";

        try {
            // Check if the value is already a string
            if (std::holds_alternative<std::string>(value)) {
                return std::get<std::string>(value);
            }

            // Convert int or double to string
            if (std::holds_alternative<int>(value)) {
                return std::to_string(asInt(value));
            }
            else if (std::holds_alternative<double>(value)) {
                return std::to_string(asDouble(value));
            }
            else if (std::holds_alternative<bool>(value)) {
                return std::get<bool>(value) ? "true" : "false";
            }
        }
        catch (const std::bad_variant_access&) {
            // Handle bad_variant_access exceptions by returning an empty string
        }
        catch (const std::length_error&) {
            // Handle length_error exceptions by returning an empty string
        }

        // Return empty string if value is neither int, double, nor string, or if an exception occurs
        return emptyString;
    }

    /**
     * @brief Converts the value to a boolean.
     * @param value The value to convert.
     * @return The boolean value.
     * @throws std::runtime_error if the value is not a boolean.
     */
    static bool asBool(const Value& value) {
        if (!isBool(value)) throw std::runtime_error("Value is not a bool");
        return std::get<bool>(value);
    }

    /**
     * @brief Converts the value to a vector (non-const version).
     * @param value The value to convert.
     * @return A reference to the vector.
     * @throws std::runtime_error if the value is not a vector.
     */
    static std::shared_ptr<TypedVector>& asVector(Value& value) {
        if (!isVector(value)) {
            throw std::runtime_error("Value is not a vector");
        }
        return std::get<std::shared_ptr<TypedVector>>(value);
    }

    /**
     * @brief Converts the value to a vector (const version).
     * @param value The value to convert.
     * @return A const reference to the vector.
     * @throws std::runtime_error if the value is not a vector.
     */
    static const std::shared_ptr<TypedVector>& asVector(const Value& value) {
        if (!isVector(value)) {
            throw std::runtime_error("Value is not a vector");
        }
        return std::get<std::shared_ptr<TypedVector>>(value);
    }

    /**
     * @brief Gets the type of the value as a string.
     * @param value The value whose type is to be determined.
     * @return The type of the value as a string.
     */
    static std::string type(const Value& value) {
        if (isInt(value)) return "int";
        if (isDouble(value)) return "double";
        if (isString(value)) return "string";
        if (isBool(value)) return "bool";
        if (isVector(value)) return "vector";
        return "null";
    }
};
