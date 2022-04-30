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
    if(!peekToken->equalsTokenType(TokenType::IDENT)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    getNextToken();
    if(!peekToken->equalsTokenType(TokenType::ASSIGN)) {
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
    if(peekToken->equalsTokenType(TokenType::EOI)) {
        std::unique_ptr<Token> token = getNextToken();
        std::string stringNum = token->getLiteral();
        return new IntLiteral(stoi(stringNum));
    }
    Expression* lHand;
    if(curToken->equalsTokenType(TokenType::INT)) {
        std::unique_ptr<Token> token = getNextToken();
        std::string strNum = token->getLiteral();
        lHand = new IntLiteral(stoi(strNum));
    }

    while(!curToken->equalsTokenType(TokenType::EOI)) {
        if(curToken->equalsTokenType(TokenType::PLUS)) {
            getNextToken();
            Expression* rHand = parseExpression();
            lHand = new BinaryExpression(OpType::OP_PLUS, lHand, rHand);
        } else if(curToken->equalsTokenType(TokenType::ASTERISK)) {
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

Statement* Parser::parse()
{
    std::unique_ptr<Token> token = getNextToken();
    // if(token->equalsTokenType(TokenType::RETURN))
    // {
    //     return parseReturn();
    // }
    // return nullptr;
    IntLiteral* num = parseInt();
    return new ReturnStatement(num);
}