#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "llvm/ADT/StringRef.h"

namespace rigel {

enum TokenType
{
    INT,
    PLUS,
    MUL,
    FIRST
};

class Token
{
private:
    TokenType type;
    llvm::StringRef literal;
public:
    Token* next;
    Token(TokenType type, llvm::StringRef literal);
    TokenType getTokenType() { return type; }
    llvm::StringRef getLiteral() { return literal; }
    void getNext();
};

};

#endif