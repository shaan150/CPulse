#ifndef VALUE_H
#define VALUE_H

#include <variant>
#include <vector>
#include <string>
#include <memory>

class TypedVector; // Forward declaration

using Value = std::variant<double, int, bool, std::string, std::monostate, std::shared_ptr<TypedVector>>;

#endif // VALUE_H