#ifndef CODEGEN_H
#define CODEGEN_H
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "Ast.h"
#include "CodeGen.h"

namespace rigel {

class Expression;
class IntLiteral;

class CodeGenerator
{
private:
    llvm::IRBuilder<> builder;
    llvm::Module *llvmModule;
public:
    CodeGenerator(llvm::Module *llvmModule);
    void codeGen(Expression* expression);
    llvm::Value* codeGen(IntLiteral* intLiteral);
    llvm::IRBuilder<>* getBuilder();
    void createAdd(IntLiteral* lIntLiteral, IntLiteral* rIntLiteral);
    void createReturn(llvm::Value* value);
};

};

#endif