#include <typeinfo>
#include <gtest/gtest.h>
#include "llvm/Support/Casting.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Parser.h"
#include "include/rigel/Ast.h"
using namespace rigel;

// TEST(TestParseToken, singleIntNum)
// {
//     llvm::StringRef st = R"(1)";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     auto exp = parser.parseInt();
//     ASSERT_EQ(1, exp->getValue());
// }

// TEST(TestParseToken, singleString)
// {
//     llvm::StringRef st = R"("str")";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     auto exp = parser.parseStr();
//     ASSERT_EQ("str", exp.getValue());
// }

// TEST(TestParseToken, identifier)
// {
//     llvm::StringRef st = "foo";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     auto exp = parser.parseIdentifier();
//     ASSERT_EQ("foo", exp.getName());
// }

// TEST(TestParseToken, no_equal_letState)
// {
//     llvm::StringRef st = "let = 1";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     auto exp = parser.parseLet();
//     EXPECT_EQ("", exp->getName());
// }


// TEST(TestParseToken, no_assign_letState)
// {
//     llvm::StringRef st = "let foo  1";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     auto exp = parser.parseLet();
//     EXPECT_EQ("", exp->getName());
// }

// TEST(TestBinary_expression, mul_expression)
// {
//     llvm::StringRef st = "1 * 2";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     Expression* expr = parser.parseExpression();
//     BinaryExpression* exp = llvm::dyn_cast<BinaryExpression>(expr);
//     EXPECT_EQ(OpType::OP_MUL, exp->getOpType());

//     Expression* expLHand = exp->getLHand();
//     IntLiteral* lHand = llvm::dyn_cast<IntLiteral>(expLHand);
//     EXPECT_EQ(1, lHand->getValue());

//     Expression* expRHand = exp->getRHand();
//     IntLiteral* rHand = llvm::dyn_cast<IntLiteral>(expRHand);
//     EXPECT_EQ(2, rHand->getValue());
// }

// TEST(TestBinary_expression, polynomial)
// {
//     llvm::StringRef st = "11 + 22 * 33";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     Expression* expr = parser.parseExpression();
//     BinaryExpression* exp = llvm::dyn_cast<BinaryExpression>(expr);
//     EXPECT_EQ(OpType::OP_PLUS, exp->getOpType());

//     Expression* expLHand = exp->getLHand();
//     IntLiteral* lHand = llvm::dyn_cast<IntLiteral>(expLHand);
//     EXPECT_EQ(11, lHand->getValue());

//     Expression* expR = exp->getRHand();
//     BinaryExpression* expRHand = llvm::dyn_cast<BinaryExpression>(expR);
//     EXPECT_EQ(OpType::OP_MUL, expRHand->getOpType());

//     Expression* expRLHand = expRHand->getLHand();
//     IntLiteral* RLHand = llvm::dyn_cast<IntLiteral>(expRLHand);
//     EXPECT_EQ(22, RLHand->getValue());

//     Expression* expRRHand = expRHand->getRHand();
//     IntLiteral* RRHand = llvm::dyn_cast<IntLiteral>(expRRHand);
//     EXPECT_EQ(33, RRHand->getValue());
// }


// TEST(TestParseToken, parse_returnState)
// {
//     llvm::StringRef st = "return 1";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     ReturnStatement* returnState = parser.parseReturn();

//     Expression* expr = returnState->getExpression();
//     IntLiteral* exp = llvm::dyn_cast<IntLiteral>(expr);

//     ASSERT_EQ(1, exp->getValue());
// }

TEST(ParseReturnState, single_integer)
{
    // Test data
    // return 1
    Expression* one = new IntLiteral(1);
    Statement* ret = new ReturnStatement(one);

    llvm::StringRef code = "return 4";
    Lexer lexer = Lexer(code);
    Parser parser = Parser(lexer);
    Statement* state = parser.parse();
    ASSERT_EQ(typeid(state), typeid(ret));

    Expression* expression = state->getExpression();
    ASSERT_EQ(NodeType::NT_INT, expression->getType());
    IntLiteral* exp = llvm::dyn_cast<IntLiteral>(expression);
    ASSERT_EQ(4, exp->getValue());
}

TEST(TestBinary_expression, plus_expression)
{
    llvm::StringRef st = "return 1 + 2";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    Statement* state = parser.parse();

    Expression* expression = state->getExpression();
    ASSERT_EQ(NodeType::OP_PLUS, expression->getType());

    BinaryExpression* binExpr = llvm::dyn_cast<BinaryExpression>(expression);

    Expression* expLHand = binExpr->getLHand();
    ASSERT_EQ(NodeType::NT_INT, expLHand->getType());
    IntLiteral* lInt = llvm::dyn_cast<IntLiteral>(expLHand);
    ASSERT_EQ(1, lInt->getValue());

    Expression* expRHand = binExpr->getRHand();
    ASSERT_EQ(NodeType::NT_INT, expLHand->getType());
    IntLiteral* rInt = llvm::dyn_cast<IntLiteral>(expRHand);
    ASSERT_EQ(2, rInt->getValue());
}

TEST(TestBinary_expression, mul_expression)
{
    llvm::StringRef st = "return 4 * 5";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    Statement* state = parser.parse();

    Expression* expression = state->getExpression();
    ASSERT_EQ(NodeType::OP_MUL, expression->getType());

    BinaryExpression* binExpr = llvm::dyn_cast<BinaryExpression>(expression);

    Expression* expLHand = binExpr->getLHand();
    ASSERT_EQ(NodeType::NT_INT, expLHand->getType());
    IntLiteral* lInt = llvm::dyn_cast<IntLiteral>(expLHand);
    ASSERT_EQ(4, lInt->getValue());

    Expression* expRHand = binExpr->getRHand();
    ASSERT_EQ(NodeType::NT_INT, expLHand->getType());
    IntLiteral* rInt = llvm::dyn_cast<IntLiteral>(expRHand);
    ASSERT_EQ(5, rInt->getValue());
}

TEST(TestBinary_expression, plus_mul_expression)
{
    llvm::StringRef st = "return 7 + 4 * 5";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    Statement* state = parser.parse();

    Expression* plusExpression = state->getExpression();
    ASSERT_EQ(NodeType::OP_PLUS, plusExpression->getType());

    BinaryExpression* plusBinExpression = llvm::dyn_cast<BinaryExpression>(plusExpression);
    Expression* plusLHand = plusBinExpression->getLHand();
    ASSERT_EQ(NodeType::NT_INT, plusLHand->getType());
    IntLiteral* plusLInt = llvm::dyn_cast<IntLiteral>(plusLHand);
    ASSERT_EQ(7, plusLInt->getValue());

    Expression* plusRHand = plusBinExpression->getRHand();
    BinaryExpression* mulExpression = llvm::dyn_cast<BinaryExpression>(plusRHand);
    ASSERT_EQ(NodeType::OP_MUL, mulExpression->getType());

    Expression* mulLHand = mulExpression->getLHand();
    ASSERT_EQ(NodeType::NT_INT, mulLHand->getType());
    IntLiteral* mulLInt = llvm::dyn_cast<IntLiteral>(mulLHand);
    ASSERT_EQ(4, mulLInt->getValue());

    Expression* mulRHand = mulExpression->getRHand();
    ASSERT_EQ(NodeType::NT_INT, mulRHand->getType());
    IntLiteral* mulRInt = llvm::dyn_cast<IntLiteral>(mulRHand);
    ASSERT_EQ(5, mulRInt->getValue());
}

// TEST(TestParseToken, parse_letState)
// {
//     llvm::StringRef st = "let foo = 1";
//     Lexer lexer = Lexer(st);
//     Parser parser = Parser(lexer);

//     Identifier ident = Identifier("foo");
//     Expression* expression = new IntLiteral(1);
//     LetStatement* test = new LetStatement(ident, expression);

//     LetStatement* letState = parser.parseLet();

//     ASSERT_EQ(typeid(test), typeid(letState));
//     ASSERT_EQ("foo", letState->getName());

//     Expression* ast = letState->getExpression();
//     IntLiteral* literal = llvm::dyn_cast<IntLiteral>(ast);
//     ASSERT_EQ(1, literal->getValue());
// }