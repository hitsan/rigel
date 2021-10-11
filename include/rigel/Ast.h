#ifndef AST_H
#define AST_H
#include <string>
#include "Token/Token.h"
#include "llvm/ADT/StringRef.h"
#define AST_PTR std::unique_ptr<Ast>
namespace rigel {

class IntLiteral
{
private:
    int literal;
public:
    IntLiteral(int literal) : literal(literal) {};
    int getLiteral() { return this->literal; };
};

class StrLiteral
{
private:
    std::string literal;
public:
    StrLiteral(std::string literal) : literal(literal) {};
    std::string getLiteral() { return this->literal; };
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
    int getValue() { return integer.getLiteral(); }
};

};

#endif