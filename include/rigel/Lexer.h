#ifndef LEXER_H
#define LEXER_H
#include "llvm/ADT/StringRef.h"
#include "Token/Token.h"
#include "llvm/Support/raw_ostream.h"

namespace rigel {

enum class CharType
{
    Operator,
    String,
    Integer,
    Keyword
}

class Lexer
{
private:
    const char *bufferStart;
    const char *bufferPtr;
    std::unique_ptr<Token> curToken;
    std::unique_ptr<Token> peekToken;
    void skipSpace();
    char peekChar();
    CharType getCharType();
    std::unique_ptr<Token> makeIntToken();
    std::unique_ptr<Token> makeStrToken();
    std::unique_ptr<Token> makeKeyToken();
    std::unique_ptr<Token> makeOpeToken();
public:
    Lexer(const llvm::StringRef &code);
    std::unique_ptr<Token> fetchToken();
};
};

#endif