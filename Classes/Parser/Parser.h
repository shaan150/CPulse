#pragma once

#include <vector>
#include <memory>
#include "Token/Token.h"
#include "AST/AST.h"
#include "CodeGenerator/CodeGenerator.h"
#include <unordered_set>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens, CodeGenerator& codeGen);

    std::unique_ptr<ASTNode> parse();

private:
    const std::vector<Token>& tokens;
    const std::unordered_set<std::string> reservedWords = { "if", "else", "while", "print", "input" };
    size_t pos;
    CodeGenerator& codeGen;

    const Token& current_token() const;
    void advance();
    void expect(TokenType type);

    friend class StatementParser;
    friend class ExpressionParser;
    friend class PrimaryParser;
};