#pragma once
#include <Parser/Parser.h>

class StatementParser {
public:
    static std::unique_ptr<ASTNode> parse_statements(Parser& parser);
    static std::unique_ptr<ExprNode> parse_statement(Parser& parser);
    static std::unique_ptr<ExprNode> parse_return_statement(Parser& parser);
    static std::unique_ptr<ExprNode> parse_while_statement(Parser& parser);
    static std::unique_ptr<ExprNode> parse_if_statement(Parser& parser);
    static std::unique_ptr<BlockNode> parse_statements_block(Parser& parser);
    static std::unique_ptr<ExprNode> parse_print_statement(Parser& parser);
};