// Purpose: Holds the name and type of a parameter.
#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

struct Parameter {
    std::string name;
    std::string type;

    Parameter(const std::string& name, const std::string& type) : name(name), type(type) {}
};

#endif // PARAMETER_H