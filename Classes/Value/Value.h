#ifndef VALUE_H
#define VALUE_H

#include <variant>
#include <vector>
#include <string>
#include <memory>

class TypedVector; // Forward declaration

/**
 * @typedef Value
 * @brief A type alias for a std::variant that can hold various types of values.
 *
 * Value can hold the following types:
 * - double: Represents a floating-point number.
 * - int: Represents an integer.
 * - bool: Represents a boolean value.
 * - std::string: Represents a string.
 * - std::monostate: Represents a "none" or "null" type.
 * - std::shared_ptr<TypedVector>: Represents a pointer to a TypedVector object.
 */
using Value = std::variant<double, int, bool, std::string, std::monostate, std::shared_ptr<TypedVector>>;

#endif // VALUE_H
