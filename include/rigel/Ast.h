#ifndef AST_H
#define AST_H
#include <string>
#include "Token.h"
#include "llvm/ADT/StringRef.h"
namespace rigel {

// template<typename T>
// class Ast
// {
// protected:
//     Token token;
//     T value;
// public:
//     Ast(const std::string value) = 0;
//     Ast<int>(std::string value) = 0;
// };

class IntegerLiteral
{
protected:
    int value;
public:
    IntegerLiteral(llvm::StringRef value) { this->value = std::stoi(value.str()); };
    int getLiteral() { return value; };
};

};

#endif