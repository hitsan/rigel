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
class Statement;
class IntLiteral;

class CodeGenerator
{
private:
    llvm::IRBuilder<> builder;
    llvm::Module *llvmModule;
public:
    CodeGenerator(llvm::Module *llvmModule);
    void codeGen(Statement* statement);
    // llvm::Value* codeGen(Expression* expression);
    llvm::Value* codeGen(IntLiteral* intLiteral);
    llvm::IRBuilder<>* getBuilder();
    llvm::Value* createInteger(IntLiteral* IntLiteral);
    llvm::Value* createAdd(llvm::Value* lIntLiteral, llvm::Value* rIntLiteral);
    llvm::Value* createMul(llvm::Value* lIntLiteral, llvm::Value* rIntLiteral);
    void createReturn(llvm::Value* value);
};

};

#endif