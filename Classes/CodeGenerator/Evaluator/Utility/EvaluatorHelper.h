#pragma once
#include <string>
#include <stdexcept>

struct EvaluatorHelper {
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
