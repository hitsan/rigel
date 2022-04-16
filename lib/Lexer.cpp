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
    curToken = makeToken();
    peekToken = makeToken();
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

std::unique_ptr<Token> Lexer::makeOpeToken(TokenType type, const llvm::StringRef &literal)
{
    bufferPtr++;
    return std::unique_ptr<Token>(new Token(type, literal));
}

std::unique_ptr<Token> Lexer::makeToken()
{
    if(!(*bufferPtr))
    {
        return makeOpeToken(TokenType::EOI, "");
    }

    std::unique_ptr<Token> token;
    skipSpace();

    switch (*bufferPtr)
    {
    case '+':
        token = makeOpeToken(TokenType::PLUS, "+");
        break;
    case '-':
        token = makeOpeToken(TokenType::MINUS, "-");
        break;
    case '*':
        token = makeOpeToken(TokenType::ASTERISK, "*");
        break;
    case '/':
        token = makeOpeToken(TokenType::SLASH, "/");
        break;
    case '!':
        token = makeOpeToken(TokenType::BANG, "!");
        break;
    case '=':
        token = makeOpeToken(TokenType::ASSIGN, "=");
        break;
    case '\"':
        token = makeStrToken();
        break;
    case '\n':
        token = makeOpeToken(TokenType::NEWLINE, "");
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

std::unique_ptr<Token> Lexer::getNextToken()
{
    std::unique_ptr<Token> nextToken = std::move(curToken);
    curToken = std::move(peekToken);
    peekToken = makeToken();
    return nextToken;
}

bool Lexer::hasCurTokenType(TokenType type)
{
    return curToken->isTokenType(type) ? true : false;
}

bool Lexer::hasPeekTokenType(TokenType type)
{
    return peekToken->isTokenType(type) ? true : false;
}