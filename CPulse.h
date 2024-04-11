// CPulse.h
#pragma once

#include <string>
#include "classes/Lexer.h"
#include "classes/Parser.h"

class CPulse {
public:
    // Process a file containing arithmetic expressions
    void processFile(const std::string& filePath);
};
