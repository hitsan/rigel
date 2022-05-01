#include <iostream>
#include "include/rigel/Parser.h"
#include "include/rigel/Lexer.h"
using namespace rigel;

Parser::Parser(Lexer &lexer) : lexer(lexer)
{
    curToken = lexer.fetchToken();
    peekToken = lexer.fetchToken();
}

std::unique_ptr<Token> Parser::getNextToken()
{
    std::unique_ptr<Token> nextToken = std::move(curToken);
    curToken = std::move(peekToken);
    peekToken = lexer.fetchToken();
    return nextToken;
}

void Parser::consumeToken()
{
    curToken = std::move(peekToken);
    peekToken = lexer.fetchToken();
}

IntLiteral* Parser::parseInt()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string strNum = token->getLiteral();
    int num = stoi(strNum);
    return new IntLiteral(num);
}

// StrLiteral Parser::parseStr()
// {
//     std::unique_ptr<Token> token = getNextToken();
//     std::string str = token->getLiteral();
//     return StrLiteral(str);
// }

LetStatement* Parser::parseLet()
{
    if(!peekToken->equalsTokenType(TokenType::IDENT)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    consumeToken();
    if(!peekToken->equalsTokenType(TokenType::ASSIGN)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    Identifier ident = parseIdentifier();
    consumeToken();
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
    if(peekToken->equalsTokenType(TokenType::EOI)) {
        std::unique_ptr<Token> token = getNextToken();
        std::string stringNum = token->getLiteral();
        return new IntLiteral(stoi(stringNum));
    }

    Expression* lHand = nullptr;
    while(!curToken->equalsTokenType(TokenType::EOI)) {
        if(curToken->equalsTokenType(TokenType::PLUS)) {
            consumeToken();
            Expression* rHand = parseExpression();
            lHand = new BinaryExpression(NodeType::PLUS, lHand, rHand);
        } else if(curToken->equalsTokenType(TokenType::ASTERISK)) {
            consumeToken();
            std::unique_ptr<Token> token = getNextToken();
            std::string stringNum = token->getLiteral();
            Expression* rHand = new IntLiteral(stoi(stringNum));
            lHand = new BinaryExpression(NodeType::MUL, lHand, rHand);
        } else if(curToken->equalsTokenType(TokenType::INT)) {
            std::unique_ptr<Token> token = getNextToken();
            std::string strNum = token->getLiteral();
            lHand = new IntLiteral(stoi(strNum));
        }
    }

    return lHand;
}

ReturnStatement* Parser::parseReturn()
{
    Expression* expression = parseExpression();
    return new ReturnStatement(expression);
}

Statement* Parser::parse()
{
    // std::unique_ptr<Token> token = getNextToken();
    TokenType type = curToken->getTokenType();
    switch (type) {
        case TokenType::RETURN:
            consumeToken();
            return parseReturn();
        default:
            return nullptr;
    }
}