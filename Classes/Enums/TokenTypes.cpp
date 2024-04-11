#include "TokenTypes.h"

std::string tokenTypeToString(TokenType type)
{
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::EOL: return "EOL";
        case TokenType::EOFI: return "EOFI";
    default: return "UNKNOWN";
    }
}
