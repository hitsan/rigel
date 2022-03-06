#include <stdlib.h>
#include <gtest/gtest.h>
#include <sys/stat.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

// TEST(outputBitcode, outputBitcode)
// {
//     CodeGenerator* generator = new CodeGenerator();
//     generator->codeGen();

//     struct stat buffer;
//     int exist = stat("./test_bin/test.bc", &buffer);
//     ASSERT_EQ(0, exist);

//     // int result = system("lli test_bin/test.bc");
// }

TEST(returnInt, input_custom_value)
{
    // ast
    Expression* twoLiteral = new IntLiteral(2);
    ReturnStatement* returnState = new ReturnStatement(twoLiteral);
    CodeGenerator* generator = new CodeGenerator();

    // TODO
    // It is wrong to pass the expression to the generator.
    generator->codeGen(returnState);

    struct stat buffer;
    int exist = stat("./test_bin/test.bc", &buffer);
    ASSERT_EQ(0, exist);

    // 
    int result = std::system("lli test_bin/test.bc");
    result /= 256;
    ASSERT_EQ(2, result);
}

TEST(binaryExpression, plus_int_value)
{
    // ast
    Expression* one = new IntLiteral(1);
    Expression* two = new IntLiteral(2);
    BinaryExpression* binaryExpression = new BinaryExpression(OP_PLUS, one, two);

    CodeGenerator* generator = new CodeGenerator();
    generator->codeGen(binaryExpression);

    struct stat buffer;
    int exist = stat("./test_bin/test.bc", &buffer);
    ASSERT_EQ(0, exist);
}