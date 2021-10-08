#ifndef TOKEN_H
#define TOKEN_H 
#include <string>
#include "llvm/ADT/StringRef.h"
#define TOKEN_PTR std::unique_ptr<Token>

namespace rigel {

enum TokenType
{
    EOI,
    ILLEGAL,
    IDENT,
    INT,
    STR,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    BOOL,
    BANG,
    ASSIGN,
    LET
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
    std::string getLiteral() { return literal.str(); }
};

};

#endif