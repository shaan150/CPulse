#pragma once

#include <vector>
#include <memory>
#include "Token/Token.h"
#include "AST/AST.h"
#include "CodeGenerator/CodeGenerator.h"
#include <unordered_set>

/**
 * @class Parser
 * @brief Responsible for parsing tokens into an abstract syntax tree (AST) and interacting with the code generator.
 */
class Parser {
public:
    /**
     * @brief Constructs a Parser with the given tokens and code generator.
     * @param tokens The vector of tokens to be parsed.
     * @param codeGen The code generator to use for executing the parsed AST.
     */
    explicit Parser(const std::vector<Token>& tokens, CodeGenerator& codeGen);

    /**
     * @brief Parses the tokens and returns a unique pointer to the resulting AST.
     * @return A unique pointer to the parsed AST node representing the program.
     */
    std::unique_ptr<ASTNode> parse();

private:
    const std::vector<Token>& tokens; ///< The vector of tokens to be parsed.
    const std::unordered_set<std::string> reservedWords = { "if", "else", "while", "print", "input" }; ///< Reserved words in the language.
    size_t pos; ///< Current position in the token vector.
    CodeGenerator& codeGen; ///< Reference to the code generator.

    /**
     * @brief Returns the current token being parsed.
     * @return A reference to the current token.
     */
    const Token& current_token() const;

    /**
     * @brief Advances to the next token in the vector.
     */
    void advance();

    /**
     * @brief Expects the current token to be of a specific type and advances to the next token.
     * @param type The expected token type.
     * @throws std::runtime_error if the current token is not of the expected type.
     */
    void expect(TokenType type);

    friend class StatementParser;
    friend class ExpressionParser;
    friend class PrimaryParser;
};