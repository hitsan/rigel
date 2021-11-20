#include <gtest/gtest.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

TEST(TestCodeGen, IntGen)
{
    // test return 1
    Identifier ident("a");
    Expression* integer = new IntLiteral(1);
    auto let = new LetStatement(ident, integer);
 
    auto ret = codegen(let);
    auto block = ret.getBlock();

    std::string expection = R"(ret i32 1)";
}