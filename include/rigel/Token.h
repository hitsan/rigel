#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "llvm/ADT/StringRef.h"

namespace rigel {

enum TokenType
{
    INT,
    STR,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    BANG
};

class Token
{
private:
    TokenType type;
    llvm::StringRef literal;
public:
    Token(TokenType type, llvm::StringRef literal)
    {
    this->type = type;
    this->literal = literal;
    };
    TokenType getTokenType() { return type; }
    llvm::StringRef getLiteral() { return literal; }
};

};

#endif