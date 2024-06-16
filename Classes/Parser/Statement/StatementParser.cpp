#include "StatementParser.h"
#include <Parser/Expression/ExpressionParser.h>

std::unique_ptr<ASTNode> StatementParser::parse_statements(Parser& parser) {
    std::vector<std::unique_ptr<ExprNode>> statements;
    while (parser.current_token().type != TokenType::EOFI) {
        if (parser.current_token().type == TokenType::EOL) {
            parser.advance();
            continue; // Skip EOL tokens
        }
        statements.push_back(std::unique_ptr<ExprNode>(dynamic_cast<ExprNode*>(parse_statement(parser).release())));
    }
    const Token blockToken = parser.tokens.front();
    auto blockNode = std::make_unique<BlockNode>(blockToken, std::move(statements));
    parser.codeGen.execute(blockNode.get());
    return blockNode;
}

std::unique_ptr<ExprNode> StatementParser::parse_statement(Parser& parser) {
    const Token& token = parser.current_token();
    if (token.type == TokenType::IF_CONDITION) {
        return parse_if_statement(parser);
    }
    else if (token.type == TokenType::WHILE_LOOP) {
        return parse_while_statement(parser);
    }
    else if (token.type == TokenType::RETURN) {
        return parse_return_statement(parser);
    }
    else {
        auto expr = ExpressionParser::parse_expression(parser);
        parser.expectEOL();
        return expr;
    }
}

std::unique_ptr<ExprNode> StatementParser::parse_return_statement(Parser& parser) {
    Token returnToken = parser.current_token(); // This should be the 'return' token
    parser.advance();
    auto value = ExpressionParser::parse_expression(parser); // Assuming you have a parse_expression function
    parser.expectEOL();
    return std::make_unique<ReturnNode>(returnToken, std::move(value));
}

std::unique_ptr<ExprNode> StatementParser::parse_print_statement(Parser& parser) {
    Token printToken = parser.current_token();
    parser.advance();
    parser.expect(TokenType::LPARENTHESIS);
    auto expr = ExpressionParser::parse_expression(parser);
    parser.expect(TokenType::RPARENTHESIS);
    // check if it's the end of the line or eofi
    parser.expectEOL();

    return std::make_unique<PrintNode>(printToken, std::move(expr));
}

std::unique_ptr<ExprNode> StatementParser::parse_if_statement(Parser& parser) {
    Token ifToken = parser.current_token();
    parser.advance(); // Move past 'if'
    parser.expect(TokenType::LPARENTHESIS);
    auto condition = ExpressionParser::parse_expression(parser);
    parser.expect(TokenType::RPARENTHESIS);
    parser.expect(TokenType::LBRACE);
    auto thenBlock = parse_statements_block(parser);
    parser.expect(TokenType::RBRACE);

    std::unique_ptr<BlockNode> elseBlock = nullptr;
    while (parser.current_token().type == TokenType::EOL) {
        parser.advance();
    }

    if (parser.current_token().type == TokenType::ELSE_CONDITION) {
        parser.advance(); // Move past 'else'
        parser.expect(TokenType::LBRACE);
        elseBlock = parse_statements_block(parser);
        parser.expect(TokenType::RBRACE);
    }
    return std::make_unique<IfNode>(ifToken, std::move(condition), std::move(thenBlock), std::move(elseBlock));
}

std::unique_ptr<ExprNode> StatementParser::parse_while_statement(Parser& parser) {
    Token whileToken = parser.current_token();
    parser.advance(); // Move past 'while'
    parser.expect(TokenType::LPARENTHESIS);
    auto condition = ExpressionParser::parse_expression(parser);
    // make sure the condition is a boolean expression 
    TokenType conditionType = condition->getToken().type;
    if (condition->getToken().type != TokenType::COMPARISON && conditionType != TokenType::LOGICAL) {
		throw std::runtime_error("Syntax Error: Expected a boolean expression in the while loop condition");
	}
    parser.expect(TokenType::RPARENTHESIS);
    parser.expect(TokenType::LBRACE);
    auto block = parse_statements_block(parser);
    parser.expect(TokenType::RBRACE);
    return std::make_unique<WhileNode>(whileToken, std::move(condition), std::move(block));
}

std::unique_ptr<BlockNode> StatementParser::parse_statements_block(Parser& parser) {
    std::vector<std::unique_ptr<ExprNode>> statements;
    while (parser.current_token().type != TokenType::RBRACE && parser.current_token().type != TokenType::EOFI) {
        if (parser.current_token().type == TokenType::EOL) {
            parser.advance();
            continue; // Skip EOL tokens
        }
        if (parser.current_token().type == TokenType::IF_CONDITION) {
            statements.push_back(parse_if_statement(parser));
            continue; // Skip to the next token
        }

        if (parser.current_token().type == TokenType::WHILE_LOOP) {
            statements.push_back(parse_while_statement(parser));
            continue; // Skip to the next token
        }

        statements.push_back(parse_statement(parser));
    }
    Token blockToken = parser.tokens.front();
    return std::make_unique<BlockNode>(blockToken, std::move(statements));
}
