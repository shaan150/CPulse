#pragma once
#include <variant>
#include <stdexcept>
#include <string>
#include <vector>
#include "TypedVector/TypedVector.h"
#include <cmath> 

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
                if (isString(value) || isDouble(value)) {
                    double doubleValue;
                    if (isString(value)) {
                        // Try to convert the string to an double
                        doubleValue = asDouble(value);
                    }
                    else {
						doubleValue = asDouble(value);
					}

                    if (doubleValue != std::floor(doubleValue)) { // Check if double has a fractional part
                        throw std::runtime_error("Value is a double with a fractional part");
                    }
                    return static_cast<int>(doubleValue);
                }
                else if (isBool(value)) {
                    return std::get<bool>(value) ? 1 : 0;
                }
            }
            catch (const std::runtime_error& e) {
				// Handle runtime_error exceptions by rethrowing them
				throw;
			}
            catch (const std::bad_variant_access&) {
                // Handle bad_variant_access exceptions by throwing a runtime_error
                throw std::runtime_error("Value is not an integer");
            }
            catch (const std::exception& e) {
				// Handle other standard exceptions
				throw std::runtime_error(std::string("An error occurred: ") + e.what());
			}
            throw std::runtime_error("Value is not an integer");
        }
        else {
            // If it's already an integer, return it as is
            return std::get<int>(value);
        }
    }

    /**
     * @brief Converts the value to a double.
     * @param value The value to convert.
     * @return The double value.
     * @throws std::runtime_error if the value is not a double.
     */
    static double asDouble(const Value& value) {
        try {
            // Check if the value is an integer and try to convert it to a double
            if (!isDouble(value)) {
                // check if it's a string and try to convert it to a double
                if (isString(value)) {
					return std::stod(std::get<std::string>(value));
                }
                else if (isInt(value)) {
					return static_cast<double>(std::get<int>(value));
				}
                else if (isBool(value)) {
					return std::get<bool>(value) ? 1.0 : 0.0;
				}
            }
            else {
                // If it's already a double, return it as is
                return std::get<double>(value);
            }
        }
        catch (const std::bad_variant_access&) {
            // Handle bad_variant_access exceptions by throwing a runtime_error
            throw std::runtime_error("Value is not a double or integer");
        }
        catch (const std::exception& e) {
            // Handle other standard exceptions
            throw std::runtime_error(std::string("An error occurred: ") + e.what());
        }
        
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
