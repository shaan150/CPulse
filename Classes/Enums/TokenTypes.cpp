#include "TokenTypes.h"

std::string tokenTypeToString(TokenType type)
{
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::EQUAL_TO: return "EQUAL_TO";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS_THAN: return "LESS_THAN";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LOGICAL_AND: return "LOGICAL_AND";
        case TokenType::LOGICAL_OR: return "LOGICAL_OR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::NOT: return "NOT";
        case TokenType::EOL: return "EOL";
        case TokenType::EOFI: return "EOFI";
    default: return "UNKNOWN";
    }
}
