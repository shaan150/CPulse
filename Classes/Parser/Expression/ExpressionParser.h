#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include "AST/AST.h"
#include "Parser/Parser.h"  // Include the full definition of the Parser class

/**
 * @class ExpressionParser
 * @brief Provides functionality to parse expressions, terms, and factors in the input code.
 */
class ExpressionParser {
public:
    /**
     * @brief Parses an expression from the input using the given parser.
     * @param parser The parser to use for parsing the expression.
     * @return A unique pointer to the parsed expression node.
     */
    static std::unique_ptr<ExprNode> parse_expression(Parser& parser);

    /**
     * @brief Parses a term from the input using the given parser.
     * @param parser The parser to use for parsing the term.
     * @return A unique pointer to the parsed term node.
     */
    static std::unique_ptr<ExprNode> parse_term(Parser& parser);

    /**
     * @brief Parses a factor from the input using the given parser.
     * @param parser The parser to use for parsing the factor.
     * @return A unique pointer to the parsed factor node.
     */
    static std::unique_ptr<ExprNode> parse_factor(Parser& parser);

    /**
     * @brief Parses a numeric node from the input using the given parser.
     * @tparam NodeType The type of node to create (e.g., IntegerNode, DoubleNode).
     * @tparam ValueType The type of value to parse (e.g., int, double).
     * @param parser The parser to use for parsing the numeric node.
     * @param token The token representing the numeric value.
     * @param value The numeric value to parse.
     * @return A unique pointer to the parsed numeric node.
     */
    template<typename NodeType, typename ValueType>
    static std::unique_ptr<ExprNode> parse_numeric_node(Parser& parser, const Token& token, ValueType value);
};

template<typename NodeType, typename ValueType>
std::unique_ptr<ExprNode> ExpressionParser::parse_numeric_node(Parser& parser, const Token& token, ValueType value) {
    parser.advance();

    // Handle consecutive `-` tokens
    std::unique_ptr<ExprNode> node = std::make_unique<NodeType>(token, value);

    while (parser.current_token().type == TokenType::ARITHMETIC && parser.current_token().value == "-") {
        Token op = parser.current_token();
        parser.advance();

        if (parser.current_token().type == TokenType::ARITHMETIC && parser.current_token().value == "-") {
            parser.advance();
            node = std::make_unique<BinaryExprNode>(op, std::move(node), "+", PrimaryParser::parse_primary(parser));
        }
        else {
            node = std::make_unique<BinaryExprNode>(op, std::move(node), "-", PrimaryParser::parse_primary(parser));
        }
    }

    return node;
}

#endif // EXPRESSIONPARSER_H
