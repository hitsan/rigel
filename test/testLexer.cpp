#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

class TestLexer : public ::testing::Test
{
public:
    std::string expr = "1 + 2 * 3 / 4 PopVirus !true";
    Lexer* expr_out;

    virtual void SetUp()
    {
        std::cout << "TestLexer SetUp" << std::endl;
        expr_out = new Lexer(expr);
    }
};

TEST_F(TestLexer, token){
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