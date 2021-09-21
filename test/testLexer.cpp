#include <gtest/gtest.h>
#include <memory>
#include "../include/rigel/Lexer.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

class TestLexer : public ::testing::Test
{
public:
    std::string expr = "1 + 2 * 3 / 4 PopVirus !";
    std::unique_ptr<Lexer> expr_out;

    virtual void SetUp()
    {
        expr_out.reset(new Lexer(expr));
    }
};

TEST_F(TestLexer, lex)
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
        Token(TokenType::BANG, "!"),
    };

    int testLength = LENGTH(test);
    for(int i = 0; i < testLength; i++)
    {
        TOKEN_PTR tok = expr_out->lex();
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
    }
}

TEST(testLexer, makeToken)
{
    Lexer mt("");
    TOKEN_PTR tok;

    tok = mt.makeToken(TokenType::PLUS, "+");
    ASSERT_EQ(TokenType::PLUS, tok->getTokenType());
    ASSERT_EQ("+", tok->getLiteral());

    tok = mt.makeToken(TokenType::MINUS, "-");
    ASSERT_EQ(TokenType::MINUS, tok->getTokenType());
    ASSERT_EQ("-", tok->getLiteral());

    tok = mt.makeToken(TokenType::ASTERISK, "*");
    ASSERT_EQ(TokenType::ASTERISK, tok->getTokenType());
    ASSERT_EQ("*", tok->getLiteral());

    tok = mt.makeToken(TokenType::SLASH, "/");
    ASSERT_EQ(TokenType::SLASH, tok->getTokenType());
    ASSERT_EQ("/", tok->getLiteral());

    tok = mt.makeToken(TokenType::BANG, "!");
    ASSERT_EQ(TokenType::BANG, tok->getTokenType());
    ASSERT_EQ("!", tok->getLiteral());
}

TEST(testLexer, makeIntToken)
{
    TOKEN_PTR tok;

    Lexer mi("122");
    tok = mi.makeIntToken();
    ASSERT_EQ(TokenType::INT, tok->getTokenType());
    ASSERT_EQ("122", tok->getLiteral());

    Lexer mt("11");
    tok = mt.makeIntToken();
    ASSERT_EQ(TokenType::INT, tok->getTokenType());
    ASSERT_EQ("11", tok->getLiteral());

    Lexer mk("44 22");
    tok = mk.makeIntToken();
    ASSERT_EQ(TokenType::INT, tok->getTokenType());
    ASSERT_EQ("44", tok->getLiteral());
}

TEST(testLexer, makeStrToken)
{
    TOKEN_PTR tok;

    Lexer mi("PopVirus");
    tok = mi.makeStrToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("PopVirus", tok->getLiteral());

    Lexer mt("Pops");
    tok = mt.makeStrToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("Pops", tok->getLiteral());

    Lexer ms("p ops");
    tok = ms.makeStrToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("p", tok->getLiteral());
}

TEST(testLexer, peekChar)
{
    Lexer mi("PopVirus");
    auto c = mi.peekChar();
    ASSERT_EQ('o', c);
}