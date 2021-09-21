#ifndef LEXER_H
#define LEXER_H
#include "llvm/ADT/StringRef.h"
#include "./Token.h"

namespace rigel {

class Lexer
{
private:
    const char *bufferStart;
    const char *bufferPtr;
    Token* cur;
    Token* peekCur;
public:
    Lexer(const llvm::StringRef &code);
    void skipSpace();
    char peekChar();
    TOKEN_PTR makeIntToken();
    TOKEN_PTR makeStrToken();
    TOKEN_PTR makeToken(TokenType type, const llvm::StringRef &literal);
    Token nextToken();
    TOKEN_PTR lex();

};
};

#endif