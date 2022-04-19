#ifndef TOKEN_H
#define TOKEN_H 
#include <string>
#include "llvm/ADT/StringRef.h"
#define TOKEN_PTR std::unique_ptr<Token>

namespace rigel {

enum class TokenType
{
    EOI,
    ILLEGAL,
    IDENT,
    NEWLINE,
    INT,
    STR,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    BOOL,
    BANG,
    ASSIGN,
    LET,
    RETURN
};

class Token
{
private:
    TokenType type;
    llvm::StringRef literal;
public:
    Token(TokenType type, llvm::StringRef literal);
    bool equalsTokenType(TokenType type);
    std::string getLiteral();
};

};

#endif