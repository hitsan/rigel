#include "../include/rigel/Ast.h"
#include "llvm/IR/IRBuilder.h"

using namespace rigel;

Expression* ReturnStatement::getExpression()
{
    return this->expression;
}

bool ReturnStatement::classof(const Expression *expr)
{
    return expr->getType() == NT_RET;
}

void ReturnStatement::codeGen(llvm::IRBuilder<> *builder)
{
    IntLiteral* retrunInt = (IntLiteral*)expression;
    int val = retrunInt->getValue();
    llvm::Value* retrunValue = builder->getInt32(val);

    builder->CreateRet(retrunValue);
}