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
    Lexer(llvm::StringRef code);
    void skipSpace();
    void peekChar();
    Token makeIntToken();
    Token makeStrToken();
    Token makeToken(TokenType type, std::string literal);
    Token nextToken();
    void lex();

};
};

#endif