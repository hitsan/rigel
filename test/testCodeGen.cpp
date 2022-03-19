#include <stdlib.h>
#include <gtest/gtest.h>
#include <sys/stat.h>
#include "../include/rigel/CodeGen.h"
#include "../include/rigel/Ast.h"
#include "../include/rigel/Lexer.h"
#include "../include/rigel/Parser.h"
using namespace rigel;

TEST(returnInt, input_custom_value)
{
    Expression* twoLiteral = new IntLiteral(8);
    Expression* returnState = new ReturnStatement(twoLiteral);
    
    llvm::LLVMContext context;
    llvm::Module *llvmModule = new llvm::Module("Module", context);
    CodeGenerator* generator = new CodeGenerator(llvmModule);

    struct stat buffer;
    int exist = stat("./test_bin/test.bc", &buffer);
    if(!exist) unlink("./test_bin/test.bc");

    generator->codeGen(returnState);

    exist = stat("./test_bin/test.bc", &buffer);
    ASSERT_EQ(0, exist);

    int result = std::system("lli test_bin/test.bc");
    result /= 256;
    ASSERT_EQ(8, result);
}

TEST(binaryExpression, plus_int_value)
{
    Expression* one = new IntLiteral(1);
    Expression* two = new IntLiteral(2);
    BinaryExpression* binaryExpression = new BinaryExpression(OP_PLUS, one, two);

    llvm::LLVMContext context;
    llvm::Module *llvmModule = new llvm::Module("Module", context);
    CodeGenerator* generator = new CodeGenerator(llvmModule);

    struct stat buffer;
    int exist = stat("./test_bin/test.bc", &buffer);
    if(!exist) unlink("./test_bin/test.bc");

    generator->codeGen(binaryExpression);

    exist = stat("./test_bin/test.bc", &buffer);
    ASSERT_EQ(0, exist);
}