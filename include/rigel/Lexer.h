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
    std::unique_ptr<Token> curToken;
    std::unique_ptr<Token> peekToken;
    void skipSpace();
    char peekChar();
    std::unique_ptr<Token> makeIntToken();
    std::unique_ptr<Token> makeStrToken();
    std::unique_ptr<Token> makeKeyToken();
    std::unique_ptr<Token> makeToken(TokenType type, const llvm::StringRef &literal);
    std::unique_ptr<Token> lex();
public:
    Lexer(const llvm::StringRef &code);
    std::unique_ptr<Token> getNextToken();
    bool hasCurTokenType(TokenType type);
    bool hasPeekTokenType(TokenType type);
};
};

#endif