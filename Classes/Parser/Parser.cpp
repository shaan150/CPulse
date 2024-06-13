// parser.cpp

#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens, CodeGenerator& codeGen)
    : tokens(tokens), pos(0), codeGen(codeGen) {}

const Token& Parser::current_token() const {
    return tokens[pos];
}

void Parser::advance() {
    if (pos < tokens.size()) {
        pos++;
    }
}

void Parser::expect(TokenType type) {
    if (type == TokenType::EOL) {
        if (current_token().type == TokenType::EOFI) {
            return;
        }
    }

    if (current_token().type != type) {
        if (type == TokenType::COMMA) {
			std::string line = std::to_string(current_token().line);
			throw std::runtime_error("Syntax Error: Expected Additional Argument At Line " + line);
		}
        std::string line = std::to_string(current_token().line);
        throw std::runtime_error("Syntax Error: Unexpected Token " + current_token().value + " at line " + line +
            "\nExpected Type: " + tokenTypeToString(type));
    }
    advance();
}

std::unique_ptr<ASTNode> Parser::parse() {
    return parse_statements();
}

std::unique_ptr<ASTNode> Parser::parse_statements() {
    std::vector<std::unique_ptr<ExprNode>> statements;
    while (current_token().type != TokenType::EOFI) {
        if (current_token().type == TokenType::EOL) {
            advance();
            continue; // Skip EOL tokens
        }
        statements.push_back(std::unique_ptr<ExprNode>(dynamic_cast<ExprNode*>(parse_statement().release())));
    }
    const Token blockToken = tokens.front();
    auto blockNode = std::make_unique<BlockNode>(blockToken, std::move(statements));
    codeGen.execute(blockNode.get());
    return blockNode;
}

std::unique_ptr<ExprNode> Parser::parse_statement() {
    const Token& token = current_token();
    if (token.type == TokenType::IF_CONDITION) {
        return parse_if_statement();
    }
    else if (token.type == TokenType::WHILE_LOOP) {
		return parse_while_statement();
	}

    else {
        auto expr = parse_expression();
        expect(TokenType::EOL);
        return expr;
    }
}

std::unique_ptr<ExprNode> Parser::parse_print_statement() {
    Token printToken = current_token();
    advance();
    expect(TokenType::LPARENTHESIS);
    auto expr = parse_expression();
    expect(TokenType::RPARENTHESIS);
    expect(TokenType::EOL);
    return std::make_unique<PrintNode>(printToken, std::move(expr));
}

std::unique_ptr<ExprNode> Parser::parse_if_statement() {
    Token ifToken = current_token();
    advance(); // Move past 'if'
    expect(TokenType::LPARENTHESIS);
    auto condition = parse_expression();
    expect(TokenType::RPARENTHESIS);
    expect(TokenType::LBRACE);
    auto thenBlock = parse_statements_block();
    expect(TokenType::RBRACE);

    std::unique_ptr<BlockNode> elseBlock = nullptr;
    if (current_token().type == TokenType::ELSE_CONDITION) {
        advance(); // Move past 'else'
        expect(TokenType::LBRACE);
        elseBlock = parse_statements_block();
        expect(TokenType::RBRACE);
    }
    return std::make_unique<IfNode>(ifToken, std::move(condition), std::move(thenBlock), std::move(elseBlock));
}

std::unique_ptr<ExprNode> Parser::parse_while_statement() {
    Token whileToken = current_token();
    advance(); // Move past 'while'
    expect(TokenType::LPARENTHESIS);
    auto condition = parse_expression();
    expect(TokenType::RPARENTHESIS);
    expect(TokenType::LBRACE);
    auto block = parse_statements_block();
    expect(TokenType::RBRACE);
    return std::make_unique<WhileNode>(whileToken, std::move(condition), std::move(block));
}

std::unique_ptr<BlockNode> Parser::parse_statements_block() {
    std::vector<std::unique_ptr<ExprNode>> statements;
    while (current_token().type != TokenType::RBRACE && current_token().type != TokenType::EOFI) {
        if (current_token().type == TokenType::EOL) {
            advance();
            continue; // Skip EOL tokens
        }
        if (current_token().type == TokenType::IF_CONDITION) {
            statements.push_back(parse_if_statement());
            continue; // Skip to the next token
        }

        if (current_token().type == TokenType::WHILE_LOOP) {
            statements.push_back(parse_while_statement());
            continue; // Skip to the next token
        }

        statements.push_back(parse_statement());
    }
    Token blockToken = tokens.front();
    return std::make_unique<BlockNode>(blockToken, std::move(statements));
}

std::unique_ptr<ExprNode> Parser::parse_expression() {
    auto left = parse_term();

    while (current_token().type == TokenType::EQUAL || current_token().type == TokenType::COMPARISON || current_token().type == TokenType::LOGICAL) {
        Token op = current_token();

        // Handle multi-character operators
        std::string opValue = op.value;
        advance();

        // Check for operators like '!=' and '=='
        if ((opValue == "!" || opValue == "=" || opValue == "<" || opValue == ">") && current_token().type == TokenType::EQUAL) {
            opValue += current_token().value;
            advance();
        }

        auto right = parse_term();

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

std::unique_ptr<ExprNode> Parser::parse_term() {
    auto node = parse_factor();

    while (current_token().type == TokenType::ARITHMETIC) {
        Token op = current_token();
        advance();
        auto right = parse_factor();
        node = std::make_unique<BinaryExprNode>(op, std::move(node), op.value, std::move(right));
    }

    return node;
}

std::unique_ptr<ExprNode> Parser::parse_factor() {
    if (current_token().type == TokenType::LPARENTHESIS) {
        advance();
        auto node = parse_expression();
        expect(TokenType::RPARENTHESIS);
        return node;
    }

    if (current_token().type == TokenType::LOGICAL || current_token().type == TokenType::COMPARISON || current_token().value == "-") {
        Token op = current_token();
        advance();
        auto operand = parse_factor();
        return std::make_unique<UnaryExprNode>(op, op.value, std::move(operand));
    }

    return parse_primary();
}

std::unique_ptr<ExprNode> Parser::parse_primary() {
    Token token = current_token();

    if (token.type == TokenType::INTEGER) {
        int value = std::stoi(token.value);
        return parse_numeric_node<IntegerNode>(token, value);
    }

    if (token.type == TokenType::DOUBLE) {
        double value = std::stod(token.value);
        return parse_numeric_node<DoubleNode>(token, value);
    }

    if (token.type == TokenType::STRING) {
        advance();
        return std::make_unique<StringNode>(token, token.value);
    }

    if (token.type == TokenType::BOOLEAN) {
        advance();
        return std::make_unique<BooleanNode>(token, token.value == "true");
    }

    if (token.type == TokenType::IDENTIFIER) {
        std::string identifier = token.value;
        return identifier_handler(token, identifier);
    }

    if (token.type == TokenType::TYPE) {
        advance();
		return handle_functions(token.value);
	}

    if (token.type == TokenType::EOFI || token.type == TokenType::EOL) {
		return nullptr;
	}

    std::string line = std::to_string(token.line);
    throw std::runtime_error("Syntax Error: Invalid Token " + token.value + " at line " + line);
}

std::unique_ptr<ExprNode> Parser::identifier_handler(Token& token, std::string& identifier)
{
    advance();
    Token newToken = current_token();
    if (newToken.type == TokenType::EQUAL) {
        advance();
        newToken = current_token();
        if (newToken.type == TokenType::EQUAL) {
            // It's an equality comparison
            advance();
            auto value = parse_expression();
            token.type = TokenType::COMPARISON;
            return std::make_unique<BinaryExprNode>(token, std::make_unique<VariableNode>(token, identifier), "==", std::move(value));
        }
        else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "list") {
            advance();
            newToken = current_token();
            if (newToken.type == TokenType::COLON) {
                // advance as we can get the type of the list
                advance();
                if (current_token().type == TokenType::TYPE) {
                    auto type = current_token().value;
                    advance();
                    expect(TokenType::LPARENTHESIS);
                    expect(TokenType::RPARENTHESIS);

                    return std::make_unique<ListInitNode>(token, identifier, type);
                }
            }
        } 
        else {
            // It's an assignment
            auto value = parse_expression();
            return std::make_unique<AssignNode>(token, identifier, std::move(value));
        }
    }
    else if (newToken.type == TokenType::METHOD_ACCESS) 
    {
        advance();
        newToken = current_token();

        if (newToken.type == TokenType::IDENTIFIER && newToken.value == "append") {
            advance();
            expect(TokenType::LPARENTHESIS);
            auto value = parse_expression();
            expect(TokenType::RPARENTHESIS);
            return std::make_unique<ListAppendNode>(token, identifier, std::move(value));
        }
        else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "pop") {
            advance();
            expect(TokenType::LPARENTHESIS);
            auto value = parse_expression();
            expect(TokenType::RPARENTHESIS);
            return std::make_unique<ListPopNode>(token, identifier, std::move(value));
        }
        else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "length") {
            advance();
            expect(TokenType::LPARENTHESIS);
            expect(TokenType::RPARENTHESIS);
            return std::make_unique<ListLengthNode>(token, identifier);
        }
        else if (newToken.type == TokenType::IDENTIFIER && newToken.value == "replace") {
            advance();
            expect(TokenType::LPARENTHESIS);
            auto index = parse_expression();
            expect(TokenType::COMMA);
            auto value = parse_expression();
            expect(TokenType::RPARENTHESIS);
            return std::make_unique<ListReplaceNode>(token, identifier, std::move(index), std::move(value));
        }
        else {
            std::string line = std::to_string(newToken.line);
            throw std::runtime_error("Syntax Error: Invalid Method " + newToken.value + " at line " + line);
        }
    }
    else if (newToken.type == TokenType::LBRACKET) {
        advance();
        auto index = parse_expression();
        expect(TokenType::RBRACKET);
        return std::make_unique<ListIndexNode>(token, identifier, std::move(index));
    }

    return handle_functions(identifier);

}

std::unique_ptr<ExprNode> Parser::handle_functions(std::string& identifier) {
    Token token = current_token();

    if (token.type == TokenType::LPARENTHESIS) {
        // Function call
        advance();
        auto arg = parse_expression();
        expect(TokenType::RPARENTHESIS);
        if (identifier == "print") {
			return std::make_unique<PrintNode>(token, std::move(arg));
		}
        else if (identifier == "input") {
            // create a print node to print the value
            auto printNode = std::make_unique<PrintNode>(token, std::move(arg));
            return std::make_unique<InputNode>(token, std::move(printNode));
        }
        else if (identifier == "int" || identifier == "double" || identifier == "string" || identifier == "bool") {
			return std::make_unique<TypeCastNode>(token, identifier, std::move(arg));
		}
        return std::make_unique<FunctionCallNode>(token, identifier, std::move(arg));
    }

    return std::make_unique<VariableNode>(token, identifier);
}

template <typename NodeType, typename ValueType>
std::unique_ptr<ExprNode> Parser::parse_numeric_node(const Token& token, ValueType value) {
    advance();

    // Handle consecutive `-` tokens
    std::unique_ptr<ExprNode> node = std::make_unique<NodeType>(token, value);

    while (current_token().type == TokenType::ARITHMETIC && current_token().value == "-") {
        Token op = current_token();
        advance();

        if (current_token().type == TokenType::ARITHMETIC && current_token().value == "-") {
            advance();
            node = std::make_unique<BinaryExprNode>(op, std::move(node), "+", parse_primary());
        }
        else {
            node = std::make_unique<BinaryExprNode>(op, std::move(node), "-", parse_primary());
        }
    }

    return node;

}
