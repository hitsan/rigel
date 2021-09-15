#include <gtest/gtest.h>
#include "../include/rigel/Token.h"
using namespace rigel;

class TestToken : public ::testing::Test
{
public:
    std::vector<Token> data;

    virtual void SetUp()
    {
        std::cout << "TestToken SetUp" << std::endl;
        data.push_back(Token(TokenType::INT, "0"));
        data.push_back(Token(TokenType::PLUS, "+"));
        data.push_back(Token(TokenType::MUL, "*"));
    }
};

TEST_F(TestToken, token){
    ASSERT_EQ(TokenType::INT, data[0].getTokenType());
    ASSERT_EQ("1", data[0].getLiteral());
}