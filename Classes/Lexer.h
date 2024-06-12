// Lexer.h
#pragma once
#include "Enums/TokenType.h"
#include "Structs/Token/Token.h"
#include "Structs/Maps/OperatorMap.h"
#include "Structs/Maps/KeywordMap.h"
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <iostream>

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

    std::string preprocessing(const std::string& input); // Method to get the current line for error reporting without whitespace

    // Method to read a number from the input string and return a Token
    Token readNumber();

    // Method to handle operators, taking the current operator character and the tokens vector
    void handleOperators(std::vector<Token>& tokens, char current);

    void handleParentheses(std::vector<Token>& tokens, char current);

    Token readIdentifier(); // Method to read an identifier and return a Token

};