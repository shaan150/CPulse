#ifndef PRIMARYPARSER_H

#include "AST/AST.h"

class Parser;

class PrimaryParser {
public:
    static std::unique_ptr<ExprNode> parse_primary(Parser& parser);
    static std::unique_ptr<ExprNode> identifier_handler(Parser& parser, Token& token, std::string& identifier);
    static std::unique_ptr<ExprNode> handle_functions(Parser& parser, std::string& identifier);
    static std::unique_ptr<ExprNode> parse_function_definition(Parser& parser);
private:
    static std::string parse_return_type(Parser& parser);
    static std::string parse_function_name(Parser& parser);
    static std::vector<std::pair<std::string, std::string>> parse_parameters(Parser& parser);
    static std::unique_ptr<BlockNode> parse_function_body(Parser& parser, bool& hasReturnStatement);
    static std::unique_ptr<ExprNode> handle_assignment(Parser& parser, Token& token, std::string& identifier);
    static std::unique_ptr<ExprNode> handle_method_access(Parser& parser, Token& token, std::string& identifier);
    static std::unique_ptr<ExprNode> handle_list_index(Parser& parser, Token& token, std::string& identifier);
};

#endif // PRIMARYPARSER_H