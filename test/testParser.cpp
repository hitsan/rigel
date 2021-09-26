#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

class TestGetToken : public ::testing::Test
{
protected:
    llvm::StringRef st = "1 + 2 * 3 / 4 PopVirus !";
    Lexer lx = Lexer(st);
    Parser* ps;

    virtual void SetUp()
    {
        ps = new Parser(lx);
    }

    virtual void TearDown()
    {
        delete ps;
    }
};

TEST_F(TestGetToken, getCurToken)
{
    Token test[] = {
    Token(TokenType::INT, "1"),
    Token(TokenType::PLUS, "+"),
    Token(TokenType::INT, "2"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "3"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::INT, "4"),
    Token(TokenType::STR, "PopVirus"),
    Token(TokenType::BANG, "!")
    };

    int testLength = LENGTH(test);
    TOKEN_PTR tok;
    for(int i = 0; i < testLength; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetToken, getPeekToken)
{
    Token test[] = {
    // Token(TokenType::INT, "1"),
    Token(TokenType::PLUS, "+"),
    Token(TokenType::INT, "2"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "3"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::INT, "4"),
    Token(TokenType::STR, "PopVirus"),
    Token(TokenType::BANG, "!"),
    Token(TokenType::EOI, ""),
    };

    int testLength = LENGTH(test);
    TOKEN_PTR tok;
    for(int i = 0; i < testLength; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}