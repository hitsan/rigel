#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "../include/rigel/CodeGen.h"
using namespace rigel;

CodeGenerator::CodeGenerator()
{

}

void CodeGenerator::codeGen(Expression* expr)
{
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module llvmModule("Module", context);

    std::string name = "main";
    llvm::FunctionType* retType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function* function = llvm::Function::Create(
                                                    retType, 
                                                    llvm::Function::ExternalLinkage,
                                                    name,
                                                    llvmModule);
    llvm::BasicBlock* block = llvm::BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(block);

    ((ReturnStatement*)expr)->codeGen(&builder);
    // ((BinaryExpression*)expr)->codeGen(&builder);

    std::error_code errorInfo;
    llvm::raw_fd_ostream os("./test_bin/test.bc", errorInfo);
    llvm::WriteBitcodeToFile(llvmModule, os);
}