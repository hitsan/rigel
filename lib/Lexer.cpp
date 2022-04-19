#include <memory>
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Token/Declarator.h"
using namespace rigel;

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

char Lexer::peekChar()
{
    return *(bufferPtr+1);
}

CharType Lexer::getCharType()
{
    const char charactor = *bufferPtr;
    if(isdigit(charactor))
    {
        return CharType::Integer;
    }
    else if(charactor == '\"')
    {
        return CharType::String;
    }
    else if(isalpha(charactor))
    {
        return CharType::Keyword;
    }


}

std::unique_ptr<Token> Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end)) { end++; }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    bufferPtr = end;
    return std::unique_ptr<Token>(new Token(TokenType::INT, literal));
}

std::unique_ptr<Token> Lexer::makeStrToken()
{
    const char *end = bufferPtr + 1;
    while((*end) != '"') {
        if(peekChar() == '\0') {
            return std::unique_ptr<Token>(new Token(TokenType::ILLEGAL, ""));
        }
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr + 1, end - bufferPtr - 1);
    bufferPtr = end + 1;
    return std::unique_ptr<Token>(new Token(TokenType::STR, literal));
}

std::unique_ptr<Token> Lexer::makeKeyToken()
{
    const char *end = bufferPtr + 1;
    while(isalpha(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    auto type = findTokenType(literal);
    bufferPtr = end;
    return std::unique_ptr<Token>(new Token(type, literal));
}

std::unique_ptr<Token> Lexer::makeOpeToken()
{
    llvm::StringRef ope = llvm::StringRef(bufferPtr, 1);
    TokenType optype =  findOperatorType(ope);
    bufferPtr++;
    return std::unique_ptr<Token>(new Token(optype, ope));
}

std::unique_ptr<Token> Lexer::fetchToken()
{
    if(!(*bufferPtr))
    {
        return std::unique_ptr<Token>(new Token(TokenType::EOI, ""));
    }

    std::unique_ptr<Token> token;
    skipSpace();

    switch (*bufferPtr)
    {
    case '+':
        token = makeOpeToken();
        break;
    case '-':
        token = makeOpeToken();
        break;
    case '*':
        token = makeOpeToken();
        break;
    case '/':
        token = makeOpeToken();
        break;
    case '!':
        token = makeOpeToken();
        break;
    case '=':
        token = makeOpeToken();
        break;
    case '\"':
        token = makeStrToken();
        break;
    case '\n':
        token = makeOpeToken();
        break;
    default:
        if(isdigit(*bufferPtr))
        {
            token = makeIntToken();
        }
        else if(isalpha(*bufferPtr))
        {
            token = makeKeyToken();
        }
        break;
    }
    return token;
}