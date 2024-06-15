#pragma once
#include <Parser/Parser.h>

/**
 * @class StatementParser
 * @brief Provides functionality to parse different types of statements in the input code.
 */
class StatementParser {
public:
    /**
     * @brief Parses a sequence of statements from the input using the given parser.
     * @param parser The parser to use for parsing the statements.
     * @return A unique pointer to the parsed AST node representing the block of statements.
     */
    static std::unique_ptr<ASTNode> parse_statements(Parser& parser);

    /**
     * @brief Parses a single statement from the input using the given parser.
     * @param parser The parser to use for parsing the statement.
     * @return A unique pointer to the parsed expression node representing the statement.
     */
    static std::unique_ptr<ExprNode> parse_statement(Parser& parser);

    /**
     * @brief Parses a return statement from the input using the given parser.
     * @param parser The parser to use for parsing the return statement.
     * @return A unique pointer to the parsed expression node representing the return statement.
     */
    static std::unique_ptr<ExprNode> parse_return_statement(Parser& parser);

    /**
     * @brief Parses a while loop statement from the input using the given parser.
     * @param parser The parser to use for parsing the while loop statement.
     * @return A unique pointer to the parsed expression node representing the while loop statement.
     */
    static std::unique_ptr<ExprNode> parse_while_statement(Parser& parser);

    /**
     * @brief Parses an if statement from the input using the given parser.
     * @param parser The parser to use for parsing the if statement.
     * @return A unique pointer to the parsed expression node representing the if statement.
     */
    static std::unique_ptr<ExprNode> parse_if_statement(Parser& parser);

    /**
     * @brief Parses a block of statements from the input using the given parser.
     * @param parser The parser to use for parsing the block of statements.
     * @return A unique pointer to the parsed block node representing the block of statements.
     */
    static std::unique_ptr<BlockNode> parse_statements_block(Parser& parser);

    /**
     * @brief Parses a print statement from the input using the given parser.
     * @param parser The parser to use for parsing the print statement.
     * @return A unique pointer to the parsed expression node representing the print statement.
     */
    static std::unique_ptr<ExprNode> parse_print_statement(Parser& parser);
};
