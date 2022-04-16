#include <gtest/gtest.h>
#include <memory>
#include "include/rigel/Lexer.h"
using namespace rigel;

class CanLexInt : public ::testing::Test
{
protected:
    llvm::StringRef expr = "let test = 1 + 2 * 3 / 4 \n return 0";
    Lexer lexer = Lexer(expr);
    TokenType tests[14] = {
        TokenType::LET,
        TokenType::IDENT,
        TokenType::ASSIGN,
        TokenType::INT,
        TokenType::PLUS,
        TokenType::INT,
        TokenType::ASTERISK,
        TokenType::INT,
        TokenType::SLASH,
        TokenType::INT,
        TokenType::NEWLINE,
        TokenType::RETURN,
        TokenType::INT,
        TokenType::EOI
    };
};

TEST_F(CanLexInt, getNextToken)
{
    for(TokenType& test : tests) {
        bool ret = lexer.getNextToken()->isTokenType(test);
        ASSERT_TRUE(ret);
    }
}

TEST_F(CanLexInt, curTokenType)
{
    for(TokenType& test : tests) {
        ASSERT_TRUE(lexer.hasCurTokenType(test));
        lexer.getNextToken();
    }
}

TEST_F(CanLexInt, peekTokenType)
{
    for(int i=1; i < 14; i++) {
        ASSERT_TRUE(lexer.hasPeekTokenType(tests[i]));
        lexer.getNextToken();
    }
}

TEST(CanLexString, curTokenType)
{
    llvm::StringRef expr = R"(let test = "1 " + "" + "Pop"  +  "Virus")";
    Lexer lexer = Lexer(expr);
    TokenType tests[] = {
        TokenType::LET,
        TokenType::IDENT,
        TokenType::ASSIGN,
        TokenType::STR,
        TokenType::PLUS,
        TokenType::STR,
        TokenType::PLUS,
        TokenType::STR,
        TokenType::PLUS,
        TokenType::STR
    };

    for(TokenType& test : tests) {
        ASSERT_TRUE(lexer.hasCurTokenType(test));
        lexer.getNextToken();
    }
}

TEST(CanDetectIlligal,curTokenType)
{
    llvm::StringRef expr = R"(let test = "1  +  "Virus")";
    Lexer lexer = Lexer(expr);
    TokenType tests[] = {
        TokenType::LET,
        TokenType::IDENT,
        TokenType::ASSIGN,
        TokenType::STR,
        TokenType::IDENT,
        TokenType::ILLEGAL
    };

    for(TokenType& test : tests) {
        ASSERT_TRUE(lexer.hasCurTokenType(test));
        lexer.getNextToken();
    }
}

TEST(PeekToken,lex)
{
    llvm::StringRef expr = R"(let test = "1  +  "Virus")";
    Lexer lexer = Lexer(expr);
    TokenType tests[] = {
        TokenType::IDENT,
        TokenType::ASSIGN,
        TokenType::STR,
        TokenType::IDENT,
        TokenType::ILLEGAL
    };

    for(TokenType &test : tests) {
        ASSERT_TRUE(lexer.hasPeekTokenType(test));
        lexer.getNextToken();
    }
}