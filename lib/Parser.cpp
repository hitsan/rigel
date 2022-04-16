#include "include/rigel/Parser.h"
#include "include/rigel/Lexer.h"
using namespace rigel;

Parser::Parser(Lexer &lex) : lexer(lex) {}

IntLiteral* Parser::parseInt()
{
    std::unique_ptr<Token> token = lexer.getNextToken();
    std::string strNum = token->getLiteral();
    int num = stoi(strNum);
    return new IntLiteral(num);
}

StrLiteral Parser::parseStr()
{
    std::unique_ptr<Token> token = lexer.getNextToken();
    std::string str = token->getLiteral();
    return StrLiteral(str);
}

LetStatement* Parser::parseLet()
{
    if(!lexer.hasPeekTokenType(TokenType::IDENT)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    lexer.getNextToken();
    if(!lexer.hasPeekTokenType(TokenType::ASSIGN)) {
        Identifier ident("");
        Expression* exp = new StrLiteral("");
        return new LetStatement(ident, exp);
    }
    Identifier ident = parseIdentifier();
    lexer.getNextToken();
    Expression* expression = parseExpression();
    return new LetStatement(ident, expression);
}

Identifier Parser::parseIdentifier()
{
    std::unique_ptr<Token> token = lexer.getNextToken();
    std::string str = token->getLiteral();
    return Identifier(str);
}

Expression* Parser::parseExpression()
{
    if(lexer.hasPeekTokenType(TokenType::EOI)) {
        std::unique_ptr<Token> token = lexer.getNextToken();
        std::string stringNum = token->getLiteral();
        return new IntLiteral(stoi(stringNum));
    }
    Expression* lHand;
    if(lexer.hasCurTokenType(TokenType::INT)) {
        std::unique_ptr<Token> token = lexer.getNextToken();
        std::string strNum = token->getLiteral();
        lHand = new IntLiteral(stoi(strNum));
    }

    while(!lexer.hasCurTokenType(TokenType::EOI)) {
        if(lexer.hasCurTokenType(TokenType::PLUS)) {
            lexer.getNextToken();
            Expression* rHand = parseExpression();
            lHand = new BinaryExpression(OpType::OP_PLUS, lHand, rHand);
        } else if(lexer.hasCurTokenType(TokenType::ASTERISK)) {
            lexer.getNextToken();
            std::unique_ptr<Token> token = lexer.getNextToken();
            std::string stringNum = token->getLiteral();
            Expression* rHand = new IntLiteral(stoi(stringNum));
            lHand = new BinaryExpression(OpType::OP_MUL, lHand, rHand);
        }
    }

    return lHand;
}

ReturnStatement* Parser::parseReturn()
{
    lexer.getNextToken();
    Expression* expression = parseExpression();
    return new ReturnStatement(expression);
}