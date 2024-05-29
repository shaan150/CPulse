// Lexer.h
#pragma once
#include "Enums/TokenTypes.h"
#include "Structs/Token.h"
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "VariableTypes.h"

class Lexer {
public:
    explicit Lexer(const std::string& input); // Constructor that takes the input string
    std::vector<Token> tokenize(); // Method to tokenize the input string

private:
    std::string input; // The input string to be tokenized
    size_t pos;        // Current position in the input string
    size_t line;       // Current line number in the input string for error reporting
    size_t column;     // Current column number in the input string for error reporting
    int parenthesesCount; // Count of parentheses for error checking
    std::unordered_map<std::string, TokenType> keywords;

    void initializeKeywords() {
        keywords = {
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"and", TokenType::LOGICAL_AND},
            {"or", TokenType::LOGICAL_OR},
            {"not", TokenType::NOT},
            {"print", TokenType::PRINT}
        };
    }

    std::string preprocessing(const std::string& input); // Method to get the current line for error reporting without whitespace

    // Method to read a number from the input string and return a Token
    Token readNumber();

    // Method to handle operators, taking the current operator character and the tokens vector
    void handleOperators(std::vector<Token>& tokens, char current);

    void handleCalculationOperators(std::vector<Token>& tokens, char current);

    void handleComparisonOperators(std::vector<Token>& tokens, char current);

    void handleLogicalOperators(std::vector<Token>& tokens, char current);

    void handleParentheses(std::vector<Token>& tokens, char current);

    Token readIdentifier(); // Method to read an identifier and return a Token

    // Utility method to check if a TokenType is considered an operator
    bool isOperator(char);
};