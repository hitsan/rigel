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
    if(getPeekType() == TokenType::EOI){
        TOKEN_PTR token = getCurToken();
        std::string stringNum = token->getLiteral();
        return new IntLiteral(stoi(stringNum));
    }
    TOKEN_PTR tok = getCurToken();
    std::string strNum = tok->getLiteral();
    Expression* lHand = new IntLiteral(stoi(strNum));
    Expression* rHand;

    while(getPeekType() != TokenType::EOI) {
        if(getPeekType() == TokenType::PLUS) {
            nextToken();
            nextToken();
            rHand = expressionParse();
            lHand = new BinaryExpression(NodeType::NT_PLUS, lHand, rHand);
        } else if(getPeekType() == TokenType::ASTERISK) {
            nextToken();
            nextToken();
            TOKEN_PTR token = getCurToken();
            std::string stringNum = token->getLiteral();
            rHand = new IntLiteral(stoi(stringNum));
            lHand = new BinaryExpression(NodeType::NT_MUL, lHand, rHand);
        }
    }

    return lHand;
}