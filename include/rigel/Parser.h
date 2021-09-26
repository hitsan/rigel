#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Lexer.h"
namespace rigel {

class Parser
{
private:
    TOKEN_PTR curToken;
    TOKEN_PTR peekToken;
    Lexer& lexer;
public:
    Parser(Lexer &lex);
    void nextToken();
    TOKEN_PTR getCurToken() { return std::move(curToken); }
    TOKEN_PTR getPeekToken() { return std::move(peekToken); }
};
};
#endif