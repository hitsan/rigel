#include <gtest/gtest.h>
#include "include/rigel/Token/Token.h"
using namespace rigel;

TEST(make_token, check_input_output){
    std::vector<Token> data;
    // make Token
    data.push_back(Token(TokenType::INT, "0"));
    data.push_back(Token(TokenType::STR, "\"string\""));
    data.push_back(Token(TokenType::PLUS, "+"));
    data.push_back(Token(TokenType::MINUS, "-"));
    data.push_back(Token(TokenType::ASTERISK, "*"));
    data.push_back(Token(TokenType::SLASH, "/"));
    data.push_back(Token(TokenType::BANG, "!"));
    data.push_back(Token(TokenType::EOI, ""));
    data.push_back(Token(TokenType::LET, "let"));
    data.push_back(Token(TokenType::ASSIGN, "="));
    data.push_back(Token(TokenType::IDENT, "x"));
    data.push_back(Token(TokenType::IDENT, "value"));

    // Test
    ASSERT_TRUE(data[0].equalsTokenType(TokenType::INT));
    ASSERT_EQ("0", data[0].getLiteral());
    ASSERT_TRUE(data[1].equalsTokenType(TokenType::STR));
    ASSERT_EQ("\"string\"", data[1].getLiteral());
    ASSERT_TRUE(data[2].equalsTokenType(TokenType::PLUS));
    ASSERT_EQ("+", data[2].getLiteral());
    ASSERT_TRUE(data[3].equalsTokenType(TokenType::MINUS));
    ASSERT_EQ("-", data[3].getLiteral());
    ASSERT_TRUE(data[4].equalsTokenType(TokenType::ASTERISK));
    ASSERT_EQ("*", data[4].getLiteral());
    ASSERT_TRUE(data[5].equalsTokenType(TokenType::SLASH));
    ASSERT_EQ("/", data[5].getLiteral());
    ASSERT_TRUE(data[6].equalsTokenType(TokenType::BANG));
    ASSERT_EQ("!", data[6].getLiteral());
    ASSERT_TRUE(data[7].equalsTokenType(TokenType::EOI));
    ASSERT_TRUE(data[8].equalsTokenType(TokenType::LET));
    ASSERT_EQ("let", data[8].getLiteral());
    ASSERT_TRUE(data[9].equalsTokenType(TokenType::ASSIGN));
    ASSERT_EQ("=", data[9].getLiteral());
    ASSERT_TRUE(data[10].equalsTokenType(TokenType::IDENT));
    ASSERT_EQ("x", data[10].getLiteral());
    ASSERT_TRUE(data[11].equalsTokenType(TokenType::IDENT));
    ASSERT_EQ("value", data[11].getLiteral());
}