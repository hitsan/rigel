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

IntLiteral Parser::parse()
{
    TOKEN_PTR tok = getCurToken();
    std::string strNum = tok->getLiteral();
    int num = stoi(strNum);
    return IntLiteral(num);
}

StrLiteral Parser::strParse()
{
    TOKEN_PTR tok = getCurToken();
    std::string str = tok->getLiteral();
    return StrLiteral(str);
}

LetStatement Parser::letParse()
{
    if(getPeekType() != TokenType::IDENT) {
        Identifier ident("");
        return LetStatement(ident, 0);
    }
    nextToken();
    if(getPeekType() != TokenType::ASSIGN) {
        Identifier ident("");
        return LetStatement(ident, 0);
    }
    Identifier ident = identParse();
    nextToken();
    nextToken();
    IntLiteral integer = parse();
    return LetStatement(ident, integer);
}

Identifier Parser::identParse()
{
    TOKEN_PTR tok = getCurToken();
    std::string str = tok->getLiteral();
    return Identifier(str);
}

PlusExpression Parser::plusParse()
{
    IntLiteral lHand = parse();
    nextToken();
    nextToken();
    IntLiteral rHand = parse();
    return PlusExpression(NodeType::NT_PLUS, lHand, rHand);
}