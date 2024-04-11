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

        // Check for line continuation
        if (current == '\\' && (pos + 1 < input.length()) && input[pos + 1] == '\n') {
            pos += 2; // Skip both the backslash and the newline
            column = 0; // Reset column at the start of the new line
            ++line; // Increment line number
            continue; // Skip further processing and continue tokenization
        }

        if (current == '\n') {
            tokens.push_back(Token(TokenType::EOL, "\\n", line, column)); // Add EOL token here
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
                tokens.push_back({ TokenType::LPAREN, "(", line, column });
                ++pos;
                break;
            case ')':
                if (--parenthesesCount < 0) {
                    std::ostringstream msg;
                    msg << "Syntax error: Unmatched closing parenthesis at line " << line << ", column " << column;
                    throw std::runtime_error(msg.str());
                }
                tokens.push_back({ TokenType::RPAREN, ")", line, column });
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

    tokens.push_back(Token(TokenType::EOFI, "", line, column));

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

    return Token(TokenType::NUMBER, numberStr, line, column);
}

void Lexer::handleOperators(std::vector<Token>& tokens, char current) {
    int signCount = 1; // Start with 1 to count the current sign
    char lastSign = current; // Track the last sign encountered

    // Move to the next character and count any additional consecutive signs
    while (++pos < input.length() && (input[pos] == '+' || input[pos] == '-')) {
        if (input[pos] != lastSign) {
            // If the sign changes from '+' to '-' or '-' to '+', treat it as a syntax error for simplicity
            std::ostringstream msg;
            msg << "Syntax error: Mixed consecutive '+' and '-' signs at line " << line << ", column " << (column - signCount);
            throw std::runtime_error(msg.str());
        }
        ++signCount;
        ++column;
    }

    // Determine the resultant sign based on the count
    if (signCount >= 3) {
        // Three or more consecutive signs is a syntax error in this implementation
        std::ostringstream msg;
        msg << "Syntax error: Three or more consecutive signs at line " << line << ", column " << (column - signCount + 1);
        throw std::runtime_error(msg.str());
    }
    else if (signCount == 2 && lastSign == '-') {
        // Two consecutive '-' signs simplify to a '+', but for simplicity, we may choose not to add a token
        tokens.push_back({ TokenType::PLUS, "+" });
    }
    else if (signCount == 1) {
        // A single sign is added as is
        tokens.push_back({ lastSign == '+' ? TokenType::PLUS : TokenType::MINUS, std::string(1, lastSign), line, column });
    }
    // No need to add a token for even number of '-' for simplicity, as they cancel out
}

bool Lexer::isOperator(TokenType type) {
    return type == TokenType::PLUS || type == TokenType::MINUS ||
        type == TokenType::MULTIPLY || type == TokenType::DIVIDE;
}


