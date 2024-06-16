#include "PrimaryParser.h"
#include <Parser/Parser.h>
#include <stdexcept>
#include <Parser/Statement/StatementParser.h>
#include <Parser/Expression/ExpressionParser.h>

std::unique_ptr<ExprNode> PrimaryParser::parse_primary(Parser& parser) {
    Token token = parser.current_token();

    if (token.type == TokenType::INTEGER) {
        int value = std::stoi(token.value);
        return ExpressionParser::parse_numeric_node<IntegerNode>(parser, token, value);
    }

    if (token.type == TokenType::DOUBLE) {
        double value = std::stod(token.value);
        return ExpressionParser::parse_numeric_node<DoubleNode>(parser, token, value);
    }

    if (token.type == TokenType::STRING) {
        parser.advance();
        return std::make_unique<StringNode>(token, token.value);
    }

    if (token.type == TokenType::BOOLEAN) {
        parser.advance();
        return std::make_unique<BooleanNode>(token, token.value == "true");
    }

    if (token.type == TokenType::IDENTIFIER) {
        std::string identifier = token.value;
        return identifier_handler(parser, token, identifier);
    }

    if (token.type == TokenType::TYPE) {
        parser.advance();
        return handle_functions(parser, token.value);
    }

    if (token.type == TokenType::EOFI || token.type == TokenType::EOL) {
        return nullptr;
    }

    if (parser.current_token().type == TokenType::FUNCTION) {
        return parse_function_definition(parser);
    }

    std::string line = std::to_string(token.line);
    throw std::runtime_error("Syntax Error: Invalid Token " + token.value + " at line " + line);
}

std::unique_ptr<ExprNode> PrimaryParser::identifier_handler(Parser& parser, Token& token, std::string& identifier) {
    parser.advance();
    Token newToken = parser.current_token();
    if (newToken.type == TokenType::EQUAL) {
        return handle_assignment(parser, token, identifier);
    }
    else if (newToken.type == TokenType::METHOD_ACCESS) {
        return handle_method_access(parser, token, identifier);
    }
    else if (newToken.type == TokenType::LBRACKET) {
        return handle_list_index(parser, token, identifier);
    }

    return handle_functions(parser, identifier);
}

std::unique_ptr<ExprNode> PrimaryParser::handle_assignment(Parser& parser, Token& token, std::string& identifier) {
    parser.advance();
    Token newToken = parser.current_token();
    if (newToken.type == TokenType::EQUAL) {
        // It's an equality comparison
        parser.advance();
        auto value = ExpressionParser::parse_expression(parser);
        token.type = TokenType::COMPARISON;
        return std::make_unique<BinaryExprNode>(token, std::make_unique<VariableNode>(token, identifier), "==", std::move(value));
    }
    else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "list") {
        parser.advance();
        newToken = parser.current_token();
        if (newToken.type == TokenType::COLON) {
            // Advance as we can get the type of the list
            parser.advance();
            if (parser.current_token().type == TokenType::TYPE) {
                auto type = parser.current_token().value;
                parser.advance();
                parser.expect(TokenType::LPARENTHESIS);
                parser.expect(TokenType::RPARENTHESIS);
                return std::make_unique<ListInitNode>(token, identifier, type);
            }
        }
    }
    else {
        // It's an assignment
        auto value = ExpressionParser::parse_expression(parser);
        return std::make_unique<AssignNode>(token, identifier, std::move(value));
    }
}

std::unique_ptr<ExprNode> PrimaryParser::handle_method_access(Parser& parser, Token& token, std::string& identifier) {
    parser.advance();
    Token newToken = parser.current_token();

    if (newToken.type == TokenType::IDENTIFIER && newToken.value == "append") {
        parser.advance();
        parser.expect(TokenType::LPARENTHESIS);
        auto value = ExpressionParser::parse_expression(parser);
        parser.expect(TokenType::RPARENTHESIS);
        return std::make_unique<ListAppendNode>(token, identifier, std::move(value));
    }
    else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "pop") {
        parser.advance();
        parser.expect(TokenType::LPARENTHESIS);
        auto value = ExpressionParser::parse_expression(parser);
        parser.expect(TokenType::RPARENTHESIS);
        return std::make_unique<ListPopNode>(token, identifier, std::move(value));
    }
    else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "length") {
        parser.advance();
        parser.expect(TokenType::LPARENTHESIS);
        parser.expect(TokenType::RPARENTHESIS);
        return std::make_unique<ListLengthNode>(token, identifier);
    }
    else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "replace") {
        parser.advance();
        parser.expect(TokenType::LPARENTHESIS);
        auto index = ExpressionParser::parse_expression(parser);
        parser.expect(TokenType::COMMA);
        auto value = ExpressionParser::parse_expression(parser);
        parser.expect(TokenType::RPARENTHESIS);
        return std::make_unique<ListReplaceNode>(token, identifier, std::move(index), std::move(value));
    }
    else {
        std::string line = std::to_string(newToken.line);
        throw std::runtime_error("Syntax Error: Invalid Method " + newToken.value + " at line " + line);
    }
}

std::unique_ptr<ExprNode> PrimaryParser::handle_list_index(Parser& parser, Token& token, std::string& identifier) {
    parser.advance();
    auto index = ExpressionParser::parse_expression(parser);
    parser.expect(TokenType::RBRACKET);
    return std::make_unique<ListIndexNode>(token, identifier, std::move(index));
}

std::unique_ptr<ExprNode> PrimaryParser::handle_functions(Parser& parser, std::string& identifier) {
    Token token = parser.current_token();

    if (token.type == TokenType::LPARENTHESIS) {
        // Function call
        parser.advance();

        std::vector<std::unique_ptr<ExprNode>> args;
        if (parser.current_token().type != TokenType::RPARENTHESIS) {
            while (true) {
                args.push_back(ExpressionParser::parse_expression(parser));
                if (parser.current_token().type == TokenType::RPARENTHESIS) {
                    break;
                }
                parser.expect(TokenType::COMMA);
            }
        }
        parser.expect(TokenType::RPARENTHESIS);
        if (identifier == "print") {
            check_arguments(args, 1, identifier, token);

            return std::make_unique<PrintNode>(token, std::move(args[0])); // Assuming print takes only one argument
        }
        else if (identifier == "input") {
            // create a print node to print the value
            check_arguments(args, 1, identifier, token);
            auto printNode = std::make_unique<PrintNode>(token, std::move(args[0])); // Assuming input takes only one argument
            return std::make_unique<InputNode>(token, std::move(printNode));
        }
        else if (identifier == "int" || identifier == "double" || identifier == "string" || identifier == "bool") {
            check_arguments(args, 1, identifier, token);
            return std::make_unique<TypeCastNode>(token, identifier, std::move(args[0])); // Assuming type casts take only one argument
        }
        return std::make_unique<FunctionCallNode>(token, identifier, std::move(args));
    }

    return std::make_unique<VariableNode>(token, identifier);
}

std::unique_ptr<ExprNode> PrimaryParser::parse_function_definition(Parser& parser) {
    Token funcToken = parser.current_token(); // This should be the 'func' token
    parser.advance();

    std::string returnType = parse_return_type(parser);
    std::string functionName = parse_function_name(parser);
    std::vector<std::pair<std::string, std::string>> parameters = parse_parameters(parser);

    bool hasReturnStatement = false;
    auto body = parse_function_body(parser, hasReturnStatement);

    if (returnType != "void" && !hasReturnStatement) {
        throw std::runtime_error("Syntax Error: Missing return statement in function '" + functionName + "' at line " + std::to_string(funcToken.line));
    }

    return std::make_unique<FunctionDefNode>(funcToken, functionName, returnType, std::move(parameters), std::move(body));
}

std::string PrimaryParser::parse_return_type(Parser& parser) {
    parser.expect(TokenType::COLON);
    Token returnTypeToken = parser.current_token();
    parser.expect(TokenType::TYPE);
    return returnTypeToken.value;
}

std::string PrimaryParser::parse_function_name(Parser& parser) {
    Token nameToken = parser.current_token();
    parser.expect(TokenType::IDENTIFIER);
    return nameToken.value;
}

std::vector<std::pair<std::string, std::string>> PrimaryParser::parse_parameters(Parser& parser) {
    std::vector<std::pair<std::string, std::string>> parameters;
    parser.expect(TokenType::LPARENTHESIS);
    if (parser.current_token().type != TokenType::RPARENTHESIS) {
        while (true) {
            Token paramNameToken = parser.current_token();
            parser.expect(TokenType::IDENTIFIER);
            std::string paramName = paramNameToken.value;

            parser.expect(TokenType::COLON);
            Token paramTypeToken = parser.current_token();
            parser.expect(TokenType::TYPE);
            std::string paramType = paramTypeToken.value;

            parameters.emplace_back(paramName, paramType);

            if (parser.current_token().type == TokenType::RPARENTHESIS) {
                break;
            }
            parser.expect(TokenType::COMMA);
        }
    }
    parser.expect(TokenType::RPARENTHESIS);
    return parameters;
}

std::unique_ptr<BlockNode> PrimaryParser::parse_function_body(Parser& parser, bool& hasReturnStatement) {
    parser.expect(TokenType::LBRACE);
    std::vector<std::unique_ptr<ExprNode>> statements;
    while (parser.current_token().type != TokenType::RBRACE) {
        auto statement = StatementParser::parse_statement(parser);
        if (dynamic_cast<ReturnNode*>(statement.get()) != nullptr) {
            hasReturnStatement = true;
        }
        statements.push_back(std::move(statement));
    }
    parser.expect(TokenType::RBRACE);
    Token blockToken = parser.current_token();
    return std::make_unique<BlockNode>(blockToken, std::move(statements));
}

// argument error if arguments are missing are not equal 
void PrimaryParser::check_arguments(const std::vector<std::unique_ptr<ExprNode>>& args, int expectedArgs, std::string functionName, Token& token) {
    std::string line = std::to_string(token.line);
    if (args.empty()) {
        throw std::runtime_error("Syntax Error: Missing Argument For " + functionName + " Function at line " + line);
    }
    if (args.size() != expectedArgs) {
		throw std::runtime_error("Syntax Error: Expected " + std::to_string(expectedArgs) + " Arguments For " + functionName + " Function at line " + line);
	}
}