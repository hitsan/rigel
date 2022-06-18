#include <typeinfo>
#include <gtest/gtest.h>
#include "llvm/Support/Casting.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Parser.h"
#include "include/rigel/Ast.h"
using namespace rigel;

void checkExpression(std::unique_ptr<Expression> expression, )
{

}

TEST(ParseReturnState, single_integer)
{
    llvm::StringRef code = "return 4";
    Lexer lexer = Lexer(code);
    Parser parser = Parser(lexer);
    std::unique_ptr<Statement> state = parser.parse();
    ASSERT_EQ(StatementType::RET, state->getType());

    std::unique_ptr<Expression> expression = state->getExpression();
    ASSERT_EQ(NodeType::INT, expression->getType());
    IntLiteral* exp = llvm::dyn_cast<IntLiteral>(expression);
    ASSERT_EQ(4, exp->getValue());
}

TEST(TestBinary_expression, plus_expression)
{
    llvm::StringRef st = "return 1 + 2";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    std::unique_ptr<Statement> state = parser.parse();

    std::unique_ptr<Expression> expression = state->getExpression();
    ASSERT_EQ(NodeType::PLUS, expression->getType());

    BinaryExpression* binExpr = llvm::dyn_cast<BinaryExpression>(expression);

    std::unique_ptr<Expression> expLHand = binExpr->getLHand();
    ASSERT_EQ(NodeType::INT, expLHand->getType());
    IntLiteral* lInt = llvm::dyn_cast<IntLiteral>(expLHand);
    ASSERT_EQ(1, lInt->getValue());

    std::unique_ptr<Expression> expRHand = binExpr->getRHand();
    ASSERT_EQ(NodeType::INT, expLHand->getType());
    IntLiteral* rInt = llvm::dyn_cast<IntLiteral>(expRHand);
    ASSERT_EQ(2, rInt->getValue());
}

TEST(TestBinary_expression, mul_expression)
{
    llvm::StringRef st = "return 4 * 5";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    std::unique_ptr<Statement> state = parser.parse();

    std::unique_ptr<Expression> expression = state->getExpression();
    ASSERT_EQ(NodeType::MUL, expression->getType());

    BinaryExpression* binExpr = llvm::dyn_cast<BinaryExpression>(expression);

    std::unique_ptr<Expression> expLHand = binExpr->getLHand();
    ASSERT_EQ(NodeType::INT, expLHand->getType());
    IntLiteral* lInt = llvm::dyn_cast<IntLiteral>(expLHand);
    ASSERT_EQ(4, lInt->getValue());

    std::unique_ptr<Expression> expRHand = binExpr->getRHand();
    ASSERT_EQ(NodeType::INT, expLHand->getType());
    IntLiteral* rInt = llvm::dyn_cast<IntLiteral>(expRHand);
    ASSERT_EQ(5, rInt->getValue());
}

TEST(TestBinary_expression, plus_mul_expression)
{
    llvm::StringRef st = "return 7 + 4 * 5";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    std::unique_ptr<Statement> state = parser.parse();

    std::unique_ptr<Expression> plusExpression = state->getExpression();
    ASSERT_EQ(NodeType::PLUS, plusExpression->getType());

    BinaryExpression* plusBinExpression = llvm::dyn_cast<BinaryExpression>(plusExpression);
    std::unique_ptr<Expression> plusLHand = plusBinExpression->getLHand();
    ASSERT_EQ(NodeType::INT, plusLHand->getType());
    IntLiteral* plusLInt = llvm::dyn_cast<IntLiteral>(plusLHand);
    ASSERT_EQ(7, plusLInt->getValue());

    std::unique_ptr<Expression> plusRHand = plusBinExpression->getRHand();
    BinaryExpression* mulExpression = llvm::dyn_cast<BinaryExpression>(plusRHand);
    ASSERT_EQ(NodeType::MUL, mulExpression->getType());

    std::unique_ptr<Expression> mulLHand = mulExpression->getLHand();
    ASSERT_EQ(NodeType::INT, mulLHand->getType());
    IntLiteral* mulLInt = llvm::dyn_cast<IntLiteral>(mulLHand);
    ASSERT_EQ(4, mulLInt->getValue());

    std::unique_ptr<Expression> mulRHand = mulExpression->getRHand();
    ASSERT_EQ(NodeType::INT, mulRHand->getType());
    IntLiteral* mulRInt = llvm::dyn_cast<IntLiteral>(mulRHand);
    ASSERT_EQ(5, mulRInt->getValue());
}

TEST(TestBinary_expression, mul_plus_expression)
{
    llvm::StringRef st = "return 9 * 2 + 6";
    Lexer lexer = Lexer(st);
    Parser parser = Parser(lexer);
    std::unique_ptr<Statement> state = parser.parse();

    std::unique_ptr<Expression> plusExpression = state->getExpression();
    ASSERT_EQ(NodeType::PLUS, plusExpression->getType());

    BinaryExpression* plusBinExpression = llvm::dyn_cast<BinaryExpression>(plusExpression);
    std::unique_ptr<Expression> plusBinRExpression = plusBinExpression->getRHand();
    ASSERT_EQ(NodeType::INT, plusBinRExpression->getType());
    IntLiteral* plusRInt = llvm::dyn_cast<IntLiteral>(plusBinRExpression);
    ASSERT_EQ(6, plusRInt->getValue());

    std::unique_ptr<Expression> plusBinLExpression = plusBinExpression->getLHand();
    BinaryExpression* mulBinExpression = llvm::dyn_cast<BinaryExpression>(plusBinLExpression);
    ASSERT_EQ(NodeType::MUL, mulBinExpression->getType());

    std::unique_ptr<Expression> mulLHand = mulBinExpression->getLHand();
    ASSERT_EQ(NodeType::INT, mulLHand->getType());
    IntLiteral* mulLInt = llvm::dyn_cast<IntLiteral>(mulLHand);
    ASSERT_EQ(9, mulLInt->getValue());

    std::unique_ptr<Expression> mulRHand = mulBinExpression->getRHand();
    ASSERT_EQ(NodeType::INT, mulRHand->getType());
    IntLiteral* mulRInt = llvm::dyn_cast<IntLiteral>(mulRHand);
    ASSERT_EQ(2, mulRInt->getValue());
}

// TEST(ParseIlligalReturnState, only_operator)
// {
//     llvm::StringRef code = "return +";
//     Lexer lexer = Lexer(code);
//     Parser parser = Parser(lexer);
//     Statement* state = parser.parse();
//     ASSERT_EQ(StatementType::ILLEGAL, state->getType());
// }

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