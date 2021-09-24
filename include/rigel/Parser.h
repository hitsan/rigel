#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Lexer.h"
using namespace rigel;

class Parser
{
private:
    TOKEN_PTR curToken;
    TOKEN_PTR peekToken;
public:
    Parser(Lexer& lexer);
    TOKEN_PTR nextToken();
};

#endif