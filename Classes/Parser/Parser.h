// parser.h

#pragma once

#include <vector>
#include <memory>
#include "Token/Token.h"
#include "AST.h"
#include "CodeGenerator.h"
#include <unordered_set>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens, CodeGenerator& codeGen);

    std::unique_ptr<ASTNode> parse();

private:
    const std::vector<Token>& tokens;
    const std::unordered_set<std::string> reservedWords = { "if", "else", "while", "print", "input"};
    size_t pos;

    CodeGenerator& codeGen;

    const Token& current_token() const;
    void advance();

    std::unique_ptr<ASTNode> parse_statements();
    std::unique_ptr<ExprNode> parse_statement();
    std::unique_ptr<ExprNode> parse_while_statement();
    std::unique_ptr<ExprNode> parse_if_statement();
    std::unique_ptr<BlockNode> parse_statements_block();
    std::unique_ptr<ExprNode> parse_return_statement();
    std::unique_ptr<ExprNode> parse_expression();
    std::unique_ptr<ExprNode> parse_term();
    std::unique_ptr<ExprNode> parse_factor();
    std::unique_ptr<ExprNode> parse_primary();
    std::unique_ptr<ExprNode> parse_function();
    std::unique_ptr<ExprNode> identifier_handler(Token& token, std::string& identifier);
    std::unique_ptr<ExprNode> handle_functions(std::string& identifier);
    std::unique_ptr<ExprNode> parse_print_statement();
    template<typename NodeType, typename ValueType>
    std::unique_ptr<ExprNode> parse_numeric_node(const Token& token, ValueType value);

    void expect(TokenType type);
};