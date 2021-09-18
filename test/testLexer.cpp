#include <gtest/gtest.h>
#include <memory>
#include "../include/rigel/Lexer.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

class TestLexer : public ::testing::Test
{
public:
    std::string expr = "1 + 2 * 3 / 4 PopVirus !true";
    std::unique_ptr<Lexer> expr_out;

    virtual void SetUp()
    {
        expr_out.reset(new Lexer(expr));
    }
};

TEST_F(TestLexer, nextToken)
{
    std::cout << "Test nextToken() " << std::endl;
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
        Token(TokenType::BOOL, "ture")
    };
    int testLength = LENGTH(test);
    for(int i = 0; i < testLength; i++)
    {
        Token tok = expr_out->nextToken();
        ASSERT_EQ(test[i].getLiteral(), tok.getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok.getTokenType());
    }
}

TEST_F(TestLexer, makeToken)
{
    std::cout << "Test makeToken() " << std::endl;
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

TEST_F(TestLexer, makeIntToken)
{
    std::cout << "Test makeIntToken() " << std::endl;
    TOKEN_PTR tok;

    Lexer mi("122");
    tok = mi.makeIntToken();
    ASSERT_EQ(TokenType::INT, tok->getTokenType());
    ASSERT_EQ("122", tok->getLiteral());

    Lexer mt("11");
    tok = mt.makeIntToken();
    ASSERT_EQ(TokenType::INT, tok->getTokenType());
    ASSERT_EQ("11", tok->getLiteral());
}

TEST_F(TestLexer, makeStrToken)
{
    std::cout << "Test makeStrToken() " << std::endl;
    TOKEN_PTR tok;

    Lexer mi("PopVirus");
    tok = mi.makeStrToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("PopVirus", tok->getLiteral());

    Lexer mt("Pops");
    tok = mt.makeStrToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("Pops", tok->getLiteral());
}

// TEST_F(TestLexer, lex)
// {
//     std::cout << "Test lex() " << std::endl;
//     Lexer mp("+");
//     auto tok = mp.lex();
//     ASSERT_EQ(TokenType::PLUS, tok.getLiteral());
//     ASSERT_EQ("+", tok.getTokenType());

//     Lexer mn("  -");
//     tok = mn.lex();
//     ASSERT_EQ(TokenType::MINUS, tok.getLiteral());
//     ASSERT_EQ("-", tok.getTokenType());

//     Lexer mnum(" 123");
//     tok = mnum.lex();
//     ASSERT_EQ(TokenType::INT, tok.getLiteral());
//     ASSERT_EQ("123", tok.getTokenType());

//     Lexer mstr(" pop virius");
//     tok = mstr.lex();
//     ASSERT_EQ(TokenType::STR, tok.getLiteral());
//     ASSERT_EQ("pop", tok.getTokenType());
// }