#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <memory>
#include "AST.h"
#include "Parameter.h"

// Represents a function definition
class Function {
public:
    Function(const std::string& name, const std::string& returnType, const std::vector<Parameter>& parameters, std::unique_ptr<BlockNode> body)
        : name(name), returnType(returnType), parameters(parameters), body(std::move(body)) {}

    const std::string& getName() const { return name; }
    const std::string& getReturnType() const { return returnType; }
    const std::vector<Parameter>& getParameters() const { return parameters; }
    const std::unique_ptr<BlockNode>& getBody() const { return body; }

private:
    std::string name;
    std::string returnType;
    std::vector<Parameter> parameters;
    std::unique_ptr<BlockNode> body;
};


#endif // FUNCTION_H