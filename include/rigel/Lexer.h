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
public:
    Lexer(const llvm::StringRef &code);
    void skipSpace();
    char peekChar();
    std::unique_ptr<Token> getNextToken();
    bool isCurTokenType(TokenType type);
    bool isPeekTokenType(TokenType type);
    std::unique_ptr<Token> makeIntToken();
    std::unique_ptr<Token> makeStrToken();
    std::unique_ptr<Token> makeKeyToken();
    std::unique_ptr<Token> makeToken(TokenType type, const llvm::StringRef &literal);
    std::unique_ptr<Token> lex();
    void showBuffer() { llvm::outs() << Lexer::bufferStart << "\n"; }
};
};

#endif