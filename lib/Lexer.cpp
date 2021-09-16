#include "../include/rigel/Lexer.h"
using namespace rigel;

#include <iostream>

Lexer::Lexer(llvm::StringRef code)
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

void Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    auto tok = Token(TokenType::INT, literal);
}

void Lexer::makeToken(TokenType type, std::string literal)
{
        auto tok = Token(type, literal);
}

void Lexer::lex()
{
    while(bufferPtr)
    {
        skipSpace();

        switch (*bufferPtr)
        {
        case '+':
            makeToken(TokenType::PLUS, "+");
            break;
        case '*':
            makeToken(TokenType::ASTERISK, "*");
            break;            
        default:
            if(isdigit(*bufferPtr))
            {
                makeIntToken();
            }
            break;
        }
    }
}