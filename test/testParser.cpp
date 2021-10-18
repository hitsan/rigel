#include <typeinfo>
#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
#include "../include/rigel/Ast.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define LEN_NUM_ARR 11
#define LEN_STR_ARR 11
using namespace rigel;

class TestGetToken : public ::testing::Test
{
protected:
    llvm::StringRef st = "let test = 1 + 2 * 3 / 4";
    Lexer lx = Lexer(st);
    Parser* ps;
    Token test[LEN_NUM_ARR] = {
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

    virtual void SetUp()
    {
        ps = new Parser(lx);
    }

    virtual void TearDown()
    {
        delete ps;
    }
};

TEST_F(TestGetToken, getCurToken)
{
    TOKEN_PTR tok;
    for(int i = 0; i < LEN_NUM_ARR-1; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetToken, getPeekToken)
{
    TOKEN_PTR tok;
    for(int i = 1; i < LEN_NUM_ARR; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

class TestGetStrToken : public ::testing::Test
{
protected:
    llvm::StringRef st = R"(let test = "1 " + "" + "Pop"  +  "Virus")";
    Lexer lx = Lexer(st);
    Parser* ps;
    Token test[LEN_STR_ARR] = {
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
        Token(TokenType::EOI, ""),
    };

    virtual void SetUp()
    {
        ps = new Parser(lx);
    }

    virtual void TearDown()
    {
        delete ps;
    }
};

TEST_F(TestGetStrToken, getCurToken)
{
    TOKEN_PTR tok;
    for(int i = 0; i < LEN_STR_ARR-1; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetStrToken, getPeekToken)
{
    TOKEN_PTR tok;
    for(int i = 1; i < LEN_STR_ARR; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST(TestParseToken, singleIntNum)
{
    llvm::StringRef st = R"(1)";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    IntLiteral test = IntLiteral(1);

    auto exp = ps.parse();
    ASSERT_EQ(test.getValue(), exp->getValue());
}

TEST(TestParseToken, singleString)
{
    llvm::StringRef st = R"("str")";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    StrLiteral test = StrLiteral("str");

    auto exp = ps.strParse();
    ASSERT_EQ(test.getValue(), exp.getValue());
}

TEST(TestParseToken, identifier)
{
    llvm::StringRef st = "foo";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Identifier test = Identifier("foo");

    auto exp = ps.identParse();
    ASSERT_EQ(test.getName(), exp.getName());
}

TEST(TestParseToken, parse_letState)
{
    llvm::StringRef st = "let foo = 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Identifier ident = Identifier("foo");
    IntLiteral* integer = new IntLiteral(1);
    LetStatement test = LetStatement(ident, integer);

    auto exp = ps.letParse();
    ASSERT_EQ(typeid(test), typeid(exp));
    ASSERT_EQ(test.getName(), exp.getName());
    ASSERT_EQ(test.getValue(), exp.getValue());
}

TEST(TestParseToken, peek_type)
{
    llvm::StringRef st = "let foo = 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    EXPECT_EQ(TokenType::IDENT, ps.getPeekType());
    ps.nextToken();
    EXPECT_EQ(TokenType::ASSIGN, ps.getPeekType());
    ps.nextToken();
    EXPECT_EQ(TokenType::INT, ps.getPeekType());
}

TEST(TestParseToken, no_equal_letState)
{
    llvm::StringRef st = "let = 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.letParse();
    EXPECT_EQ("", exp.getName());
}


TEST(TestParseToken, no_assign_letState)
{
    llvm::StringRef st = "let foo  1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.letParse();
    EXPECT_EQ("", exp.getName());
}

TEST(TestBinary_expression, PLUS_expression)
{
    llvm::StringRef st = "1 + 2";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    IntLiteral* one = new IntLiteral(1);
    IntLiteral* two = new IntLiteral(2);
    BinarlyExpression plus = BinarlyExpression(NodeType::NT_PLUS, one, two);

    auto exp = ps.plusParse();
    EXPECT_EQ(plus.getType(), exp->getType());
    auto expLHand = exp->getLHand();
    EXPECT_EQ(one->getValue(), expLHand->getValue());
    auto expRHand = exp->getRHand();
    EXPECT_EQ(two->getValue(), expRHand->getValue());
}

TEST(TestBinary_expression, PRODUCT_expression)
{
    llvm::StringRef st = "1 * 2";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    IntLiteral* one = new IntLiteral(1);
    IntLiteral* two = new IntLiteral(2);
    BinarlyExpression mul = BinarlyExpression(NodeType::NT_MUL, one, two);

    auto exp = ps.mulParse();
    EXPECT_EQ(mul.getType(), exp->getType());
    auto expLHand = exp->getLHand();
    EXPECT_EQ(one->getValue(), expLHand->getValue());
    auto expRHand = exp->getRHand();
    EXPECT_EQ(two->getValue(), expRHand->getValue());
}