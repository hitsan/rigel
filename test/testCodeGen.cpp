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
    Expression* expr = new IntLiteral(1);
    ReturnStatement* retState = new ReturnStatement(expr);

    CodeGenerator* generator = new CodeGenerator();
    generator->codeGen(retState);

    struct stat buffer;
    int exist = stat("./test_bin/test.bc", &buffer);
    ASSERT_EQ(0, exist);
}