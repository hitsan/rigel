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
    IntLiteral(int literal) { this->literal = literal; };
    int getLiteral() { return this->literal; };
};

class StrLiteral
{
private:
    std::string literal;
public:
    StrLiteral(std::string literal) { this->literal = literal; };
    std::string getLiteral() { return this->literal; };
};

class LetStatement
{
public:
    LetStatement() {};
};

class Identifier
{
private:
    std::string name;
public:
    Identifier(std::string name) { this->name = name; };
    std::string getName() { return this->name; };
};

};

#endif