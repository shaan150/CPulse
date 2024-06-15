#include "PrintOperations.h"
#include <iostream>

void PrintOperations::printValue(const Value& value) {
    std::string output;
    // Convert value to string properly
    if (std::holds_alternative<int>(value)) {
        output = std::to_string(std::get<int>(value));
    }
    else if (std::holds_alternative<double>(value)) {
        output = std::to_string(std::get<double>(value));
    }
    else if (std::holds_alternative<bool>(value)) {
        output = std::get<bool>(value) ? "true" : "false";
    }
    else if (std::holds_alternative<std::string>(value)) {
        output = std::get<std::string>(value);
    }
    else if (std::holds_alternative<std::monostate>(value)) {
        output = "None";
    }
    else if (std::holds_alternative<std::shared_ptr<TypedVector>>(value)) {
        const auto& vec = std::get<std::shared_ptr<TypedVector>>(value);
        const auto& values = vec->getValues();
        // Create string representation of vector
        output = "[";
        for (size_t i = 0; i < values.size(); i++) {
            if (std::holds_alternative<int>(values[i])) {
                output += std::to_string(std::get<int>(values[i]));
            }
            else if (std::holds_alternative<double>(values[i])) {
                output += std::to_string(std::get<double>(values[i]));
            }
            else if (std::holds_alternative<bool>(values[i])) {
                output += std::to_string(std::get<bool>(values[i]));
            }
            else if (std::holds_alternative<std::string>(values[i])) {
                output += std::get<std::string>(values[i]);
            }
            if (i != values.size() - 1) {
                output += ", ";
            }
        }
        output += "]";
    }
    else {
        throw std::runtime_error("Print Error: Unsupported type " + ValueHelper::type(value));
    }

    std::cout << output << std::endl;
}
