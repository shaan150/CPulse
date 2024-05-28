#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens),  // This initializes the member 'tokens' with a copy of the input parameter 'tokens'.
    current(0)      // Initializing 'current' to 0.
{}

void Parser::parse() {
	CodeGenerator codeGen;
	try {
		while (!isAtEnd()) {
			if (peek().type == TokenType::EOFI) { // Check for the end-of-file indicator
				break;
			}
			auto expr = expression(); // Parse the expression into an AST
			if (expr) {
				codeGen.execute(expr.get()); // Execute the parsed expression using the CodeGenerator
			}
			if (!match({ TokenType::EOL, TokenType::EOFI })) { // Ensure each expression ends with a newline or EOF
				synchronize(); // Synchronize to the next line if the current line ends improperly
			}
		}
	}
	catch (const std::runtime_error& error) {
		std::cerr << "Parse error: " << error.what() << std::endl; // Handle any parsing errors
	}
}

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (TokenType type : types) {
        if (check(type)) {
			advance();
			return true;
		}
	}

	return false;
}

bool Parser::check(TokenType type) const
{
    if(isAtEnd()) return false;

	return peek().type == type;
}

Token Parser::advance()
{
	if (!isAtEnd()) current++;

	return previous();
}

bool Parser::isAtEnd() const
{
	return peek().type == TokenType::EOFI;
}

Token Parser::peek() const
{
	return tokens[current];
}

Token Parser::previous() const
{
	if (current > 0) {
		return tokens[current - 1];
	}

	return tokens[0];
}

void Parser::consume(TokenType type, const std::string& message) {

	if (type == TokenType::EOL) throw std::runtime_error("Expected a token, got EOL");

	if (check(type)) {
		advance();  // Move to the next token
	}
}

std::unique_ptr<ExprNode> Parser::declaration() {
	if (match({ TokenType::IDENTIFIER }) && match({ TokenType::ASSIGN })) {
		std::string varName = previous().value;
		std::unique_ptr<ExprNode> value = expression();
		variables[varName] = std::move(value);
		return std::make_unique<VariableAssignNode>(varName, std::move(value));  // Custom node type for assignments
	}
	return expression();  // Fall back to parsing a regular expression
}


std::unique_ptr<ExprNode> Parser::expression()
{
	return logicalOr();
}

std::unique_ptr<ExprNode> Parser::logicalOr()
{
	std::unique_ptr<ExprNode> expr = logicalAnd();

	while (match({ TokenType::LOGICAL_OR })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = logicalAnd();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::logicalAnd()
{
	std::unique_ptr<ExprNode> expr = equality();

	while (match({ TokenType::LOGICAL_AND })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = equality();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::equality()
{
	std::unique_ptr<ExprNode> expr = comparison();

	while (match({ TokenType::EQUAL_TO, TokenType::NOT_EQUAL })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = comparison();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::comparison()
{
	std::unique_ptr<ExprNode> expr = term();

	while (match({ TokenType::LESS_THAN, TokenType::LESS_EQUAL, TokenType::GREATER_THAN, TokenType::GREATER_EQUAL })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = term();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::term()
{
	std::unique_ptr<ExprNode> expr = factor();

	while (match({ TokenType::PLUS, TokenType::MINUS })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = factor();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::factor()
{
	std::unique_ptr<ExprNode> expr = unary();

	while (match({ TokenType::MULTIPLY, TokenType::DIVIDE })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = unary();
		expr = std::make_unique<BinaryExprNode>(std::move(expr), tokenTypeToString(op.type), std::move(right));
	}

	return expr;
}

std::unique_ptr<ExprNode> Parser::unary(){

	if (match({ TokenType::MINUS, TokenType::NOT })) {
		Token op = previous();
		std::unique_ptr<ExprNode> right = unary();
		return std::make_unique<UnaryExprNode>(tokenTypeToString(op.type), std::move(right));
	}

	return primary();
}

std::unique_ptr<ExprNode> Parser::primary() {
	if (match({ TokenType::NUMBER })) {
		// Convert string to double and create a number node
		double value = std::stod(previous().value);
		return std::make_unique<NumberNode>(value);
	}

	if (match({ TokenType::STRING })) {
		// Create a string node based on the token value
		std::string value = previous().value;
		return std::make_unique<StringNode>(value);
	}

	if (match({ TokenType::FALSE, TokenType::TRUE })) {
		// Create a boolean node based on the token type
		bool value = previous().type == TokenType::TRUE;
		return std::make_unique<BooleanNode>(value);
	}
	if (match({ TokenType::LPAREN })) {
		// Parse the expression inside the parentheses
		
		std::unique_ptr<ExprNode> expr = expression();
		consume(TokenType::RPAREN, "Expected ')' after expression");
		return expr;
	}

	throw std::runtime_error("Expected an expression");

}

void Parser::synchronize() {
	advance(); // Skip the problematic token

	while (!isAtEnd()) {
		if (previous().type == TokenType::EOL) return; // Stop if the previous token was the end of a line

		// Check if the next token marks the beginning of a new statement
		switch (peek().type) {
		case TokenType::EOL:  // End of a line
		case TokenType::PLUS:
		case TokenType::MINUS:
		case TokenType::MULTIPLY:
		case TokenType::DIVIDE:
		case TokenType::EQUAL_TO:
		case TokenType::NOT_EQUAL:
		case TokenType::LESS_THAN:
		case TokenType::GREATER_THAN:
		case TokenType::LESS_EQUAL:
		case TokenType::GREATER_EQUAL:
		case TokenType::LPAREN:
		case TokenType::RPAREN:
			return; // Safe points to start parsing again
		default:
			advance(); // Continue to skip tokens
		}
	}
}

