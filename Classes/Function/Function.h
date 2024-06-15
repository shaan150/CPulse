#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <memory>
#include <Function/Parameter.h>

/**
 * @class Function
 * @brief Represents a function definition, including its name, return type, parameters, and body.
 */
class Function {
public:
    /**
     * @brief Constructs a Function object.
     * @param name The name of the function.
     * @param returnType The return type of the function.
     * @param parameters The parameters of the function.
     * @param body The body of the function, represented as a BlockNode.
     */
    Function(const std::string& name, const std::string& returnType, const std::vector<Parameter>& parameters, std::unique_ptr<BlockNode> body)
        : name(name), returnType(returnType), parameters(parameters), body(std::move(body)) {}

    /**
     * @brief Gets the name of the function.
     * @return A constant reference to the name of the function.
     */
    const std::string& getName() const { return name; }

    /**
     * @brief Gets the return type of the function.
     * @return A constant reference to the return type of the function.
     */
    const std::string& getReturnType() const { return returnType; }

    /**
     * @brief Gets the parameters of the function.
     * @return A constant reference to the vector of parameters of the function.
     */
    const std::vector<Parameter>& getParameters() const { return parameters; }

    /**
     * @brief Gets the body of the function.
     * @return A constant reference to the unique pointer of the BlockNode representing the body of the function.
     */
    const std::unique_ptr<BlockNode>& getBody() const { return body; }

private:
    std::string name; ///< The name of the function.
    std::string returnType; ///< The return type of the function.
    std::vector<Parameter> parameters; ///< The parameters of the function.
    std::unique_ptr<BlockNode> body; ///< The body of the function, represented as a BlockNode.
};

#endif // FUNCTION_H
