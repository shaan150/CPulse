// Purpose: Holds the name and type of a parameter.
#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

/**
 * @struct Parameter
 * @brief Represents a parameter with a name and type.
 */
struct Parameter {
    std::string name; ///< The name of the parameter.
    std::string type; ///< The type of the parameter.

    /**
     * @brief Constructor to initialize a Parameter.
     * @param name The name of the parameter.
     * @param type The type of the parameter.
     */
    Parameter(const std::string& name, const std::string& type) : name(name), type(type) {}
};

#endif // PARAMETER_H
