#include <gtest/gtest.h>
#include <memory>
#include "../include/rigel/Lexer.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

TEST(TestIntLexer, lex)
{
    // preparation data
    llvm::StringRef expr = "let test = 1 + 2 * 3 / 4";
    Lexer lx = Lexer(expr);
    Token test[] = {
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

    int testLength = LENGTH(test);
    for(int i = 0; i < testLength; i++)
    {
        TOKEN_PTR tok = lx.lex();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
    }
}

TEST(TestStringLexer, lex)
{
    llvm::StringRef expr = R"(let test = "1 " + "" + "Pop"  +  "Virus")";
    Lexer lx = Lexer(expr);
    Token test[] = {
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
    };

    int testLength = LENGTH(test);
    for(int i = 0; i < testLength; i++)
    {
        TOKEN_PTR tok = lx.lex();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
    }
}

TEST(testLexer, peekChar)
{
    Lexer mi("PopVirus");
    auto c = mi.peekChar();
    ASSERT_EQ('o', c);
}