#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
#include "../include/rigel/Ast.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

class TestGetToken : public ::testing::Test
{
protected:
    llvm::StringRef st = "1 + 2 * 3 / 4 PopVirus !";
    Lexer lx = Lexer(st);
    Parser* ps;

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
    Token test[] = {
    Token(TokenType::INT, "1"),
    Token(TokenType::PLUS, "+"),
    Token(TokenType::INT, "2"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "3"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::INT, "4"),
    Token(TokenType::STR, "PopVirus"),
    Token(TokenType::BANG, "!")
    };

    int testLength = LENGTH(test);
    TOKEN_PTR tok;
    for(int i = 0; i < testLength; i++)
    {
        tok = ps->getCurToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

TEST_F(TestGetToken, getPeekToken)
{
    Token test[] = {
    // Token(TokenType::INT, "1"),
    Token(TokenType::PLUS, "+"),
    Token(TokenType::INT, "2"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "3"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::INT, "4"),
    Token(TokenType::STR, "PopVirus"),
    Token(TokenType::BANG, "!"),
    Token(TokenType::EOI, ""),
    };

    int testLength = LENGTH(test);
    TOKEN_PTR tok;
    for(int i = 0; i < testLength; i++)
    {
        tok = ps->getPeekToken();
        ASSERT_EQ(test[i].getLiteral(), tok->getLiteral());
        ASSERT_EQ(test[i].getTokenType(), tok->getTokenType());
        ps->nextToken();
    }
}

/*
TEST(parseAST, integerLiteral)
{
    llvm::StringRef st = "1";
    Lexer lx(st);
    Parser ps(lx);

    Ast ast = ps.parse();
    ASSERT_EQ("1", ast.getLiteral());
}

class TestParse : public ::testing::Test
{
protected:
    Ast* plus;
    IntegerLiteral* op1;
    IntegerLiteral* op2;

    virtual void SetUp()
    {
        plus = new InfixExpression(TokenType::PLUS);
        op1 = new IntegerLiteral("1");
        op2 = new IntegerLiteral("2");

        plus->setLHand(op1);
        plus->setRHand(op2);
    }

    virtual void TearDown()
    {
        delete plus;
        delete op1;
        delete op2;
    }
};


// void equalsAst(InfixExpression* test, InfixExpression* input)
// {
//     if(test == nullptr && input == nullptr)
//         return;

//     ASSERT_EQ(test.getLiteral(), input.getLiteral());

//     equalsAst(test->getLHand(), input->getLHand());
//     equalsAst(test->getRHand(), input->getRHand());
// }

void equalsAst(InfixExpression* test, InfixExpression* input)
{
    ASSERT_EQ(test.getLiteral(), input.getLiteral());

    equalsAst(test->getLHand(), input->getLHand());
    equalsAst(test->getRHand(), input->getRHand());
}

TEST_F(TestParse, infixExpression)
{
    llvm::StringRef st = "1 + 2";
    Lexer lx(st);
    Parser ps(lx);

    Ast input = ps.parse();
    ASSERT_EQ(plus->getLiteral(), inputgetLiteral());
    auto lHand = plus->getLHand();
    auto lInput = input->getLHand();
    ASSERT_EQ(lHand.getLiteral(), lInput.getLiteral());
    auto rHand = plus->getRHand();
    auto rInput = input->getRHand();
    ASSERT_EQ(rHand.getLiteral(), rInput.getLiteral());
}
*/