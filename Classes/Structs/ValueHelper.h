#pragma once
#include <variant>
#include <stdexcept>
#include <string>
#include <vector>
#include "TypedVector.h"

struct ValueHelper {
    static bool isInt(const Value& value) {
        return std::holds_alternative<int>(value);
    }

    static bool isDouble(const Value& value) {
        return std::holds_alternative<double>(value);
    }

    static bool isString(const Value& value) {
        return std::holds_alternative<std::string>(value);
    }

    static bool isBool(const Value& value) {
        return std::holds_alternative<bool>(value);
    }

    static bool isVector(const Value& value) {
        return std::holds_alternative<std::shared_ptr<TypedVector>>(value);
    }

    static int asInt(const Value& value) {
        if (!isInt(value)) {
            // check if the value is a double and try to convert it to an int
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

    static double asDouble(const Value& value) {
        if (!isDouble(value)) throw std::runtime_error("Value is not a double");
        return std::get<double>(value);
    }

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

    static bool asBool(const Value& value) {
        if (!isBool(value)) throw std::runtime_error("Value is not a bool");
        return std::get<bool>(value);
    }

    static std::shared_ptr<TypedVector>& asVector(Value& value) {
        if (!isVector(value)) {
            throw std::runtime_error("Value is not a vector");
        }
        return std::get<std::shared_ptr<TypedVector>>(value);
    }

    static const std::shared_ptr<TypedVector>& asVector(const Value& value) {
        if (!isVector(value)) {
            throw std::runtime_error("Value is not a vector");
        }
        return std::get<std::shared_ptr<TypedVector>>(value);
    }

    // get type of value
    static std::string type(const Value& value) {
		if (isInt(value)) return "int";
		if (isDouble(value)) return "double";
		if (isString(value)) return "string";
		if (isBool(value)) return "bool";
        if (isVector(value)) return "vector";
		return "null";
	}
};
