#ifndef AST_H
#define AST_H
#include <string>
#include "Token/Token.h"
#include "llvm/ADT/StringRef.h"
#define AST_PTR std::unique_ptr<Ast>
namespace rigel {

enum NodeType
{
    NT_PLUS,
    NT_MUL,
    NT_INT,
    NT_STR,
    NT_RET,
};

class Expression
{
protected:
    const NodeType type;
public:
    Expression(NodeType type) : type(type) {};
    NodeType getType() const { return type; };
};

class IntLiteral : public Expression
{
private:
    int value;
public:
    IntLiteral(int value) : Expression(NT_INT), value(value) {};
    int getValue() { return this->value; };
    static bool classof(const Expression *expr) {
        return expr->getType() == NT_INT;
    }
};

class StrLiteral : public Expression
{
private:
    std::string value;
public:
    StrLiteral(std::string value) : Expression(NT_STR), value(value) {};
    std::string getValue() { return this->value; };
    static bool classof(const Expression *expr) {
        return expr->getType() == NT_STR;
    }
};

class Identifier
{
private:
    std::string name;
public:
    Identifier(std::string name) : name(name) {};
    std::string getName() { return this->name; };
};

class LetStatement
{
private:
    Identifier ident;
    Expression* expression;
public:
    LetStatement(Identifier ident, Expression* expression) : ident(ident), expression(expression) {};
    std::string getName() { return ident.getName(); };
    Expression* getExpression() { return expression; };
};

class BinaryExpression : public Expression
{
protected:
    Expression* lHand;
    Expression* rHand;
public:
    BinaryExpression(NodeType type, Expression* lHand, Expression* rHand) : Expression(type), lHand(lHand), rHand(rHand) {};
    Expression* getLHand() { return lHand; };
    Expression* getRHand() { return rHand; };
    static bool classof(const Expression *expr) {
        auto type = expr->getType();
        return (type >= NT_PLUS) | (type >= NT_MUL);
    }
};

class ReturnStatement : public Expression
{
protected:
    Expression* expression;
public:
    ReturnStatement(Expression* expression) : Expression(NT_RET), expression(expression) {};
    Expression* getExpression() { return expression; };
    static bool classof(const Expression *expr) {
        return expr->getType() == NT_RET;
    }
};

};

#endif