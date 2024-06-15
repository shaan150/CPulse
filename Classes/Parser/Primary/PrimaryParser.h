#ifndef PRIMARYPARSER_H
#define PRIMARYPARSER_H

#include "AST/AST.h"

class Parser;

/**
 * @class PrimaryParser
 * @brief Provides functionality to parse primary expressions, identifiers, and functions in the input code.
 */
class PrimaryParser {
public:
    /**
     * @brief Parses a primary expression from the input using the given parser.
     * @param parser The parser to use for parsing the primary expression.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> parse_primary(Parser& parser);

    /**
     * @brief Handles the parsing of an identifier.
     * @param parser The parser to use for parsing the identifier.
     * @param token The token representing the identifier.
     * @param identifier The identifier string.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> identifier_handler(Parser& parser, Token& token, std::string& identifier);

    /**
     * @brief Handles the parsing of a function call or definition.
     * @param parser The parser to use for parsing the function.
     * @param identifier The identifier string representing the function name.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> handle_functions(Parser& parser, std::string& identifier);

    /**
     * @brief Parses a function definition from the input using the given parser.
     * @param parser The parser to use for parsing the function definition.
     * @return A unique pointer to the parsed function definition node.
     */
    static std::unique_ptr<ExprNode> parse_function_definition(Parser& parser);

private:
    /**
     * @brief Parses the return type of a function.
     * @param parser The parser to use for parsing the return type.
     * @return The return type as a string.
     */
    static std::string parse_return_type(Parser& parser);

    /**
     * @brief Parses the name of a function.
     * @param parser The parser to use for parsing the function name.
     * @return The function name as a string.
     */
    static std::string parse_function_name(Parser& parser);

    /**
     * @brief Parses the parameters of a function.
     * @param parser The parser to use for parsing the function parameters.
     * @return A vector of parameter name and type pairs.
     */
    static std::vector<std::pair<std::string, std::string>> parse_parameters(Parser& parser);

    /**
     * @brief Parses the body of a function.
     * @param parser The parser to use for parsing the function body.
     * @param hasReturnStatement A reference to a boolean flag indicating if the body contains a return statement.
     * @return A unique pointer to the parsed block node representing the function body.
     */
    static std::unique_ptr<BlockNode> parse_function_body(Parser& parser, bool& hasReturnStatement);

    /**
     * @brief Handles the parsing of an assignment operation.
     * @param parser The parser to use for parsing the assignment.
     * @param token The token representing the assignment.
     * @param identifier The identifier string representing the variable name.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> handle_assignment(Parser& parser, Token& token, std::string& identifier);

    /**
     * @brief Handles the parsing of a method access operation.
     * @param parser The parser to use for parsing the method access.
     * @param token The token representing the method access.
     * @param identifier The identifier string representing the object name.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> handle_method_access(Parser& parser, Token& token, std::string& identifier);

    /**
     * @brief Handles the parsing of a list index operation.
     * @param parser The parser to use for parsing the list index.
     * @param token The token representing the list index.
     * @param identifier The identifier string representing the list name.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> handle_list_index(Parser& parser, Token& token, std::string& identifier);
};

#endif // PRIMARYPARSER_H
