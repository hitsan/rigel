#include "../include/rigel/Ast.h"
#include "llvm/IR/IRBuilder.h"

using namespace rigel;

Expression* ReturnStatement::getExpression()
{
    return this->expression;
}

NodeType Expression::getType() const
{
    return type;
}

void Expression::walk(llvm::IRBuilder<> *builder)
{
    auto type = this->getType();
    switch (type) {
        case NT_BIN:
            {
                BinaryExpression* binariyExpression = llvm::dyn_cast<BinaryExpression>(this);
                binariyExpression->walk(builder);
            }
            break;
        case NT_RET:
            {
                ReturnStatement* returnExpression = llvm::dyn_cast<ReturnStatement>(this);
                returnExpression->walk(builder);
            }
            break;
        default:
            break;
    }
}

bool BinaryExpression::classof(const Expression *expression) {
    return expression->getType() == NT_BIN;
}

void BinaryExpression::walk(llvm::IRBuilder<> *builder)
{
    IntLiteral* lIntLiteral = (IntLiteral*)lHand;
    IntLiteral* rIntLiteral = (IntLiteral*)rHand;
    int lIntValue = lIntLiteral->getValue();
    int rIntValue = rIntLiteral->getValue();
    llvm::Value* lValue = builder->getInt32(lIntValue);
    llvm::Value* rValue = builder->getInt32(rIntValue);

    builder->CreateAdd(lValue, rValue, "addtmp");
}

bool ReturnStatement::classof(const Expression *expression)
{
    return expression->getType() == NT_RET;
}

void ReturnStatement::walk(llvm::IRBuilder<> *builder)
{
    IntLiteral* retrunInt = (IntLiteral*)expression;
    int val = retrunInt->getValue();
    llvm::Value* retrunValue = builder->getInt32(val);

    builder->CreateRet(retrunValue);
}