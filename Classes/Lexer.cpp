#include "Lexer.h"

Lexer::Lexer(const std::string& input)
    : input(input), pos(0), line(1), column(0), parenthesesCount(0) {
    initializeKeywords();
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

    return Token(TokenType::NUMBER, numberStr, line, column);
}

void Lexer::handleOperators(std::vector<Token>& tokens, char current) {
    if (pos == input.length() - 1) {
        std::ostringstream msg;
        msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", value " << current;
        throw std::runtime_error(msg.str());
    }

    switch (current) {
    case '+': case '-': case '*': case '/':
        handleCalculationOperators(tokens, current);
        break;
    case '=':
        tokens.push_back(Token(TokenType::ASSIGN, "=", line, column));
        ++pos;
        ++column;
        break;
    case '!': case '<': case '>':
        handleComparisonOperators(tokens, current);
        break;
    case '&': case '|':
        handleLogicalOperators(tokens, current);
        break;
    case '(': case ')':
        handleParentheses(tokens, current);
        break;
    case '\\':
        break; // Ignore backslashes
    case ' ':
        break; // Ignore spaces
    case '\n':
        break; // Ignore newlines
    default:
        std::ostringstream msg;
        msg << "Syntax Error: Unexpected character '" << current << "' at line " << line << ", value " << current;
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
    }
    else {
        throw std::runtime_error("Syntax error: Unrecognized or incomplete comparison operator '" + op + "' at line " + std::to_string(line) + ", value " + current);
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
        throw std::runtime_error("Syntax error: Unrecognized or incomplete logical operator '" + op + "' at line " + std::to_string(line) + ", value " + current);
    }
}

void Lexer::handleCalculationOperators(std::vector<Token>& tokens, char current) {
    std::string op(1, current);
    TokenType type = TokenType::PLUS;  // Default to PLUS for initialization

    while (pos + 1 < input.length() && std::isspace(input[pos + 1])) {
        ++pos;  // Move past the whitespace
        ++column;
    }

    ++pos;
    ++column;

    if (pos < input.length() && std::isdigit(input[pos])) {
        tokens.push_back(Token(type, op, line, column)); // Add the operator
        tokens.push_back(readNumber()); // Read the number
    }
    else if (pos < input.length() && (input[pos] == '+' || input[pos] == '-' || input[pos] == '*' || input[pos] == '/')) {
        char nextOp = input[pos];
        if (current == '-' && nextOp == '-') {
            type = TokenType::PLUS;
            ++pos;  // Skip the next minus
            ++column;
            while (pos < input.length() && std::isspace(input[pos])) {
                ++pos;
                ++column;
            }
            if (std::isdigit(input[pos])) {
                tokens.push_back(Token(type, "+", line, column));  // Use + instead of --
                tokens.push_back(readNumber());
            }
            else {
                std::ostringstream msg;
                msg << "Syntax error: Expected a number after '--' at line " << line << ", value " << input[pos];
                throw std::runtime_error(msg.str());
            }
        }
        else if (current == '-' && std::isdigit(input[pos + 1])) {
            tokens.push_back(Token(TokenType::MINUS, "-", line, column));
            ++pos; // Move past the minus
            ++column;
            tokens.push_back(readNumber());
        }
        else {
            std::ostringstream msg;
            msg << "Syntax error: Invalid use of consecutive operators at line " << line << ", value " << input[pos];
            throw std::runtime_error(msg.str());
        }
    }
    else {
        tokens.push_back(Token(type, op, line, column));
    }
}

void Lexer::handleParentheses(std::vector<Token>& tokens, char current) {
    size_t savePos = pos;
    size_t saveColumn = column;

    ++pos;
    ++column;

    if (current == '(') {
        tokens.push_back(Token(TokenType::LPAREN, "(", line, column));
        parenthesesCount++;
    }
    else if (current == ')') {
        parenthesesCount--;
        if (parenthesesCount < 0) {
            std::ostringstream msg;
            msg << "Syntax error: Unmatched closing parenthesis at line " << line << ", value " << input[pos];
            throw std::runtime_error(msg.str());
        }
        tokens.push_back(Token(TokenType::RPAREN, ")", line, column));
    }
}

Token Lexer::readIdentifier() {
    size_t start = pos;
    while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
        ++pos;
        ++column;
    }
    std::string identifier = input.substr(start, pos - start);

    if (keywords.find(identifier) != keywords.end()) {
        return Token(keywords[identifier], identifier, line, column);
    }
    return Token(TokenType::IDENTIFIER, identifier, line, column);
}

bool Lexer::isOperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '=' || op == '!' || op == '<' || op == '>' || op == '&' || op == '|' || op == '(' || op == ')');
}