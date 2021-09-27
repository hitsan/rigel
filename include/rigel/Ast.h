#ifndef AST_H
#define AST_H
#include <string>
#include "Token.h"
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
    IntegerLiteral(std::string value) { this->value = std::stoi(value); };
    int getLiteral() { return value; };
};

};

#endif