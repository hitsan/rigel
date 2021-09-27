#include <gtest/gtest.h>
#include "../include/rigel/Token.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
#include "../include/rigel/Ast.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

TEST(makeAST, integerLiteral)
{
    llvm::StringRef st = "1";
    Lexer lx(st);
    Parser ps(lx);

    IntegerLiteral ast = ps.parse();
    ASSERT_EQ(1, ast.getLiteral());
}