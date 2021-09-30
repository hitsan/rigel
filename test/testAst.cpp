#include <gtest/gtest.h>
#include "../include/rigel/Token/Token.h"
#include "../include/rigel/Ast.h"
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
using namespace rigel;

// TEST(makeAST, integerLiteral)
// {
//     llvm::StringRef st = "1";
//     IntegerLiteral il(st.str());

//     ASSERT_EQ(1, il.getLiteral());
// }