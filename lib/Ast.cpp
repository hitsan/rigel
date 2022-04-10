#include <iostream>
#include "../include/rigel/Ast.h"
#include "llvm/IR/IRBuilder.h"

using namespace rigel;

NodeType Expression::getType() const
{
    return type;
}

llvm::Value* Expression::walk(CodeGenerator* generator) {}

Expression* BinaryExpression::getLHand() { return lHand; };
Expression* BinaryExpression::getRHand() { return rHand; };
OpType BinaryExpression::getOpType() { return opType; };

int IntLiteral::getValue() { return this->value; };

llvm::Value* IntLiteral::walk(CodeGenerator* generator)
{
    return generator->createInteger(this);
}

bool BinaryExpression::classof(const Expression *expression) {
    return expression->getType() == NT_BIN;
}

llvm::Value* BinaryExpression::walk(CodeGenerator* generator)
{
    IntLiteral* lIntLiteral = (IntLiteral*)lHand;
    IntLiteral* rIntLiteral = (IntLiteral*)rHand;
    return generator->createAdd(lIntLiteral, rIntLiteral);
}

Expression* ReturnStatement::getExpression()
{
    return expression;
}