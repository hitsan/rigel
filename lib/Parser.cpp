#include "../include/rigel/Parser.h"
#include "../include/rigel/Lexer.h"
using namespace rigel;

// #include "llvm/Support/raw_ostream.h"
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

LetStatement* Parser::letParse()
{
    if(getPeekType() != TokenType::IDENT) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    nextToken();
    if(getPeekType() != TokenType::ASSIGN) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    Identifier ident = identParse();
    nextToken();
    nextToken();
    Expression* expression = expressionParse();
    return new LetStatement(ident, expression);
}

Identifier Parser::identParse()
{
    TOKEN_PTR tok = getCurToken();
    std::string str = tok->getLiteral();
    return Identifier(str);
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

ReturnStatement* Parser::returnParse()
{
    return new ReturnStatement(new IntLiteral(1));
}