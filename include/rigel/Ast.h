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
    NT_MUL
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
    IntLiteral* integer;
public:
    LetStatement(Identifier ident, IntLiteral* integer) : ident(ident), integer(integer) {};
    std::string getName() { return ident.getName(); };
    int getValue() { return integer->getValue(); }
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

// class PlusExpression : public BinarlyExpression
// {
// public:
//     PlusExpression(NodeType type, IntLiteral lHand, IntLiteral rHand) : BinarlyExpression(type, lHand, rHand) {};
// };

// class MulExpression : public BinarlyExpression
// {
// public:
//     MulExpression(NodeType type, IntLiteral lHand, IntLiteral rHand) : BinarlyExpression(type, lHand, rHand) {};
// };

};

#endif