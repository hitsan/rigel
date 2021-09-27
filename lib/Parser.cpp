#include "../include/rigel/Parser.h"
#include "../include/rigel/Lexer.h"
using namespace rigel;

#include "llvm/Support/raw_ostream.h"
Parser::Parser(Lexer &lex) : lexer(lex)
{
    this->curToken = lexer.lex();
    this->peekToken = lexer.lex();
}

void Parser::nextToken()
{
    curToken = std::move(peekToken);
    peekToken = lexer.lex();
}

IntegerLiteral Parser::parse()
{
    return IntegerLiteral("1");
}