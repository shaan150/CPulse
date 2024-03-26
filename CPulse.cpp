#include "CPulse.h"
#include <fstream>
#include <iostream>

void CPulse::processFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    size_t lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        try {
            Lexer lexer(line);
            auto tokens = lexer.tokenize();

            std::cout << "Line " << lineNumber << " tokens:" << std::endl;
            for (const auto& token : tokens) {
                // Output each token; adjust as needed based on how you want to display them
                std::cout << "  " << token.value << " (" << static_cast<int>(token.type) << ")" << std::endl;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error processing line " << lineNumber << ": " << e.what() << std::endl;
        }
    }

    file.close();
}

int main() {
    CPulse cpulse;
    cpulse.processFile("path/to/your/input.txt");

    return 0;
}
