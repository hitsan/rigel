#include <typeinfo>
#include <gtest/gtest.h>
#include "llvm/Support/Casting.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Parser.h"
#include "include/rigel/Ast.h"
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

    auto exp = ps.parse();
    ASSERT_EQ(1, exp->getValue());
}

TEST(TestParseToken, singleString)
{
    llvm::StringRef st = R"("str")";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.strParse();
    ASSERT_EQ("str", exp.getValue());
}

TEST(TestParseToken, identifier)
{
    llvm::StringRef st = "foo";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.identParse();
    ASSERT_EQ("foo", exp.getLiteral());
}

TEST(TestParseToken, parse_letState)
{
    llvm::StringRef st = "let foo = 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Identifier ident = Identifier("foo");
    Expression* expression = new IntLiteral(1);
    LetStatement* test = new LetStatement(ident, expression);

    LetStatement* letState = ps.letParse();

    ASSERT_EQ(typeid(test), typeid(letState));
    ASSERT_EQ("foo", letState->getName());

    Expression* ast = letState->getExpression();
    IntLiteral* literal = llvm::dyn_cast<IntLiteral>(ast);
    ASSERT_EQ(1, literal->getValue());
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
    EXPECT_EQ("", exp->getName());
}


TEST(TestParseToken, no_assign_letState)
{
    llvm::StringRef st = "let foo  1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.letParse();
    EXPECT_EQ("", exp->getName());
}

TEST(TestBinary_expression, PLUS_expression)
{
    llvm::StringRef st = "1 + 2";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Expression* expr = ps.expressionParse();
    BinaryExpression* exp = llvm::dyn_cast<BinaryExpression>(expr);
    EXPECT_EQ(OpType::OP_PLUS, exp->getOpType());

    Expression* expLHand = exp->getLHand();
    IntLiteral* lHand = llvm::dyn_cast<IntLiteral>(expLHand);
    EXPECT_EQ(1, lHand->getValue());

    Expression* expRHand = exp->getRHand();
    IntLiteral* rHand = llvm::dyn_cast<IntLiteral>(expRHand);
    EXPECT_EQ(2, rHand->getValue());
}

TEST(TestBinary_expression, PRODUCT_expression)
{
    llvm::StringRef st = "1 * 2";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Expression* expr = ps.expressionParse();
    BinaryExpression* exp = llvm::dyn_cast<BinaryExpression>(expr);
    EXPECT_EQ(OpType::OP_MUL, exp->getOpType());

    Expression* expLHand = exp->getLHand();
    IntLiteral* lHand = llvm::dyn_cast<IntLiteral>(expLHand);
    EXPECT_EQ(1, lHand->getValue());

    Expression* expRHand = exp->getRHand();
    IntLiteral* rHand = llvm::dyn_cast<IntLiteral>(expRHand);
    EXPECT_EQ(2, rHand->getValue());
}

TEST(TestBinary_expression, Polynomial)
{
    llvm::StringRef st = "11 + 22 * 33";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    Expression* expr = ps.expressionParse();
    BinaryExpression* exp = llvm::dyn_cast<BinaryExpression>(expr);
    EXPECT_EQ(OpType::OP_PLUS, exp->getOpType());

    Expression* expLHand = exp->getLHand();
    IntLiteral* lHand = llvm::dyn_cast<IntLiteral>(expLHand);
    EXPECT_EQ(11, lHand->getValue());

    Expression* expR = exp->getRHand();
    BinaryExpression* expRHand = llvm::dyn_cast<BinaryExpression>(expR);
    EXPECT_EQ(OpType::OP_MUL, expRHand->getOpType());

    Expression* expRLHand = expRHand->getLHand();
    IntLiteral* RLHand = llvm::dyn_cast<IntLiteral>(expRLHand);
    EXPECT_EQ(22, RLHand->getValue());

    Expression* expRRHand = expRHand->getRHand();
    IntLiteral* RRHand = llvm::dyn_cast<IntLiteral>(expRRHand);
    EXPECT_EQ(33, RRHand->getValue());
}

TEST(TestParseToken, parse_returnState)
{
    llvm::StringRef st = "return 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    ReturnStatement* returnState = ps.returnParse();

    Expression* expr = returnState->getExpression();
    IntLiteral* exp = llvm::dyn_cast<IntLiteral>(expr);

    ASSERT_EQ(1, exp->getValue());
}