#include <gtest/gtest.h>
#include "../include/rigel/Token.h"
using namespace rigel;

TEST(make_token, check_input_output){
    std::vector<Token> data;
    // make Token
    data.push_back(Token(TokenType::INT, "0"));
    data.push_back(Token(TokenType::STR, "string"));
    data.push_back(Token(TokenType::PLUS, "+"));
    data.push_back(Token(TokenType::MINUS, "-"));
    data.push_back(Token(TokenType::ASTERISK, "*"));
    data.push_back(Token(TokenType::SLASH, "/"));
    data.push_back(Token(TokenType::BANG, "!"));
    data.push_back(Token(TokenType::EOI, ""));
    data.push_back(Token(TokenType::LET, "let"));
    data.push_back(Token(TokenType::ASSIGN, "="));

    // Test
    ASSERT_EQ(TokenType::INT, data[0].getTokenType());
    ASSERT_EQ("0", data[0].getLiteral());
    ASSERT_EQ(TokenType::STR, data[1].getTokenType());
    ASSERT_EQ("string", data[1].getLiteral());
    ASSERT_EQ(TokenType::PLUS, data[2].getTokenType());
    ASSERT_EQ("+", data[2].getLiteral());
    ASSERT_EQ(TokenType::MINUS, data[3].getTokenType());
    ASSERT_EQ("-", data[3].getLiteral());
    ASSERT_EQ(TokenType::ASTERISK, data[4].getTokenType());
    ASSERT_EQ("*", data[4].getLiteral());
    ASSERT_EQ(TokenType::SLASH, data[5].getTokenType());
    ASSERT_EQ("/", data[5].getLiteral());
    ASSERT_EQ(TokenType::BANG, data[6].getTokenType());
    ASSERT_EQ("!", data[6].getLiteral());
    ASSERT_EQ(TokenType::EOI, data[7].getTokenType());
    ASSERT_EQ(TokenType::LET, data[8].getTokenType());
    ASSERT_EQ("let", data[8].getLiteral());
    ASSERT_EQ(TokenType::ASSIGN, data[9].getTokenType());
    ASSERT_EQ("=", data[9].getLiteral());
}