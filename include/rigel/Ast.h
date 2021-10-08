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

};

#endif