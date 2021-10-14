#ifndef AST_H
#define AST_H
#include <string>
#include "Token/Token.h"
#include "llvm/ADT/StringRef.h"
#define AST_PTR std::unique_ptr<Ast>
namespace rigel {

enum NodeType
{
    SUM
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
public:
    PlusExpression(NodeType type, IntLiteral lHand, IntLiteral rHand) {};
    NodeType getType() { return NodeType::SUM; }; 
    IntLiteral getLHand() { return IntLiteral(0); };
    IntLiteral getRHand() { return IntLiteral(0); };
};

};

#endif