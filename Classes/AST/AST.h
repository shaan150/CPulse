#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Structs/Token/Token.h"

/**
 * @class ASTNode
 * @brief Base class for all AST nodes.
 */
class ASTNode {
public:
    virtual ~ASTNode() = default;  ///< Ensure proper cleanup with a virtual destructor
};

/**
 * @class ExprNode
 * @brief Expression node base class for all kinds of expressions.
 */
class ExprNode : public ASTNode {
public:
    /**
     * @brief Constructor for ExprNode.
     * @param token The token associated with this expression node.
     */
    ExprNode(const Token& token) : token(token) {}
    virtual ~ExprNode() = default;

    /**
     * @brief Get the token associated with this expression node.
     * @return The token associated with this expression node.
     */
    const Token& getToken() const { return token; }

private:
    Token token;
};

/**
 * @class BinaryExprNode
 * @brief Represents a binary operation (e.g., addition, multiplication).
 */
class BinaryExprNode : public ExprNode {
public:
    /**
     * @brief Constructor for BinaryExprNode.
     * @param token The token associated with this binary expression node.
     * @param left The left operand of the binary operation.
     * @param op The operator of the binary operation.
     * @param right The right operand of the binary operation.
     */
    BinaryExprNode(const Token& token, std::unique_ptr<ExprNode> left, const std::string op, std::unique_ptr<ExprNode> right)
        : ExprNode(token), left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    const std::unique_ptr<ExprNode>& getLeft() const { return left; }
    const std::string& getOp() const { return op; }
    const std::unique_ptr<ExprNode>& getRight() const { return right; }

private:
    std::unique_ptr<ExprNode> right;
    const std::string op;
    std::unique_ptr<ExprNode> left;
};

/**
 * @class UnaryExprNode
 * @brief Represents a unary operation (e.g., negation).
 */
class UnaryExprNode : public ExprNode {
public:
    /**
     * @brief Constructor for UnaryExprNode.
     * @param token The token associated with this unary expression node.
     * @param op The operator of the unary operation.
     * @param operand The operand of the unary operation.
     */
    UnaryExprNode(const Token& token, const std::string op, std::unique_ptr<ExprNode> operand)
        : ExprNode(token), operand(std::move(operand)), op(op) {}

    const std::unique_ptr<ExprNode>& getOperand() const { return operand; }
    const std::string& getOp() const { return op; }

private:
    std::unique_ptr<ExprNode> operand;
    const std::string op;
};

/**
 * @class DoubleNode
 * @brief Represents Double literals (e.g. "3.14").
 */
class DoubleNode : public ExprNode {
public:
    /**
     * @brief Constructor for DoubleNode.
     * @param token The token associated with this double literal.
     * @param value The value of the double literal.
     */
    explicit DoubleNode(const Token& token, const double value) : ExprNode(token), value(value) {}

    const double getValue() const { return value; }

private:
    const double value;
};

/**
 * @class IntegerNode
 * @brief Represents Integer literals (e.g., "123").
 */
class IntegerNode : public ExprNode {
public:
    /**
     * @brief Constructor for IntegerNode.
     * @param token The token associated with this integer literal.
     * @param value The value of the integer literal.
     */
    explicit IntegerNode(const Token& token, const int value) : ExprNode(token), value(value) {}

    const int getValue() const { return value; }

private:
    const int value;
};

/**
 * @class StringNode
 * @brief Represents string literals (e.g., "hello").
 */
class StringNode : public ExprNode {
public:
    /**
     * @brief Constructor for StringNode.
     * @param token The token associated with this string literal.
     * @param value The value of the string literal.
     */
    explicit StringNode(const Token& token, const std::string value) : ExprNode(token), value(std::move(value)) {}

    const std::string getValue() const { return value; }

private:
    const std::string value;
};

/**
 * @class BooleanNode
 * @brief Represents boolean literals (e.g., "true", "false").
 */
class BooleanNode : public ExprNode {
public:
    /**
     * @brief Constructor for BooleanNode.
     * @param token The token associated with this boolean literal.
     * @param value The value of the boolean literal.
     */
    explicit BooleanNode(const Token& token, const bool value) : ExprNode(token), value(value) {}

    const bool getValue() const { return value; }

private:
    const bool value;
};

/**
 * @class VariableNode
 * @brief Represents a variable (e.g., "x", "y").
 */
class VariableNode : public ExprNode {
public:
    /**
     * @brief Constructor for VariableNode.
     * @param token The token associated with this variable.
     * @param name The name of the variable.
     */
    explicit VariableNode(const Token& token, const std::string name) : ExprNode(token), name(std::move(name)) {}

    const std::string getName() const { return name; }

private:
    const std::string name;
};

/**
 * @class AssignNode
 * @brief Represents an assignment (e.g., "x = 1").
 */
class AssignNode : public ExprNode {
public:
    /**
     * @brief Constructor for AssignNode.
     * @param token The token associated with this assignment.
     * @param name The name of the variable being assigned.
     * @param value The value being assigned to the variable.
     */
    AssignNode(const Token& token, const std::string name, std::unique_ptr<ExprNode> value)
        : ExprNode(token), name(std::move(name)), value(std::move(value)) {}

    const std::string getName() const { return name; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string name;
    std::unique_ptr<ExprNode> value;
};

/**
 * @class PrintNode
 * @brief Represents a print statement node.
 */
class PrintNode : public ExprNode {
public:
    /**
     * @brief Constructor for PrintNode.
     * @param token The token associated with this print statement.
     * @param expression The expression to print.
     */
    explicit PrintNode(const Token& token, std::unique_ptr<ExprNode> expression)
        : ExprNode(token), expression(std::move(expression)) {}

    const std::unique_ptr<ExprNode>& getExpression() const { return expression; }

private:
    std::unique_ptr<ExprNode> expression; ///< The expression to print
};

/**
 * @class InputNode
 * @brief Represents an input statement node.
 */
class InputNode : public ExprNode {
public:
    /**
     * @brief Constructor for InputNode.
     * @param token The token associated with this input statement.
     * @param expression The expression for the input statement.
     */
    explicit InputNode(const Token& token, std::unique_ptr<ExprNode> expression)
        : ExprNode(token), expression(std::move(expression)) {}

    const std::unique_ptr<ExprNode>& getExpression() const { return expression; }

private:
    std::unique_ptr<ExprNode> expression; ///< The expression for the input statement
};

/**
 * @class BlockNode
 * @brief Represents a block of statements.
 */
class BlockNode : public ExprNode {
public:
    /**
     * @brief Constructor for BlockNode.
     * @param token The token associated with this block.
     * @param statements The statements in the block.
     */
    BlockNode(const Token& token, std::vector<std::unique_ptr<ExprNode>> statements)
        : ExprNode(token), statements(std::move(statements)) {}

    // Delete copy constructor and copy assignment operator
    BlockNode(const BlockNode&) = delete;
    BlockNode& operator=(const BlockNode&) = delete;

    // Default move constructor and move assignment operator
    BlockNode(BlockNode&&) = default;
    BlockNode& operator=(BlockNode&&) = default;

    const std::vector<std::unique_ptr<ExprNode>>& getStatements() const { return statements; }

private:
    std::vector<std::unique_ptr<ExprNode>> statements;
};

/**
 * @class FunctionCallNode
 * @brief Represents a function call node with a name and arguments.
 */
class FunctionCallNode : public ExprNode {
public:
    /**
     * @brief Constructor for FunctionCallNode.
     * @param token The token associated with this function call.
     * @param name The name of the function.
     * @param args The arguments to the function call.
     */
    FunctionCallNode(const Token& token, const std::string& name, std::vector<std::unique_ptr<ExprNode>> args)
        : ExprNode(token), name(name), args(std::move(args)) {}

    const std::string& getName() const { return name; }
    const std::vector<std::unique_ptr<ExprNode>>& getArgs() const { return args; }

private:
    const std::string name;
    std::vector<std::unique_ptr<ExprNode>> args;
};

/**
 * @class IfNode
 * @brief Represents an if-statement node.
 */
class IfNode : public ExprNode {
public:
    /**
     * @brief Constructor for IfNode.
     * @param token The token associated with this if statement.
     * @param condition The condition for the if statement.
     * @param thenBlock The block of statements to execute if the condition is true.
     * @param elseBlock The block of statements to execute if the condition is false (optional).
     */
    IfNode(const Token& token, std::unique_ptr<ExprNode> condition, std::unique_ptr<BlockNode> thenBlock, std::unique_ptr<BlockNode> elseBlock = nullptr)
        : ExprNode(token), condition(std::move(condition)), thenBlock(std::move(thenBlock)), elseBlock(std::move(elseBlock)) {}

    const std::unique_ptr<ExprNode>& getCondition() const { return condition; }
    const std::unique_ptr<BlockNode>& getThenBlock() const { return thenBlock; }
    const std::unique_ptr<BlockNode>& getElseBlock() const { return elseBlock; }

private:
    std::unique_ptr<ExprNode> condition;
    std::unique_ptr<BlockNode> thenBlock;
    std::unique_ptr<BlockNode> elseBlock;
};

/**
 * @class WhileNode
 * @brief Represents a while loop node.
 */
class WhileNode : public ExprNode {
public:
    /**
     * @brief Constructor for WhileNode.
     * @param token The token associated with this while loop.
     * @param condition The condition for the while loop.
     * @param block The block of statements to execute while the condition is true.
     */
    WhileNode(const Token& token, std::unique_ptr<ExprNode> condition, std::unique_ptr<BlockNode> block)
        : ExprNode(token), condition(std::move(condition)), block(std::move(block)) {}

    const std::unique_ptr<ExprNode>& getCondition() const { return condition; }
    const std::unique_ptr<BlockNode>& getBlock() const { return block; }

private:
    std::unique_ptr<ExprNode> condition;
    std::unique_ptr<BlockNode> block;
};

/**
 * @class ListInitNode
 * @brief Represents the initialization of a list with a specified element type.
 */
class ListInitNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListInitNode.
     * @param token The token associated with this list initialization.
     * @param name The name of the list.
     * @param elementType The type of the elements in the list.
     */
    ListInitNode(const Token& token, const std::string& name, const std::string& elementType)
        : ExprNode(token), name(name), elementType(elementType) {}

    const std::string& getName() const { return name; }
    const std::string& getElementType() const { return elementType; }

private:
    const std::string name;
    const std::string elementType;
};

/**
 * @class ListAppendNode
 * @brief Represents an append operation to a list.
 */
class ListAppendNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListAppendNode.
     * @param token The token associated with this list append operation.
     * @param listName The name of the list.
     * @param value The value to append to the list.
     */
    ListAppendNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> value)
        : ExprNode(token), listName(listName), value(std::move(value)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> value;
};

/**
 * @class ListIndexNode
 * @brief Represents an indexing operation on a list.
 */
class ListIndexNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListIndexNode.
     * @param token The token associated with this list indexing operation.
     * @param listName The name of the list.
     * @param index The index to access in the list.
     */
    ListIndexNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> index)
        : ExprNode(token), listName(listName), index(std::move(index)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getIndex() const { return index; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> index;
};

/**
 * @class ListLengthNode
 * @brief Represents an operation to get the length of a list.
 */
class ListLengthNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListLengthNode.
     * @param token The token associated with this list length operation.
     * @param listName The name of the list.
     */
    ListLengthNode(const Token& token, const std::string& listName)
        : ExprNode(token), listName(listName) {}

    const std::string& getListName() const { return listName; }

private:
    const std::string listName;
};

/**
 * @class ListPopNode
 * @brief Represents an operation to remove an element from a list at a specified index.
 */
class ListPopNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListPopNode.
     * @param token The token associated with this list pop operation.
     * @param listName The name of the list.
     * @param index The index of the element to remove from the list.
     */
    ListPopNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> index)
        : ExprNode(token), listName(listName), index(std::move(index)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getIndex() const { return index; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> index;
};

/**
 * @class ListReplaceNode
 * @brief Represents an operation to replace an element in a list at a specified index with a new value.
 */
class ListReplaceNode : public ExprNode {
public:
    /**
     * @brief Constructor for ListReplaceNode.
     * @param token The token associated with this list replace operation.
     * @param listName The name of the list.
     * @param index The index of the element to replace.
     * @param value The new value to place at the specified index.
     */
    ListReplaceNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> index, std::unique_ptr<ExprNode> value)
        : ExprNode(token), listName(listName), index(std::move(index)), value(std::move(value)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getIndex() const { return index; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> index;
    std::unique_ptr<ExprNode> value;
};

/**
 * @class TypeCastNode
 * @brief Represents a type cast operation (e.g., converting one type to another).
 */
class TypeCastNode : public ExprNode {
public:
    /**
     * @brief Constructor for TypeCastNode.
     * @param token The token associated with this type cast operation.
     * @param type The type to cast to.
     * @param value The value to be cast.
     */
    TypeCastNode(const Token& token, const std::string& type, std::unique_ptr<ExprNode> value)
        : ExprNode(token), type(type), value(std::move(value)) {}

    const std::string& getType() const { return type; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string type;
    std::unique_ptr<ExprNode> value;
};

/**
 * @class FunctionDefNode
 * @brief Represents a function definition node.
 */
class FunctionDefNode : public ExprNode {
public:
    /**
     * @brief Constructor for FunctionDefNode.
     * @param token The token associated with this function definition.
     * @param name The name of the function.
     * @param returnType The return type of the function.
     * @param parameters The parameters of the function.
     * @param body The body of the function.
     */
    FunctionDefNode(const Token& token, const std::string& name, const std::string& returnType, std::vector<std::pair<std::string, std::string>> parameters, std::unique_ptr<BlockNode> body)
        : ExprNode(token), name(name), returnType(returnType), parameters(std::move(parameters)), body(std::move(body)) {}

    // Delete copy constructor and copy assignment operator
    FunctionDefNode(const FunctionDefNode&) = delete;
    FunctionDefNode& operator=(const FunctionDefNode&) = delete;

    // Default move constructor and move assignment operator
    FunctionDefNode(FunctionDefNode&&) = default;
    FunctionDefNode& operator=(FunctionDefNode&&) = default;

    const std::string& getName() const { return name; }
    const std::string& getReturnType() const { return returnType; }
    const std::vector<std::pair<std::string, std::string>>& getParameters() const { return parameters; }
    const std::unique_ptr<BlockNode>& getBody() const { return body; } // Return by reference for modification

private:
    std::string name;
    std::string returnType;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::unique_ptr<BlockNode> body;
};

/**
 * @class ReturnNode
 * @brief Represents a return statement (e.g., return expr;).
 */
class ReturnNode : public ExprNode {
public:
    /**
     * @brief Constructor for ReturnNode.
     * @param token The token associated with this return statement.
     * @param value The value to return.
     */
    ReturnNode(const Token& token, std::unique_ptr<ExprNode> value)
        : ExprNode(token), value(std::move(value)) {}

    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    std::unique_ptr<ExprNode> value;
};
