#pragma once
#include <string>
#include <stdexcept>

/**
 * @struct EvaluatorHelper
 * @brief A utility struct for helping with evaluation tasks.
 *
 * This struct provides static utility functions to assist in the evaluation
 * of expressions and types within the code generator.
 */
struct EvaluatorHelper {
    /**
     * @brief Extracts the list type from a given type string.
     *
     * This function parses the provided type string to determine if it
     * represents a list type and, if so, returns the appropriate C++ vector
     * type. It handles basic types such as int, double, bool, and string.
     *
     * @param typeStr The type string to parse.
     * @return A string representing the extracted list type.
     * @throws std::runtime_error if the type string is invalid or incorrectly formatted.
     */
    static std::string extractListType(const std::string& typeStr) {
        std::string listType;
        if (typeStr.find(":") != std::string::npos) {
            std::string type = typeStr.substr(0, typeStr.find(":"));
            listType = typeStr.substr(typeStr.find(":") + 1);

            if (type != "list" && listType != "int" && listType != "double" && listType != "bool" && listType != "string") {
                throw std::runtime_error("Runtime Error: Invalid parameter type " + type);
            }
            else if (type != "list") {
                return typeStr;
            }

            if (listType != "int" && listType != "double" && listType != "bool" && listType != "string") {
                throw std::runtime_error("Runtime Error: Invalid list type " + listType);
            }

            if (listType == "string") listType = "std::string";

            listType = "std::vector<" + listType + ">";
        }
        else if (typeStr == "list") {
            throw std::runtime_error("Runtime Error: Invalid format, missing ':' in " + typeStr);
        }

        return listType;
    }
};
