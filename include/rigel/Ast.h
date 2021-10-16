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

class IntLiteral
{
private:
    int value;
public:
    IntLiteral(int value) : value(value) {};
    int getValue() { return this->value; };
};

class StrLiteral
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
    IntLiteral integer;
public:
    LetStatement(Identifier ident, IntLiteral integer) : ident(ident), integer(integer) {};
    std::string getName() { return ident.getName(); };
    int getValue() { return integer.getValue(); }
};

class PlusExpression
{
private:
    NodeType type;
    IntLiteral lHand;
    IntLiteral rHand;
public:
    PlusExpression(NodeType type, IntLiteral lHand, IntLiteral rHand) : type(type), lHand(lHand), rHand(rHand) {};
    NodeType getType() { return NodeType::NT_PLUS; }; 
    IntLiteral getLHand() { return lHand; };
    IntLiteral getRHand() { return rHand; };
};

class MulExpression
{
private:
    NodeType type;
    IntLiteral lHand;
    IntLiteral rHand;
public:
    MulExpression(NodeType type, IntLiteral lHand, IntLiteral rHand) : type(type), lHand(lHand), rHand(rHand) {};
    NodeType getType() { return NodeType::NT_MUL; }; 
    IntLiteral getLHand() { return lHand; };
    IntLiteral getRHand() { return rHand; };
};

};

#endif