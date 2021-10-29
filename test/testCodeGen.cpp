#include <gtest/gtest.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

TEST(TestCodeGen, IntGen)
{
    llvm::StringRef st = R"(1)";
    Lexer lx = Lexer(st);
    Parser ps = Parser(lx);

    auto exp = ps.parse();
    exp->codegen();
    Expression* expression = new IntLiteral(1);
    expression->codeGen();
}