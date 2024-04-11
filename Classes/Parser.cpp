#include "Parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

void Parser::parseProgram() {
    CodeGenerator codegen; // Instance of CodeGenerator

    while (!isAtEnd()) {
        auto expr = expression(); // Parse an expression to get an AST
        if (expr != nullptr) {
            // Use CodeGenerator to compile and execute the expression
            codegen.generateCode(expr.get()); // Adjust generateCode as needed to execute the code
        }
        // Advance past the EOL token, if present, before parsing the next expression
        match({ TokenType::EOL });
    }
}

std::unique_ptr<ExprNode> Parser::expression() {
    auto node = term();
    while (match({ TokenType::PLUS, TokenType::MINUS })) {
        Token op = tokens[current - 1];
        auto right = term();
        char opChar = (op.type == TokenType::PLUS) ? '+' : '-';
        node = std::make_unique<BinaryExprNode>(std::move(node), opChar, std::move(right));
    }
    return node;
}

std::unique_ptr<ExprNode> Parser::term() {
    auto node = factor();
    while (match({ TokenType::MULTIPLY, TokenType::DIVIDE })) {
        Token op = tokens[current - 1];
        auto right = factor();
        if (op.type == TokenType::MULTIPLY) {
            node = std::make_unique<BinaryExprNode>(std::move(node), '*', std::move(right));
        }
        else if (op.type == TokenType::DIVIDE) {
            node = std::make_unique<BinaryExprNode>(std::move(node), '/', std::move(right));
        }
    }
    return node;
}

std::unique_ptr<ExprNode> Parser::factor() {
    if (match({ TokenType::MINUS })) {
        auto operand = factor();
        return std::make_unique<UnaryExprNode>('-', std::move(operand));
    }
    else if (match({ TokenType::NUMBER })) {
        double value = std::stod(tokens[current - 1].value);
        return std::make_unique<NumberNode>(value);
    }
    else if (match({ TokenType::LPAREN })) {
        auto expr = expression();
        consume(TokenType::RPAREN, "Expect ')' after expression.");
        return expr;
    }
    throw std::runtime_error("Expect expression.");
}

std::unique_ptr<NumberNode> Parser::number() {
    consume(TokenType::NUMBER, "Expect number.");
    double value = std::stod(tokens[current - 1].value);
    return std::make_unique<NumberNode>(value);
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOFI;
}

void Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) advance();
    else throw std::runtime_error(message);
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

const Token& Parser::peek() const {
    return tokens[current];
}
