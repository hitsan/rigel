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
    removeBC();
}

TEST_F(TestCodegenExpression, return_plus_expression)
{
    Expression* binaryExpression = new BinaryExpression(OP_PLUS, inum[1], inum[2]);
    Statement* returnState = new ReturnStatement(binaryExpression);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(3, result);
    removeBC();
}

TEST_F(TestCodegenExpression, return_mul_expression)
{
    Expression* binaryExpression = new BinaryExpression(OP_MUL, inum[3], inum[5]);
    Statement* returnState = new ReturnStatement(binaryExpression);
    generator->codeGen(returnState);

    int result = std::system(lli);
    result /= 256;
    ASSERT_EQ(15, result);
    removeBC();
}

TEST_F(TestCodegenExpression, return_polynomial)
{
    Expression* expression[4];
    Statement* returnState;
    int result = 0; 

    // // 3 * 5 + 2
    // expression[0] = new BinaryExpression(OP_MUL, inum[3], inum[5]);
    // expression[1] = new BinaryExpression(OP_PLUS, expression[0], inum[2]);
    // returnState = new ReturnStatement(expression[1]);
    // generator->codeGen(returnState);

    // result = std::system(lli);
    // result /= 256;
    // ASSERT_EQ(17, result);
    // removeBC();

    // // 3 + 5 + 2
    // expression[0] = new BinaryExpression(OP_PLUS, inum[3], inum[5]);
    // expression[1] = new BinaryExpression(OP_PLUS, expression[0], inum[2]);
    // returnState = new ReturnStatement(expression[1]);
    // generator->codeGen(returnState);

    // result = std::system(lli);
    // result /= 256;
    // ASSERT_EQ(10, result);
    // removeBC();

    // // (3 + 5) * 2
    // expression[0] = new BinaryExpression(OP_PLUS, inum[3], inum[5]);
    // expression[1] = new BinaryExpression(OP_MUL, expression[0], inum[2]);
    // returnState = new ReturnStatement(expression[1]);
    // generator->codeGen(returnState);

    // result = std::system(lli);
    // result /= 256;
    // ASSERT_EQ(30, result);
    // removeBC();

    // (3 + 5) * (2 + 8) 
    expression[0] = new BinaryExpression(OP_PLUS, inum[3], inum[5]);
    expression[1] = new BinaryExpression(OP_PLUS, inum[2], inum[8]);
    expression[2] = new BinaryExpression(OP_MUL, expression[0], expression[1]);
    returnState = new ReturnStatement(expression[2]);
    generator->codeGen(returnState);

    result = std::system(lli);
    result /= 256;
    ASSERT_EQ(80, result);
    removeBC();
}