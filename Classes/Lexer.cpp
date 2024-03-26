#include "Lexer.h"
#include <cctype>
#include <stdexcept>
#include <sstream> // For string formatting

Lexer::Lexer(const std::string& input) : input(input), pos(0), line(1), column(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    int parenthesesCount = 0;

    while (pos < input.length()) {
        const char current = input[pos];
        ++column; // Move to next column

        if (current == '\n') {
            // Newline: reset column, increment line, and check parentheses
            column = 0;
            ++line;
            if (parenthesesCount != 0) {
                throw std::runtime_error("Syntax error: Unmatched parentheses at end of line " + std::to_string(line - 1));
            }
            parenthesesCount = 0;
            ++pos; // Move to the next character
            continue;
        }

        if (std::isspace(current)) {
            ++pos; // Skip whitespace
        }
        else if (std::isdigit(current) || current == '.') {
            tokens.push_back(readNumber());
        }
        else {
            switch (current) {
            case '+':
            case '-':
                handleOperators(tokens, current);
                break;
            case '*':
            case '/':
                if (!tokens.empty() && isOperator(tokens.back().type)) {
                    std::ostringstream msg;
                    msg << "Syntax error: Consecutive operators at line " << line << ", column " << column;
                    throw std::runtime_error(msg.str());
                }
                tokens.push_back({ current == '*' ? TokenType::MULTIPLY : TokenType::DIVIDE, std::string(1, current) });
                ++pos;
                break;
            case '(':
                ++parenthesesCount;
                tokens.push_back({ TokenType::LPAREN, "(" });
                ++pos;
                break;
            case ')':
                if (--parenthesesCount < 0) {
                    std::ostringstream msg;
                    msg << "Syntax error: Unmatched closing parenthesis at line " << line << ", column " << column;
                    throw std::runtime_error(msg.str());
                }
                tokens.push_back({ TokenType::RPAREN, ")" });
                ++pos;
                break;
            default:
                std::ostringstream msg;
                msg << "Unexpected character '" << current << "' at line " << line << ", column " << column;
                throw std::runtime_error(msg.str());
            }
        }
    }

    if (parenthesesCount != 0) {
        throw std::runtime_error("Syntax error: Unmatched opening parenthesis at end of input.");
    }

    return tokens;
}

Token Lexer::readNumber() {
    size_t start = pos;
    size_t startColumn = column; // Track the start column for error reporting
    bool decimalFound = false;

    while (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
        if (input[pos] == '.') {
            if (decimalFound) {
                std::ostringstream msg;
                msg << "Syntax error: Invalid number format with multiple decimal points at line " << line << ", column " << startColumn;
                throw std::runtime_error(msg.str());
            }
            decimalFound = true;
        }
        ++pos;
        ++column;
    }

    std::string numberStr = input.substr(start, pos - start);
    if (numberStr == ".") {
        std::ostringstream msg;
        msg << "Syntax error: Lone decimal point is not a valid number at line " << line << ", column " << startColumn;
        throw std::runtime_error(msg.str());
    }

    return Token(TokenType::NUMBER, numberStr);
}

void Lexer::handleOperators(std::vector<Token>& tokens, char current) {
    if (!tokens.empty() && isOperator(tokens.back().type)) {
        std::ostringstream msg;
        msg << "Syntax error: Consecutive operators at line " << line << ", column " << (column - 1); // Since column was already incremented
        throw std::runtime_error(msg.str());
    }
    else {
        TokenType type = (current == '+') ? TokenType::PLUS : TokenType::MINUS;
        tokens.push_back({ type, std::string(1, current) });
    }
    ++pos;
}

bool Lexer::isOperator(TokenType type) {
    return type == TokenType::PLUS || type == TokenType::MINUS ||
        type == TokenType::MULTIPLY || type == TokenType::DIVIDE;
}


