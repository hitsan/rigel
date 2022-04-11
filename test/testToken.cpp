#include <gtest/gtest.h>
#include "include/rigel/Token/Token.h"
using namespace rigel;

TEST(make_token, check_input_output){
    std::vector<Token> data;
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

    ASSERT_EQ(TokenType::INT, data[0].getTokenType());
    ASSERT_EQ("0", data[0].getLiteral());
    ASSERT_EQ(TokenType::STR, data[1].getTokenType());
    ASSERT_EQ("\"string\"", data[1].getLiteral());
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
    ASSERT_EQ(TokenType::IDENT, data[10].getTokenType());
    ASSERT_EQ("x", data[10].getLiteral());
    ASSERT_EQ(TokenType::IDENT, data[11].getTokenType());
    ASSERT_EQ("value", data[11].getLiteral());
}

TEST(number, Integer){
    std::vector<Number> data;
    data.push_back(Number(NumType::NUM_INT, 0));
    data.push_back(Number(NumType::NUM_INT, 1));
    data.push_back(Number(NumType::NUM_INT, 11));

    ASSERT_EQ(NumType::NUM_INT, data[0].getTokenType());
    ASSERT_EQ(0, data[0].getLiteral());
    ASSERT_EQ(NumType::NUM_INT, data[1].getTokenType());
    ASSERT_EQ(1, data[1].getLiteral());
    ASSERT_EQ(NumType::NUM_INT, data[2].getTokenType());
    ASSERT_EQ(11, data[2].getLiteral());
}

TEST(operator, expression){
    std::vector<Operator> data;
    data.push_back(Operator(OpType::OP_PLUS));
    data.push_back(Operator(OpType::OP_MINUS));
    data.push_back(Operator(OpType::OP_MUL));
    data.push_back(Operator(OpType::OP_SLASH));
    data.push_back(Operator(OpType::OP_BANG));

    ASSERT_EQ(OpType::OP_PLUS, data[0].getTokenType());
    ASSERT_EQ(OpType::OP_MINUS, data[1].getTokenType());
    ASSERT_EQ(OpType::OP_MUL, data[2].getTokenType());
    ASSERT_EQ(OpType::OP_SLASH, data[3].getTokenType());
    ASSERT_EQ(OpType::OP_BANG, data[4].getTokenType());
}

TEST(identifier, Ident){
    std::vector<Identifier> data;
    data.push_back(Identifier("x"));
    data.push_back(Identifier("i"));
    data.push_back(Identifier("value"));

    ASSERT_EQ("x", data[0].getLiteral());
    ASSERT_EQ("i", data[1].getLiteral());
    ASSERT_EQ("value", data[2].getLiteral());
}