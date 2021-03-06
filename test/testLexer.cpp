#include <gtest/gtest.h>
#include <memory>
#include "include/rigel/Lexer.h"
using namespace rigel;

TEST(CanLexInt, getNextToken)
{
    llvm::StringRef expr = "let test = 1 + 2 * 3 / 4 \n return 0";
    Lexer lexer = Lexer(expr);
    TokenType tests[] = {
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

    for(TokenType& test : tests) {
        bool ret = lexer.fetchToken()->equalsTokenType(test);
        ASSERT_TRUE(ret);
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
        bool ret = lexer.fetchToken()->equalsTokenType(test);
        ASSERT_TRUE(ret);
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
        bool ret = lexer.fetchToken()->equalsTokenType(test);
        ASSERT_TRUE(ret);
    }
}