#include "CPulse.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void CPulse::processFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // Read the entire contents of the file into a string
    std::ostringstream sstr;
    sstr << file.rdbuf();
    std::string content = sstr.str();

    try {
        Lexer lexer(content);  // Initialize the lexer with the entire content
        auto tokens = lexer.tokenize(); // Tokenize the entire content

        Parser parser(tokens); // Initialize the parser with the tokens
        parser.parseProgram(); // Parse the program

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    file.close();
}

int main() {

    CPulse cpulse;
    cpulse.processFile("no errors.txt");

    return 0;
}
