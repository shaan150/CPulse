#include "CPulse.h"
#include "TokenType.h"
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
        std::vector<Token> tokens = lexer.tokenize(); // Tokenize the entire content

        // print the tokens
        for (const auto& token : tokens) {
			std::cout << "Token: " << token.value << " Type: " << tokenTypeToString(token.type) << std::endl;
		}
        CodeGenerator codeGen;
        Parser parser(tokens, codeGen);  // Initialize the parser with the tokens
        parser.parse();  // Parse the tokens


    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    file.close();
}

int main() {

    CPulse cpulse;
    cpulse.processFile("variable_test.txt");

    return 0;
}
