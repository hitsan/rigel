#include <gtest/gtest.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

TEST(TestCodeGen, IntGen)
{
    llvm::StringRef st = "let a = 1";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.parse();
    exp->codegen();

    std::string expection = R"(%1 = alloca i32, align 4
                               store i32 1, i32* %1, align 4)";
}