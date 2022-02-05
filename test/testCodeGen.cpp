#include <stdlib.h>
#include <gtest/gtest.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

// TEST(TestCodeGen, IntGen)
// {
//     // test return 1
//     Identifier ident("a");
//     Expression* integer = new IntLiteral(1);
//     auto let = new LetStatement(ident, integer);
 
//     auto ret = codegen(let);
//     auto inst = ret.getInstructions();

//     std::string expection = R"(ret i32 1)";
// }

TEST(TestCodeGen, NomalExitStatus)
{
    const char bin[] = "/rigel/test/bin/a.out";
    int status = system(bin);
    ASSERT_EQ(status, 0);
}