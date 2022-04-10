#include <stdlib.h>
#include <gtest/gtest.h>
#include <sys/stat.h>
#include "include/rigel/CodeGen.h"
#include "include/rigel/Ast.h"
#include "include/rigel/Lexer.h"
#include "include/rigel/Parser.h"
using namespace rigel;

const char bcPath[] = "test_bin/test.bc";
const char lli[] = "lli test_bin/test.bc";

class TestCodegenExpression : public ::testing::Test
{
protected:
    Expression* inum[10];

    llvm::LLVMContext context;
    llvm::Module *llvmModule = new llvm::Module("Module", context);
    CodeGenerator* generator = new CodeGenerator(llvmModule);

    struct stat buffer;
    int exist;

    virtual void SetUp()
    {
        for(int i = 0; i < 10; i++)
        {
            inum[i] = new IntLiteral(i);
        }
        exist = stat(bcPath, &buffer);
        if(!exist) unlink(bcPath);
    }

    void removeBC()
    {
        exist = stat(bcPath, &buffer);
        if(!exist) unlink(bcPath);
    }

};

TEST_F(TestCodegenExpression, return_int_value)
{
    Statement* returnState = new ReturnStatement(inum[8]);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(8, result);
}

TEST_F(TestCodegenExpression, return_plus_expression)
{
    Expression* binaryExpression = new BinaryExpression(OP_PLUS, inum[1], inum[2]);
    Statement* returnState = new ReturnStatement(binaryExpression);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(3, result);
}

TEST_F(TestCodegenExpression, return_mul_expression)
{
    Expression* binaryExpression = new BinaryExpression(OP_MUL, inum[3], inum[5]);
    Statement* returnState = new ReturnStatement(binaryExpression);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(15, result);
}

TEST_F(TestCodegenExpression, return_polynomial)
{
    Expression* mulExpression = new BinaryExpression(OP_MUL, inum[3], inum[5]);
    Expression* addExpression = new BinaryExpression(OP_PLUS, mulExpression, inum[2]);
    Statement* returnState = new ReturnStatement(addExpression);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(17, result);
}