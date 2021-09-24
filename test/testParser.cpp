#include <gtest/gtest.h>
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

TEST(expression, nextToken)
{
    Lexer lx("PopVirus");
    Parser ps(lx);
    auto tok = ps.nextToken();
    ASSERT_EQ(TokenType::STR, tok->getTokenType());
    ASSERT_EQ("PopVirus", tok->getLiteral());
}