#ifndef PARSER_H
#define PARSER_H
#include "Token/Token.h"
#include "Lexer.h"
#include "Ast.h"
namespace rigel {

class Parser
{
private:
    TOKEN_PTR curToken;
    TOKEN_PTR peekToken;
    Lexer& lexer;
public:
    Parser(Lexer &lex);
    IntLiteral* parseInt();
    StrLiteral parseStr();
    LetStatement* parseLet();
    ReturnStatement* parseReturn();
    Identifier parseIdentifier();
    Expression* parseExpression();
};
};
#endif