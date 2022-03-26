#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/Casting.h"
#include "../include/rigel/CodeGen.h"
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

void CodeGenerator::codeGen(Expression* expression)
{
    expression->walk(this);

    std::error_code errorInfo;
    llvm::raw_fd_ostream os("./test_bin/test.bc", errorInfo);
    llvm::WriteBitcodeToFile(*llvmModule, os);
}

llvm::Value* CodeGenerator::codeGen(IntLiteral* intLiteral)
{
    int intValue = intLiteral->getValue();
    llvm::Value* value = builder.getInt32(intValue);
    return value;
}

void CodeGenerator::createAdd(IntLiteral* lIntLiteral, IntLiteral* rIntLiteral)
{
    int lIntValue = lIntLiteral->getValue();
    int rIntValue = rIntLiteral->getValue();
    llvm::Value* lValue = builder.getInt32(lIntValue);
    llvm::Value* rValue = builder.getInt32(rIntValue);

    builder.CreateAdd(lValue, rValue, "addtmp");
}

void CodeGenerator::createReturn(llvm::Value* value)
{
    builder.CreateRet(value);
}