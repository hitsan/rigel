#ifndef LEXER_H
#define LEXER_H
#include "llvm/ADT/StringRef.h"
#include "Token/Token.h"
#include "llvm/Support/raw_ostream.h"

namespace rigel {

class Lexer
{
private:
    const char *bufferStart;
    const char *bufferPtr;
    TOKEN_PTR cur;
    TOKEN_PTR peekCur;
public:
    Lexer(const llvm::StringRef &code);
    void skipSpace();
    char peekChar();
    TOKEN_PTR makeIntToken();
    TOKEN_PTR makeStrToken();
    TOKEN_PTR makeKeyToken();
    TOKEN_PTR makeToken(TokenType type, const llvm::StringRef &literal);
    TOKEN_PTR lex();
    void showBuffer() { llvm::outs() << Lexer::bufferStart << "\n"; }
};
};

#endif