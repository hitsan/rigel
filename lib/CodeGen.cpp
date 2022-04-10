#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/Casting.h"
#include "include/rigel/CodeGen.h"
using namespace rigel;

CodeGenerator::CodeGenerator(llvm::Module *llvmModule) : llvmModule(llvmModule), builder(llvmModule->getContext())
{
    const std::string name = "main";
    llvm::FunctionType* retType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function* function = llvm::Function::Create(
                                                    retType, 
                                                    llvm::Function::ExternalLinkage,
                                                    name,
                                                    llvmModule);
    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmModule->getContext(), "entry", function);
    builder.SetInsertPoint(block);
}

llvm::IRBuilder<>* CodeGenerator::getBuilder()
{
    return &builder;
}

llvm::Value* CodeGenerator::codeGen(IntLiteral* intLiteral)
{
    int intValue = intLiteral->getValue();
    llvm::Value* value = builder.getInt32(intValue);
    return value;
}

llvm::Value* CodeGenerator::createInteger(IntLiteral* IntLiteral)
{
    int integer = IntLiteral->getValue();
    llvm::Value* intValue = builder.getInt32(integer);
    return intValue;
}

llvm::Value* CodeGenerator::createAdd(llvm::Value* lIntLiteral, llvm::Value* rIntLiteral)
{
    return builder.CreateAdd(lIntLiteral, rIntLiteral, "addtmp");
}

llvm::Value* CodeGenerator::createMul(llvm::Value* lIntLiteral, llvm::Value* rIntLiteral)
{
    return builder.CreateMul(lIntLiteral, rIntLiteral, "addtmp");
}

void CodeGenerator::createReturn(llvm::Value* value)
{
    builder.CreateRet(value);
}

void CodeGenerator::codeGen(Statement* statement)
{
    Expression* expression = statement->getExpression();
    llvm::Value* value = expression->walk(this);
    createReturn(value);

    std::error_code errorInfo;
    llvm::raw_fd_ostream os("./test_bin/test.bc", errorInfo);
    llvm::WriteBitcodeToFile(*llvmModule, os);
}