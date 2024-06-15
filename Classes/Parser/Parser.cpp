#include "Parser.h"
#include <stdexcept>
#include "Statement/StatementParser.h"

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
    if (current_token().type == TokenType::EOFI) {
        return;
    }

    while (current_token().type == TokenType::EOL && type != TokenType::EOL) {
        advance();
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
    return StatementParser::parse_statements(*this);
}
