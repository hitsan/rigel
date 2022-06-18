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

std::unique_ptr<IntLiteral> Parser::parseInt()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string strNum = token->getLiteral();
    int num = stoi(strNum);
    return std::unique_ptr<IntLiteral>(new IntLiteral(num));
    // return new IntLiteral(num);
}

// StrLiteral Parser::parseStr()
// {
//     std::unique_ptr<Token> token = getNextToken();
//     std::string str = token->getLiteral();
//     return StrLiteral(str);
// }

// LetStatement* Parser::parseLet()
// {
//     if(!peekToken->equalsTokenType(TokenType::IDENT)) {
//         Identifier ident("");
//         Expression* exp = new StrLiteral("");
//         return new LetStatement(ident, exp);
//     }
//     consumeToken();
//     if(!peekToken->equalsTokenType(TokenType::ASSIGN)) {
//         Identifier ident("");
//         Expression* exp = new StrLiteral("");
//         return new LetStatement(ident, exp);
//     }
//     Identifier ident = parseIdentifier();
//     consumeToken();
//     Expression* expression = parseExpression();
//     return new LetStatement(ident, expression);
// }

Identifier Parser::parseIdentifier()
{
    std::unique_ptr<Token> token = getNextToken();
    std::string str = token->getLiteral();
    return Identifier(str);
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    if(peekToken->equalsTokenType(TokenType::EOI)){
        return parseInt();
    }

    std::unique_ptr<Expression> lHand;
    if(curToken->equalsTokenType(TokenType::INT)) {
        lHand = parseInt();
    }
    while(!curToken->equalsTokenType(TokenType::EOI)) {
        if(curToken->equalsTokenType(TokenType::PLUS)) {
            consumeToken();
            std::unique_ptr<Expression> rHand = parseExpression();
            lHand = std::unique_ptr<BinaryExpression>(new BinaryExpression(NodeType::PLUS, std::move(lHand), std::move(rHand)));
        } else if(curToken->equalsTokenType(TokenType::ASTERISK)) {
            consumeToken();
            std::unique_ptr<Expression> rHand = parseInt();
            lHand = std::unique_ptr<BinaryExpression>(new BinaryExpression(NodeType::MUL, std::move(lHand), std::move(rHand)));
        } else {
            // error
        }
    }

    return lHand;
}

std::unique_ptr<ReturnStatement> Parser::parseReturn()
{
    std::unique_ptr<Expression> expression = parseExpression();
    std::unique_ptr<ReturnStatement> statement(new ReturnStatement(std::move(expression)));
    return statement;
}

std::unique_ptr<Statement> Parser::parse()
{
    TokenType type = curToken->getTokenType();
    // std::unique_ptr<Statement> statement;
    switch (type) {
        case TokenType::RETURN:
            consumeToken();
            return parseReturn();
            // statement.reset(parseReturn());
            // return statement;
        default:
            return nullptr;
    }
}