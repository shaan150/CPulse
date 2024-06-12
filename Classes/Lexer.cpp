#include "Lexer.h"
#include <algorithm>

Lexer::Lexer(const std::string& input)
    : input(input), pos(0), line(1), column(0), parenthesesCount(0) {
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::string currentToken;
    bool inComment = false;
    bool inString = false;

    while (pos < input.length()) {

        if (input[pos] == '\\' && (pos + 1 < input.length()) && input[pos + 1] == '\n' && !inString && !inComment) {
            pos += 2; // Skip both the backslash and the newline
            ++line; // Increment line count
            continue; // Skip further processing and continue tokenization on the new line
        }

        if (input[pos] == '\n') {
            line++;

            if (inComment)
            {
                inComment = false;
            }

            tokens.push_back(Token(TokenType::EOL, "\\n", line, column));

            pos++;
            continue;
        }

        if ((std::isdigit(input[pos]) || input[pos] == '.') && !inComment && !inString) {
            tokens.push_back(readNumber());
            continue;
        }

        if (input[pos] == '"') {
            if (!inString) {
                inString = true;
                pos++; // skip the opening quote
                continue;
            }
            else if (inString) {
                inString = false;
                tokens.push_back(Token(TokenType::STRING, currentToken, line, column));
                currentToken.clear();
                pos++; // skip the closing quote
                continue;
            }
        }

        if (inString) {
            currentToken += input[pos];
            pos++;
            column++;
            continue;
        }

        if (std::isspace(input[pos])) {
            pos++;
            column++;
            continue;
        }

        if (std::isalpha(input[pos]) && !inString && !inComment) {
            tokens.push_back(readIdentifier());
            continue;
        }

        if (input[pos] == '#') {
            inComment = true;
            pos++;
            continue;
        }

        // Handling operators directly here
        if (!inComment && !inString && input[pos] != ' ') {
            handleOperators(tokens, input[pos]);
            continue;
        }

        pos++;
    }

    if (parenthesesCount != 0) {
        throw std::runtime_error("Unmatched opening parenthesis at end of input.");
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
            throw std::runtime_error("Syntax error: Multiple decimal points found in number at line " + std::to_string(line));
        }
        decimalFound = decimalFound || input[pos] == '.';
        ++pos;
        ++column;
    }

    std::string numberStr = input.substr(start, pos - start);
    if (numberStr == ".") {
        throw std::runtime_error("Syntax error: Lone decimal point is not a valid number at line " + std::to_string(line));
    }

    if (decimalFound) {
		return Token(TokenType::DOUBLE, numberStr, line, startColumn);
	}

    return Token(TokenType::INTEGER, numberStr, line, column);
}

void Lexer::handleOperators(std::vector<Token>& tokens, char current) {
    auto it = OperatorMap::map.find(current);
    if (it != OperatorMap::map.end()) {
        tokens.push_back(Token(it->second, std::string(1, current), line, column));
        ++pos;
        ++column;
    }
    else {
        switch (current) {
            case '\\':
            case ' ':
            case '\n':
                // Ignore backslashes, spaces, and newlines
                break;
            default:
                std::ostringstream msg;
                msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", value " << current;
                throw std::runtime_error(msg.str());
        }
    }
}

Token Lexer::readIdentifier() {
    size_t start = pos;
    while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
        ++pos;
        ++column;
    }
    std::string identifier = input.substr(start, pos - start);
    // lowercase the identifier
    std::transform(identifier.begin(), identifier.end(), identifier.begin(), ::tolower);
    auto keyword = KeywordMap::map.find(identifier);
    if (keyword != KeywordMap::map.end()) {
        return Token(keyword->second, identifier, line, column);
    }
    return Token(TokenType::IDENTIFIER, identifier, line, column);
}