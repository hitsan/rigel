#include "../include/rigel/Lexer.h"
#include "../include/rigel/Token.h"
using namespace rigel;

Lexer::Lexer(llvm::StringRef code)
{
    bufferStart = code.begin();
    bufferPtr = bufferStart;
    auto tok = Token(TokenType::FIRST, "");
    cur = &tok;
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
    cur->next = &tok;
    cur = &tok;
}

void Lexer::makeToken(TokenType type, std::string literal)
{
        auto tok = Token(type, literal);
        cur->next = &tok;
        cur = &tok;
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
            makeToken(TokenType::MUL, "*");
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