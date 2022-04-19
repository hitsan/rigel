#ifndef PARSER_H
#define PARSER_H
#include "Token/Token.h"
#include "Lexer.h"
#include "Ast.h"
namespace rigel {

class Parser
{
private:
    Lexer& lexer;
    std::unique_ptr<Token> curToken;
    std::unique_ptr<Token> peekToken;
public:
    Parser(Lexer &lex);
    IntLiteral* parseInt();
    StrLiteral parseStr();
    LetStatement* parseLet();
    ReturnStatement* parseReturn();
    Identifier parseIdentifier();
    Expression* parseExpression();
    std::unique_ptr<Token> getNextToken();
};
};
#endif