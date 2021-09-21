#include <iostream>
#include <memory>
#include "../include/rigel/Lexer.h"
using namespace rigel;

#include <vector>
Token tok[] = {
    Token(TokenType::INT, "1"),
    Token(TokenType::PLUS, "+"),
    Token(TokenType::INT, "2"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "3"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::INT, "4"),
    Token(TokenType::STR, "PopVirus"),
    Token(TokenType::BANG, "!"),
    Token(TokenType::BOOL, "ture")
};
int count = 0;

Lexer::Lexer(const llvm::StringRef &code)
{
    bufferStart = code.begin();
    bufferPtr = bufferStart;
}

void Lexer::skipSpace()
{
    while(*bufferPtr == ' ') {
        bufferPtr++;
    }
}

TOKEN_PTR Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    bufferPtr = end;
    return TOKEN_PTR(new Token(TokenType::INT, literal));
}

TOKEN_PTR Lexer::makeStrToken()
{
    const char *end = bufferPtr + 1;
    while(isalpha(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    bufferPtr = end;
    return TOKEN_PTR(new Token(TokenType::STR, literal));
}

TOKEN_PTR Lexer::makeToken(TokenType type, const llvm::StringRef &literal)
{
    bufferPtr++;
    return TOKEN_PTR(new Token(type, literal));
}

Token Lexer::nextToken()
{
    return tok[count++];
}

TOKEN_PTR Lexer::lex()
{
    TOKEN_PTR token;

    skipSpace();

    switch (*bufferPtr)
    {
    case '+':
        token = makeToken(TokenType::PLUS, "+");
        break;
    case '-':
        token = makeToken(TokenType::MINUS, "-");
        break;
    case '*':
        token = makeToken(TokenType::ASTERISK, "*");
        break;
    case '/':
        token = makeToken(TokenType::SLASH, "/");
        break;
    case '!':
        token = makeToken(TokenType::BANG, "!");
        break;
    default:
        if(isdigit(*bufferPtr))
        {
            token = makeIntToken();
        }
        else if(isalpha(*bufferPtr))
        {
            token = makeStrToken();
        }
        break;
    }
    return token;
}