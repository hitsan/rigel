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

IntLiteral* Parser::parse()
{
    TOKEN_PTR tok = getCurToken();
    std::string strNum = tok->getLiteral();
    int num = stoi(strNum);
    return new IntLiteral(num);
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
    IntLiteral* integer = parse();
    return LetStatement(ident, integer);
}

Identifier Parser::identParse()
{
    TOKEN_PTR tok = getCurToken();
    std::string str = tok->getLiteral();
    return Identifier(str);
}

BinaryExpression* Parser::plusParse()
{
    TOKEN_PTR rtok = getCurToken();
    std::string lNum = rtok->getLiteral();
    int lhand = stoi(lNum);
    IntLiteral* lHand = new IntLiteral(lhand);

    nextToken();
    nextToken();

    TOKEN_PTR ltok = getCurToken();
    std::string rNum = ltok->getLiteral();
    int rhand = stoi(rNum);
    IntLiteral* rHand = new IntLiteral(rhand);
    return new BinaryExpression(NodeType::NT_PLUS, lHand, rHand);
}

BinaryExpression* Parser::mulParse()
{
    TOKEN_PTR rtok = getCurToken();
    std::string lNum = rtok->getLiteral();
    int lhand = stoi(lNum);
    IntLiteral* lHand = new IntLiteral(lhand);

    nextToken();
    nextToken();

    TOKEN_PTR ltok = getCurToken();
    std::string rNum = ltok->getLiteral();
    int rhand = stoi(rNum);
    IntLiteral* rHand = new IntLiteral(rhand);
    return new BinaryExpression(NodeType::NT_MUL, lHand, rHand);
}

Expression* Parser::expressionParse()
{
    IntLiteral* one = new IntLiteral(1);
    IntLiteral* two = new IntLiteral(2);
    IntLiteral* three = new IntLiteral(3);
    BinaryExpression* mul = new BinaryExpression(NodeType::NT_MUL, two, three);
    Expression* plus = new BinaryExpression(NodeType::NT_PLUS, one, mul);
    return plus;
}