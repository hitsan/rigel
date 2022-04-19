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

std::unique_ptr<Token> Lexer::makeToken(TokenType type, llvm::StringRef literal)
{
    return std::unique_ptr<Token>(new Token(type, literal));
}

std::unique_ptr<Token> Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end)) { end++; }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    bufferPtr = end;
    return makeToken(TokenType::INT, literal);
}

std::unique_ptr<Token> Lexer::makeStrToken()
{
    const char *end = bufferPtr + 1;
    while((*end) != '"') {
        if(peekChar() == '\0') {
            return makeToken(TokenType::ILLEGAL, "");
        }
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr + 1, end - bufferPtr - 1);
    bufferPtr = end + 1;
    return makeToken(TokenType::STR, literal);
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
    return makeToken(type, literal);
}

std::unique_ptr<Token> Lexer::makeOpeToken()
{
    llvm::StringRef ope = llvm::StringRef(bufferPtr, 1);
    TokenType optype =  findOperatorType(ope);
    bufferPtr++;
    return makeToken(optype, ope);
}

std::unique_ptr<Token> Lexer::fetchToken()
{
    if(!(*bufferPtr))
    {
        return makeToken(TokenType::EOI, "");
    }

    std::unique_ptr<Token> token;
    skipSpace();

    switch (*bufferPtr)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
    case '=':
    case '\n':
        token = makeOpeToken();
        break;
    case '\"':
        token = makeStrToken();
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