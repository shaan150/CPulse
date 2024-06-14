#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Structs/Token/Token.h"

// Base class for all AST nodes.
class ASTNode {
public:
    virtual ~ASTNode() = default;  // Ensure proper cleanup with a virtual destructor
};

// Expression node base class for all kinds of expressions.
class ExprNode : public ASTNode {
public:
    ExprNode(const Token& token) : token(token) {}
    virtual ~ExprNode() = default;

    const Token& getToken() const { return token; }

private:
    Token token;
};

// Represents a binary operation (e.g., addition, multiplication).
class BinaryExprNode : public ExprNode {
public:
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

// Represents a unary operation (e.g., negation).
class UnaryExprNode : public ExprNode {
public:
    UnaryExprNode(const Token& token, const std::string op, std::unique_ptr<ExprNode> operand)
        : ExprNode(token), operand(std::move(operand)), op(op) {}

    const std::unique_ptr<ExprNode>& getOperand() const { return operand; }
    const std::string& getOp() const { return op; }

private:
    std::unique_ptr<ExprNode> operand;
    const std::string op;

};

// Represents Double literals (e.g. "3.14").
class DoubleNode : public ExprNode {
public:
    explicit DoubleNode(const Token& token, const double value) : ExprNode(token), value(value) {}

    const double getValue() const { return value; }

private:
    const double value;
};

// Represents Integer literals (e.g., "123").
class IntegerNode : public ExprNode {
public:
    explicit IntegerNode(const Token& token, const int value) : ExprNode(token), value(value) {}

    const int getValue() const { return value; }
private:
    const int value;
};

// Represents string literals (e.g., "hello").
class StringNode : public ExprNode {
public:
    explicit StringNode(const Token& token, const std::string value) : ExprNode(token), value(std::move(value)) {}

    const std::string getValue() const { return value; }

private:
    const std::string value;
};

// Represents boolean literals (e.g., "true", "false").
class BooleanNode : public ExprNode {
public:
    explicit BooleanNode(const Token& token, const bool value) : ExprNode(token), value(value) {}

    const bool getValue() const { return value; }

private:
    const bool value;
};

// Represents a variable (e.g., "x", "y").
class VariableNode : public ExprNode {
public:
    explicit VariableNode(const Token& token, const std::string name) : ExprNode(token), name(std::move(name)) {}

    const std::string getName() const { return name; }

private:
    const std::string name;
};

// Represents an assignment (e.g., "x = 1").
class AssignNode : public ExprNode {
public:
    AssignNode(const Token& token, const std::string name, std::unique_ptr<ExprNode> value)
        : ExprNode(token), name(std::move(name)), value(std::move(value)) {}

    const std::string getName() const { return name; }

    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string name;
    std::unique_ptr<ExprNode> value;
};

// Represents a function node with a name
class PrintNode : public ExprNode {
public:
    explicit PrintNode(const Token& token, std::unique_ptr<ExprNode> expression)
        : ExprNode(token), expression(std::move(expression)) {}

    const std::unique_ptr<ExprNode>& getExpression() const { return expression; }
private:
    std::unique_ptr<ExprNode> expression; // The expression to print
};


// Represents a function node with a name
class InputNode : public ExprNode {
public:
    explicit InputNode(const Token& token, std::unique_ptr<ExprNode> expression)
        : ExprNode(token), expression(std::move(expression)) {}

    const std::unique_ptr<ExprNode>& getExpression() const { return expression; }
private:
    std::unique_ptr<ExprNode> expression; // The expression to print
};

// Represents a block node with a list of statements
class BlockNode : public ExprNode {
public:
    explicit BlockNode(const Token& token, std::vector<std::unique_ptr<ExprNode>> statements)
        : ExprNode(token), statements(std::move(statements)) {}

    const std::vector<std::unique_ptr<ExprNode>>& getStatements() const { return statements; }

private:
    std::vector<std::unique_ptr<ExprNode>> statements;
};

// Represents a function call node with a name and arguments
class FunctionCallNode : public ExprNode {
public:
    explicit FunctionCallNode(const Token& token, const std::string name, std::unique_ptr<ExprNode> arg)
        : ExprNode(token), name(std::move(name)), arg(std::move(arg)) {}

    const std::string getName() const { return name; }
    const std::unique_ptr<ExprNode>& getArg() const { return arg; }

private:
    const std::string name;
    std::unique_ptr<ExprNode> arg;
};

// Represents an if-statement node
class IfNode : public ExprNode {
public:
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

// Represents a while loop node
class WhileNode : public ExprNode {
public:
    WhileNode(const Token& token, std::unique_ptr<ExprNode> condition, std::unique_ptr<BlockNode> block)
        : ExprNode(token), condition(std::move(condition)), block(std::move(block)) {}

    const std::unique_ptr<ExprNode>& getCondition() const { return condition; }
    const std::unique_ptr<BlockNode>& getBlock() const { return block; };
private:
    std::unique_ptr<ExprNode> condition;
    std::unique_ptr<BlockNode> block;
};

class ListInitNode : public ExprNode {
public:
    ListInitNode(const Token& token, const std::string& name, const std::string& elementType)
        : ExprNode(token), name(name), elementType(elementType) {}

    const std::string& getName() const { return name; }
    const std::string& getElementType() const { return elementType; }

private:
    const std::string name;
    const std::string elementType;
};

class ListAppendNode : public ExprNode {
public:
    ListAppendNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> value)
        : ExprNode(token), listName(listName), value(std::move(value)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> value;
};

class ListIndexNode : public ExprNode {
public:
    ListIndexNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> index)
        : ExprNode(token), listName(listName), index(std::move(index)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getIndex() const { return index; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> index;
};

class ListLengthNode : public ExprNode {
public:
    ListLengthNode(const Token& token, const std::string& listName)
        : ExprNode(token), listName(listName) {}

    const std::string& getListName() const { return listName; }

private:
    const std::string listName;
};

class ListPopNode : public ExprNode {
public:
    ListPopNode(const Token& token, const std::string& listName, std::unique_ptr<ExprNode> index)
        : ExprNode(token), listName(listName), index(std::move(index)) {}

    const std::string& getListName() const { return listName; }
    const std::unique_ptr<ExprNode>& getIndex() const { return index; }

private:
    const std::string listName;
    std::unique_ptr<ExprNode> index;
};

class ListReplaceNode : public ExprNode {
public:
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

class TypeCastNode : public ExprNode {
public:
    TypeCastNode(const Token& token, const std::string& type, std::unique_ptr<ExprNode> value)
        : ExprNode(token), type(type), value(std::move(value)) {}

    const std::string& getType() const { return type; }
    const std::unique_ptr<ExprNode>& getValue() const { return value; }
private:
    const std::string type;
    std::unique_ptr<ExprNode> value;
};;