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
};

class Expression{};

class IntLiteral : public Expression
{
private:
    int value;
public:
    IntLiteral(int value) : value(value) {};
    int getValue() { return this->value; };
};

class StrLiteral : public Expression
{
private:
    std::string value;
public:
    StrLiteral(std::string value) : value(value) {};
    std::string getValue() { return this->value; };
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
    NodeType type;
    Expression* lHand;
    Expression* rHand;
public:
    BinaryExpression(NodeType type, Expression* lHand, Expression* rHand) : type(type), lHand(lHand), rHand(rHand) {};
    NodeType getType() { return type; }; 
    Expression* getLHand() { return lHand; };
    Expression* getRHand() { return rHand; };
};

class ReturnStatement : public Expression
{
protected:
    Expression* expression;
public:
    ReturnStatement(Expression* expression) : expression(expression) {};
    Expression* getExpression() { return expression; };
};

};

#endif