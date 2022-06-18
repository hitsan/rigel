#ifndef PARSER_H
#define PARSER_H
#include "Token/Token.h"
#include "Lexer.h"
#include "Ast.h"
namespace rigel {

class Parser
{
private:
    Lexer& lexer;
    std::unique_ptr<Token> curToken;
    std::unique_ptr<Token> peekToken;

    std::unique_ptr<IntLiteral> parseInt();
    // StrLiteral parseStr();
    // LetStatement* parseLet();
    std::unique_ptr<ReturnStatement> parseReturn();
    Identifier parseIdentifier();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Token> getNextToken();
    void consumeToken();
    // std::unique_ptr<BinaryExpression> makeBinaryExpression(NodeType type, )
public:
    Parser(Lexer &lex);
    std::unique_ptr<Statement> parse();
};
};
#endif