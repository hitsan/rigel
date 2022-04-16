#include "include/rigel/Parser.h"
#include "include/rigel/Lexer.h"
using namespace rigel;

Parser::Parser(Lexer &lexer) : lexer(lexer)
{
    curToken = lexer.makeToken();
    peekToken = lexer.makeToken();
}

std::unique_ptr<Token> Parser::getNextToken()
{
    std::unique_ptr<Token> nextToken = std::move(curToken);
    curToken = std::move(peekToken);
    peekToken = lexer.makeToken();
    return nextToken;
}

IntLiteral* Parser::parseInt()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string strNum = token->getLiteral();
    int num = stoi(strNum);
    return new IntLiteral(num);
}

StrLiteral Parser::parseStr()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string str = token->getLiteral();
    return StrLiteral(str);
}

LetStatement* Parser::parseLet()
{
    if(!peekToken->isTokenType(TokenType::IDENT)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    getNextToken();
    if(!peekToken->isTokenType(TokenType::ASSIGN)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    Identifier ident = parseIdentifier();
    getNextToken();
    Expression* expression = parseExpression();
    return new LetStatement(ident, expression);
}

Identifier Parser::parseIdentifier()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string str = token->getLiteral();
    return Identifier(str);
}

Expression* Parser::parseExpression()
{
    if(peekToken->isTokenType(TokenType::EOI)) {
        std::unique_ptr<Token> token = getNextToken();
        std::string stringNum = token->getLiteral();
        return new IntLiteral(stoi(stringNum));
    }
    Expression* lHand;
    if(curToken->isTokenType(TokenType::INT)) {
        std::unique_ptr<Token> token = getNextToken();
        std::string strNum = token->getLiteral();
        lHand = new IntLiteral(stoi(strNum));
    }

    while(!curToken->isTokenType(TokenType::EOI)) {
        if(curToken->isTokenType(TokenType::PLUS)) {
            getNextToken();
            Expression* rHand = parseExpression();
            lHand = new BinaryExpression(OpType::OP_PLUS, lHand, rHand);
        } else if(curToken->isTokenType(TokenType::ASTERISK)) {
            getNextToken();
            std::unique_ptr<Token> token = getNextToken();
            std::string stringNum = token->getLiteral();
            Expression* rHand = new IntLiteral(stoi(stringNum));
            lHand = new BinaryExpression(OpType::OP_MUL, lHand, rHand);
        }
    }

    return lHand;
}

ReturnStatement* Parser::parseReturn()
{
    getNextToken();
    Expression* expression = parseExpression();
    return new ReturnStatement(expression);
}