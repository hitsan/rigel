#include <memory>
#include "llvm/Support/raw_ostream.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Token/Declarator.h"
using namespace rigel;

Lexer::Lexer(const llvm::StringRef &code)
{
    bufferStart = code.begin();
    bufferPtr = bufferStart;
    // curToken = lex();
    // peekToken = lex();
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


TOKEN_PTR Lexer::makeIntToken()
{
    const char *end = bufferPtr + 1;
    while(isdigit(*end)) { end++; }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    bufferPtr = end;
    return TOKEN_PTR(new Token(TokenType::INT, literal));
}

TOKEN_PTR Lexer::makeStrToken()
{
    const char *end = bufferPtr + 1;
    while((*end) != '"') {
        if(peekChar() == '\0') {
            return TOKEN_PTR(new Token(TokenType::ILLEGAL, ""));
        }
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr + 1, end - bufferPtr - 1);
    bufferPtr = end + 1;
    return TOKEN_PTR(new Token(TokenType::STR, literal));
}

TOKEN_PTR Lexer::makeKeyToken()
{
    const char *end = bufferPtr + 1;
    while(isalpha(*end))
    {
        end++;
    }
    auto literal = llvm::StringRef(bufferPtr, end - bufferPtr);
    auto type = findTokenType(literal);
    bufferPtr = end;
    return TOKEN_PTR(new Token(type, literal));
}

TOKEN_PTR Lexer::makeToken(TokenType type, const llvm::StringRef &literal)
{
    bufferPtr++;
    return TOKEN_PTR(new Token(type, literal));
}

TOKEN_PTR Lexer::lex()
{
    if(!(*bufferPtr))
    {
        return makeToken(TokenType::EOI, "");
    }

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
    case '=':
        token = makeToken(TokenType::ASSIGN, "=");
        break;
    case '\"':
        token = makeStrToken();
        break;
    case '\n':
        token = makeToken(TokenType::NEWLINE, "");
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

void Lexer::init()
{
    curToken = lex();
    peekToken = lex();
}

std::unique_ptr<Token> Lexer::getNextToken()
{
    std::unique_ptr<Token> nextToken = std::move(curToken);
    curToken = std::move(peekToken);
    peekToken = lex();
    return std::move(nextToken);
}
