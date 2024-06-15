#ifndef EXPRESSIONPARSER_H
#include "AST/AST.h"

#include "Parser/Parser.h"  // Include the full definition of the Parser class

class ExpressionParser {
public:
    static std::unique_ptr<ExprNode> parse_expression(Parser& parser);
    static std::unique_ptr<ExprNode> parse_term(Parser& parser);
    static std::unique_ptr<ExprNode> parse_factor(Parser& parser);
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