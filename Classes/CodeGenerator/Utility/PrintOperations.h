#ifndef PRINTOPERATIONS_H
#define PRINTOPERATIONS_H

#include "Value/ValueHelper.h"
#include <iostream>

/**
 * @class PrintOperations
 * @brief Provides functionality to print different types of values to the standard output.
 */
class PrintOperations {
public:
    /**
     * @brief Prints the given value to the standard output.
     * @param value The value to be printed. The value can be of type int, double, bool, string, None (monostate), or a shared_ptr to a TypedVector.
     * @throws std::runtime_error if the value type is unsupported.
     */
    static void printValue(const Value& value);
};

#endif // PRINTOPERATIONS_H
