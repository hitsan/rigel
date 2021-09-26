#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Lexer.h"
#define LEXER_PTR std::unique_ptr<Lexer>
namespace rigel {

class Parser
{
private:
    TOKEN_PTR curToken;
    TOKEN_PTR peekToken;
    LEXER_PTR lexer;
public:
    Parser(LEXER_PTR lex);
    void nextToken();
    TOKEN_PTR getCurToken() { return std::move(curToken); }
    TOKEN_PTR getPeekToken() { return std::move(peekToken); }
};
};
#endif