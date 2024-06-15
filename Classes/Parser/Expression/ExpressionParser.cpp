#include "ExpressionParser.h"
#include <Parser/Primary/PrimaryParser.h>
#include <Parser/Parser.h>

std::unique_ptr<ExprNode> ExpressionParser::parse_expression(Parser& parser) {
    auto left = parse_term(parser);

    while (parser.current_token().type == TokenType::EQUAL || parser.current_token().type == TokenType::COMPARISON || parser.current_token().type == TokenType::LOGICAL) {
        Token op = parser.current_token();

        // Handle multi-character operators
        std::string opValue = op.value;
        parser.advance();

        // Check for operators like '!=' and '=='
        if ((opValue == "!" || opValue == "=" || opValue == "<" || opValue == ">") && parser.current_token().type == TokenType::EQUAL) {
            opValue += parser.current_token().value;
            parser.advance();
        }

        auto right = parse_term(parser);

        if (opValue == "==") {
            op.type = TokenType::COMPARISON;
            left = std::make_unique<BinaryExprNode>(op, std::move(left), "==", std::move(right));
        }
        else if (opValue == "!=") {
            op.type = TokenType::COMPARISON;
            left = std::make_unique<BinaryExprNode>(op, std::move(left), "!=", std::move(right));
        }
        else if (opValue == "=") {
            left = std::make_unique<BinaryExprNode>(op, std::move(left), "=", std::move(right));
        }
        else {
            left = std::make_unique<BinaryExprNode>(op, std::move(left), opValue, std::move(right));
        }
    }

    return left;
}

std::unique_ptr<ExprNode> ExpressionParser::parse_term(Parser& parser) {
    auto node = parse_factor(parser);

    while (parser.current_token().type == TokenType::ARITHMETIC) {
        Token op = parser.current_token();
        parser.advance();
        auto right = parse_factor(parser);
        node = std::make_unique<BinaryExprNode>(op, std::move(node), op.value, std::move(right));
    }

    return node;
}

std::unique_ptr<ExprNode> ExpressionParser::parse_factor(Parser& parser) {
    if (parser.current_token().type == TokenType::LPARENTHESIS) {
        parser.advance();
        auto node = parse_expression(parser);
        parser.expect(TokenType::RPARENTHESIS);
        return node;
    }

    if (parser.current_token().type == TokenType::LOGICAL || parser.current_token().type == TokenType::COMPARISON || (parser.current_token().value == "-" && parser.current_token().type == TokenType::ARITHMETIC)) {
        Token op = parser.current_token();
        parser.advance();
        auto operand = parse_factor(parser);
        return std::make_unique<UnaryExprNode>(op, op.value, std::move(operand));
    }

    return PrimaryParser::parse_primary(parser);
}


