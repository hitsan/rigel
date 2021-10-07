#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
#include "../include/rigel/Ast.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define LEN_NUM_ARR 11
#define LEN_STR_ARR 11
using namespace rigel;

class TestGetToken : public ::testing::Test
{
protected:
    llvm::StringRef st = "let test = 1 + 2 * 3 / 4";
    Lexer lx = Lexer(st);
    Parser* ps;
    Token test[LEN_NUM_ARR] = {
        Token(TokenType::LET, "let"),
        Token(TokenType::IDENT, "test"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::INT, "1"),
        Token(TokenType::PLUS, "+"),
        Token(TokenType::INT, "2"),
        Token(TokenType::ASTERISK, "*"),
        Token(TokenType::INT, "3"),
        Token(TokenType::SLASH, "/"),
        Token(TokenType::INT, "4"),
        Token(TokenType::EOI, ""),
    };

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
    TOKEN_PTR tok;
    for(int i = 0; i < LEN_NUM_ARR-1; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetToken, getPeekToken)
{
    TOKEN_PTR tok;
    for(int i = 1; i < LEN_NUM_ARR; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

class TestGetStrToken : public ::testing::Test
{
protected:
    llvm::StringRef st = R"(let test = "1 " + "" + "Pop"  +  "Virus")";
    Lexer lx = Lexer(st);
    Parser* ps;
    Token test[LEN_STR_ARR] = {
        Token(TokenType::LET, "let"),
        Token(TokenType::IDENT, "test"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::STR, "1 "),
        Token(TokenType::PLUS, "+"),
        Token(TokenType::STR, ""),
        Token(TokenType::PLUS, "+"),
        Token(TokenType::STR, "Pop"),
        Token(TokenType::PLUS, "+"),
        Token(TokenType::STR, "Virus"),
        Token(TokenType::EOI, ""),
    };

    virtual void SetUp()
    {
        ps = new Parser(lx);
    }

    virtual void TearDown()
    {
        delete ps;
    }
};

TEST_F(TestGetStrToken, getCurToken)
{
    TOKEN_PTR tok;
    for(int i = 0; i < LEN_STR_ARR-1; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetStrToken, getPeekToken)
{
    TOKEN_PTR tok;
    for(int i = 1; i < LEN_STR_ARR; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}