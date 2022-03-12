#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/Casting.h"
#include "../include/rigel/CodeGen.h"
using namespace rigel;

CodeGenerator::CodeGenerator()
{
    llvm::LLVMContext context;
    this->builder = new llvm::IRBuilder<>(context);
    this->llvmModule = new llvm::Module("Module", context);

    std::string name = "main";
    llvm::FunctionType* retType = llvm::FunctionType::get(builder->getInt32Ty(), false);
    llvm::Function* function = llvm::Function::Create(
                                                    retType, 
                                                    llvm::Function::ExternalLinkage,
                                                    name,
                                                    llvmModule);
    llvm::BasicBlock* block = llvm::BasicBlock::Create(context, "entry", function);
    builder->SetInsertPoint(block);
}

llvm::IRBuilder<>* CodeGenerator::getBuilder()
{
    return builder;
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
    llvm::Value* value = builder->getInt32(intValue);
    return value;
}