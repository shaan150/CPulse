#include "TokenType.h"

std::string tokenTypeToString(TokenType type)
{
    switch (type) {
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::DOUBLE: return "DOUBLE";
        case TokenType::STRING: return "STRING";
        case TokenType::BOOLEAN: return "BOOLEAN";
        case TokenType::TYPE: return "TYPE";
        case TokenType::COLON: return "COLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::METHOD_ACCESS: return "METHOD_ACCESS";
        case TokenType::LPARENTHESIS: return "LPARENTHESIS";
        case TokenType::RPARENTHESIS: return "RPARENTHESIS";
        case TokenType::LBRACKET: return "LBRACKET";
        case TokenType::RBRACKET: return "RBRACKET";
        case TokenType::LBRACE: return "LBRACE";
        case TokenType::RBRACE: return "RBRACE";
        case TokenType::ARITHMETIC: return "ARITHMETIC";
        case TokenType::LOGICAL: return "LOGICAL";
        case TokenType::COMPARISON: return "COMPARISON";
        case TokenType::IF_CONDITION: return "IF_CONDITION";
        case TokenType::ELSE_CONDITION: return "ELSE_CONDITION";
        case TokenType::WHILE_LOOP: return "WHILE_LOOP";
        case TokenType::RETURN: return "RETURN";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::BITWISE: return "BITWISE";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::EOL: return "EOL";
        case TokenType::EOFI: return "EOFI";
    default: return "UNKNOWN";
    }
}
