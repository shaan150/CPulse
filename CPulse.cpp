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
    std::string base_path = "Files/";
    std::string extension = ".txt";
    int test_number = 1;

   // run all tests in the Files directory with the .txt extension
    for (const auto& entry : fs::directory_iterator(base_path)) {
        if (entry.path().extension() == extension) {
			cpulse.processFile(entry.path().string(), "Test " + std::to_string(test_number));
			test_number++;
		}
	}

    return 0;
}
