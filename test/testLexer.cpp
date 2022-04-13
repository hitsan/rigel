#include <gtest/gtest.h>
#include <memory>
#include "include/rigel/Lexer.h"
using namespace rigel;

TEST(TestIntLexer, lex)
{
    // preparation data
    llvm::StringRef expr = "let test = 1 + 2 * 3 / 4 \n return 0";
    Lexer lx = Lexer(expr);
    Token tests[] = {
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
        Token(TokenType::NEWLINE, ""),
        Token(TokenType::RETURN, "return"),
        Token(TokenType::INT, "0"),
        Token(TokenType::EOI, ""),
    };

    lx.init();
    for(Token& test : tests) {
        std::unique_ptr<Token> tok = lx.getNextToken();
        ASSERT_EQ(test.getLiteral(), tok->getLiteral());
        ASSERT_EQ(test.getTokenType(), tok->getTokenType());
    }
}

TEST(TestStringLexer, lex)
{
    llvm::StringRef expr = R"(let test = "1 " + "" + "Pop"  +  "Virus")";
    Lexer lx = Lexer(expr);
    Token tests[] = {
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

    lx.init();
    for(Token& test : tests) {
        std::unique_ptr<Token> tok = lx.getNextToken();
        ASSERT_EQ(test.getLiteral(), tok->getLiteral());
        ASSERT_EQ(test.getTokenType(), tok->getTokenType());
    }
}

TEST(testLexer, peekChar)
{
    Lexer mi("PopVirus");
    auto c = mi.peekChar();
    ASSERT_EQ('o', c);
}

TEST(Illigal_String,lex)
{
    llvm::StringRef expr = R"(let test = "1  +  "Virus")";
    Lexer lx = Lexer(expr);
    Token tests[] = {
        Token(TokenType::LET, "let"),
        Token(TokenType::IDENT, "test"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::STR, "1  +  "),
        Token(TokenType::IDENT, "Virus"),
        Token(TokenType::ILLEGAL,""),
    };

    lx.init();
    for(Token& test : tests) {
        std::unique_ptr<Token> tok = lx.getNextToken();
        ASSERT_EQ(test.getLiteral(), tok->getLiteral());
        ASSERT_EQ(test.getTokenType(), tok->getTokenType());
    }
}