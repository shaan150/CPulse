#include "CPulse.h"

namespace fs = std::filesystem;

void CPulse::processFile(const std::string& filePath, const std::string& title) {
    if (!title.empty()) {
		std::cout << "Processing " << title << "..." << std::endl;
	}
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
       /* for (const auto& token : tokens) {
			std::cout << "Token: " << token.value << " Type: " << tokenTypeToString(token.type) << std::endl;
		}*/
        CodeGenerator codeGen;
        Parser parser(tokens, codeGen);  // Initialize the parser with the tokens
        parser.parse();  // Parse the tokens


    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    file.close();

    // print a ascii line
    std::cout << std::string(80, '-') << std::endl;
}

int main() {

    CPulse cpulse;
    cpulse.processFile("stage1_test.txt", "Test 1");
    cpulse.processFile("stage2_test.txt", "Test 2");
    cpulse.processFile("stage3_test.txt", "Test 3");
    cpulse.processFile("stage4_test.txt", "Test 4");
    cpulse.processFile("stage5_test.txt", "Test 5");
    cpulse.processFile("list_test.txt", "Test 6");


    return 0;
}
