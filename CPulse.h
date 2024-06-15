// CPulse.h
#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <Parser/Parser.h>
#include "classes/Lexer/Lexer.h"
#include "TokenType.h"

class CPulse {
public:
    // Process a file containing arithmetic expressions
    void processFile(const std::string& filePath, const std::string& title);
};
