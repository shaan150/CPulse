#pragma once

#include <vector>
#include <string>
#include <memory> // For std::unique_ptr
#include "Token.h" // Ensure this is correctly pathed to your Token definition
#include "AST.h"   // Include the header for your AST node definitions
#include "CodeGenerator.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    // Changes the return type of parseProgram if you decide to evaluate or do something with the AST here
    void parseProgram();

    double evaluate(std::unique_ptr<ExprNode> node);

    // Returns the root of the AST for the entire program

private:
    const std::vector<Token>& tokens;
    size_t current;

    // Changed return types to std::unique_ptr<ExprNode> to reflect AST construction
    std::unique_ptr<ExprNode> expression();
    std::unique_ptr<ExprNode> term();
    std::unique_ptr<ExprNode> factor();
    std::unique_ptr<NumberNode> number();

    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type) const;
    bool isAtEnd() const;
    void consume(TokenType type, const std::string& message);
    const Token& advance();
    const Token& peek() const;
};
