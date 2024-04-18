#include "Lexer.h"
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <iostream>

Lexer::Lexer(const std::string& input)
    : input(input), pos(0), line(1), column(0), parenthesesCount(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    int parenthesesCount = 0;

    // Keyword map for Boolean and logical operators
    const std::unordered_map<std::string, TokenType> keywords = {
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"and", TokenType::LOGICAL_AND},
        {"or", TokenType::LOGICAL_OR},
        {"not", TokenType::NOT}
    };

    while (pos < input.length()) {
        const char current = input[pos];
        ++column;


        if (std::isdigit(current) || current == '.') {
            tokens.push_back(readNumber());
            continue;
        }

        // Handle line continuation
        if (current == '\\' && (pos + 1 < input.length()) && input[pos + 1] == '\n') {
            pos += 2; // Skip both the backslash and the newline
            ++line; // Increment line count
            column = 0; // Reset column count at the start of the new line
            continue; // Skip further processing and continue tokenization on the new line
        }

        if (current == '\n') {
            // check if the previous character was anything other than a whitespace if it is then throw an error
            if (input[pos - 1] == ' ') {
				std::ostringstream msg;
				msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", column " << column;
				throw std::runtime_error(msg.str());
			}
            tokens.push_back(Token(TokenType::EOL, "\\n", line, column));
            column = 0;
            ++line;
            parenthesesCount = 0;
            ++pos;
            continue;
        }

        if (std::isspace(current)) {
            ++pos; // Skip whitespaces
            continue;
        }

        // Handle keywords and identifiers
        if (std::isalpha(current)) {
            std::string word;
            while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
                word += input[pos++];
                ++column;
            }
            auto found = keywords.find(word);
            if (found != keywords.end()) {
                tokens.push_back(Token(found->second, word, line, column));
            }
            else {
                throw std::runtime_error("Syntax error: Unknown keyword or identifier '" + word + "' at line " + std::to_string(line) + ", column " + std::to_string(column));
            }
            continue;
        }

        // Handle operators and punctuation
        handleOperators(tokens, current);
        ++pos;
    }

    if (parenthesesCount != 0) {
        throw std::runtime_error("Syntax error: Unmatched opening parenthesis at end of input.");
    }

    tokens.push_back(Token(TokenType::EOFI, "", line, column));
    return tokens;
}

Token Lexer::readNumber() {
    size_t start = pos;
    size_t startColumn = column;
    bool decimalFound = false;

    while (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
        if (input[pos] == '.' && decimalFound) {
            throw std::runtime_error("Syntax error: Multiple decimal points found in number at line " + std::to_string(line) + ", column " + std::to_string(column));
        }
        decimalFound = decimalFound || input[pos] == '.';
        ++pos;
        ++column;
    }

    std::string numberStr = input.substr(start, pos - start);
    if (numberStr == ".") {
        throw std::runtime_error("Syntax error: Lone decimal point is not a valid number at line " + std::to_string(line) + ", column " + std::to_string(startColumn));
    }

    return Token(TokenType::NUMBER, numberStr, line, column);
}

void Lexer::handleOperators(std::vector<Token>& tokens, char current) {

    // check if this is the last character in the input

    if (pos == input.length() - 1) {
		std::ostringstream msg;
		msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", column " << column;
		throw std::runtime_error(msg.str());
	}

    switch (current) {
    case '+': case '-': case '*': case '/':
        // Check next character to handle cases like +=, -=, etc., if needed
        handleCalculationOperators(tokens, current);
        break;
    case '=': case '!': case '<': case '>':
        handleComparisonOperators(tokens, current);
        break;
    case '&': case '|':
        handleLogicalOperators(tokens, current);
        break;
    case '(': case ')':
        handleParentheses(tokens, current);
        break;
    default:
        std::ostringstream msg;
        msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", column " << column;
        throw std::runtime_error(msg.str());
    }

}

void Lexer::handleComparisonOperators(std::vector<Token>& tokens, char current) {
    std::string op(1, current); // Start with the current character
    ++pos; ++column; // Move past the first character

    if (current == '=' && input[pos] == '=') {
        op += input[pos++];
        ++column;
        tokens.push_back(Token(TokenType::EQUAL_TO, op, line, column));
    }
    else if (current == '!' && input[pos] == '=') {
        op += input[pos++];
        ++column;
        tokens.push_back(Token(TokenType::NOT_EQUAL, op, line, column));
    }
    else if ((current == '<' || current == '>') && input[pos] == '=') {
        op += input[pos++];
        ++column;
        TokenType type = (current == '<') ? TokenType::LESS_EQUAL : TokenType::GREATER_EQUAL;
        tokens.push_back(Token(type, op, line, column));
    }
    else if (current == '<' || current == '>') {
        TokenType type = (current == '<') ? TokenType::LESS_THAN : TokenType::GREATER_THAN;
        tokens.push_back(Token(type, std::string(1, current), line, column));
    }
    else if (current == '!') {
		tokens.push_back(Token(TokenType::NOT, "!", line, column));
        pos--; // Move back to the '!' character to handle it as a separate token
	}
    else {
        throw std::runtime_error("Syntax error: Unrecognized or incomplete comparison operator '" + op + "' at line " + std::to_string(line) + ", column " + std::to_string(column));
        }

    }

void Lexer::handleLogicalOperators(std::vector<Token>& tokens, char current) {
    std::string op(1, current); // Start with the current character
    if ((current == '&' && input[pos + 1] == '&') ||
        (current == '|' && input[pos + 1] == '|')) {
        op += input[++pos];
        ++column;
        TokenType type = (current == '&') ? TokenType::LOGICAL_AND : TokenType::LOGICAL_OR;
        tokens.push_back(Token(type, op, line, column));
        ++pos; // Move past the second character of the operator
    }
    else {
        throw std::runtime_error("Syntax error: Unrecognized or incomplete logical operator '" + op + "' at line " + std::to_string(line) + ", column " + std::to_string(column));
    }
}

void Lexer::handleCalculationOperators(std::vector<Token>& tokens, char current) {
    // Start with the current character
    std::string op(1, current);
    TokenType type = TokenType::PLUS;  // Default to PLUS to handle initialization

    // Determine the operator type
    switch (current) {
    case '+':
        type = TokenType::PLUS;
        break;
    case '-':
        type = TokenType::MINUS;
        break;
    case '*':
        type = TokenType::MULTIPLY;
        break;
    case '/':
        type = TokenType::DIVIDE;
        break;
    default:
        // Throw an error if the operator is unrecognized
        std::ostringstream msg;
        msg << "Syntax error: Unrecognized operator '" << current << "' at line " << line << ", column " << column;
        throw std::runtime_error(msg.str());
    }

    // Move past the operator
    ++pos;
    ++column;

    // Check if the next character is a digit or another operator to handle consecutive operators
    if (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
        // If the next character is a digit, the current operator is valid and we need to tokenize the following number
        tokens.push_back(Token(type, op, line, column));

        // You might call readNumber here if you detect a digit immediately after an operator
        if (std::isdigit(input[pos]) || input[pos] == '.') {
            tokens.push_back(readNumber());
        }
    }
    else if (pos < input.length() && (input[pos] == '+' || input[pos] == '-' || input[pos] == '*' || input[pos] == '/')) {
        // Handle consecutive operators: you may want to throw an error or handle specific valid cases (e.g., negative numbers)
        std::ostringstream msg;
        msg << "Syntax error: Consecutive operators at line " << line << ", column " << column;
        throw std::runtime_error(msg.str());
    }
    else {
        // If there's no digit following the operator, push the operator as a token
        tokens.push_back(Token(type, op, line, column));
    }
}


void Lexer::handleParentheses(std::vector<Token>& tokens, char current) {
    //save the current position and column
    size_t savePos = pos;
    size_t saveColumn = column;

    // Increment position and column as we're consuming the parenthesis
    ++pos;
    ++column;

    // Check the type of parenthesis and push the corresponding token
    if (current == '(') {
        tokens.push_back(Token(TokenType::LPAREN, "(", line, column));
        // Increment the count of open parentheses
        parenthesesCount++;
    }
    else if (current == ')') {
        // Decrement the count of open parentheses
        parenthesesCount--;
        if (parenthesesCount < 0) {
            // More closing parentheses than opening ones
            std::ostringstream msg;
            msg << "Syntax error: Unmatched closing parenthesis at line " << line << ", column " << column;
            throw std::runtime_error(msg.str());
        }
        tokens.push_back(Token(TokenType::RPAREN, ")", line, column));
    }

    // Restore the position and column
	pos = savePos;
	column = saveColumn;
}

