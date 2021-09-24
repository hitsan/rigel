#include "../include/rigel/Parser.h"
#include "../include/rigel/Lexer.h"
using namespace rigel;

Parser::Parser(Lexer& lexer)
{
    this->curToken = lexer.lex();
    this->peekToken = lexer.lex();
}

TOKEN_PTR Parser::nextToken()
{
    return TOKEN_PTR(new Token(TokenType::INT, "literal"));
}