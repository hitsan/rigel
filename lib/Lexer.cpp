#include <iostream>
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

Token Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end))
    {
        end++;

    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    return Token(TokenType::INT, literal);
}

Token Lexer::makeStrToken()
{
    const char *end = bufferPtr + 1;
    while(isalpha(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    return Token(TokenType::STR, literal);
}

Token Lexer::makeToken(TokenType type, std::string literal)
{
    return  Token(type, literal);
}

Token Lexer::nextToken()
{
    return tok[count++];
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
        case '-':
            makeToken(TokenType::MINUS, "-");
            break;
        case '*':
            makeToken(TokenType::ASTERISK, "*");
            break;
        case '/':
            makeToken(TokenType::SLASH, "/");
            break;
        case '!':
            makeToken(TokenType::BANG, "!");
            break;
        default:
            if(isdigit(*bufferPtr))
            {
                makeIntToken();
            }
            else if(isalpha(*bufferPtr))
            {
                makeStrToken();
            }
            break;
        }
    }
}