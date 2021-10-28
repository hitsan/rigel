#include <gtest/gtest.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
using namespace rigel;

TEST(TestCodeGen, IntGen)
{
    Expression* expression = new IntLiteral(1);
    expression->codeGen();
}