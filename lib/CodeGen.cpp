#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "../include/rigel/CodeGen.h"
using namespace rigel;

CodeGenerator::CodeGenerator()
{

}

void CodeGenerator::codeGen(ReturnStatement* retState)
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

    Expression* expr = retState->getExpression();
    IntLiteral* getValue = (IntLiteral*)expr;
    int val = getValue->getValue();
    
    llvm::Value* ret = builder.getInt32(val);
    builder.CreateRet(ret);

    std::error_code error_info;
    llvm::raw_fd_ostream os("./test_bin/test.bc", error_info);
    llvm::WriteBitcodeToFile(llvmModule, os);
}