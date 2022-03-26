#include <iostream>
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

void Expression::walk(CodeGenerator* generator)
{
    this->walk(generator);
}

Expression* BinaryExpression::getLHand() { return lHand; };
Expression* BinaryExpression::getRHand() { return rHand; };
OpType BinaryExpression::getOpType() { return opType; };

int IntLiteral::getValue() { return this->value; };
void IntLiteral::walk(CodeGenerator* generator)
{
    // llvm::IRBuilder<>* builder = generator->getBuilder();
}

bool BinaryExpression::classof(const Expression *expression) {
    return expression->getType() == NT_BIN;
}

void BinaryExpression::walk(CodeGenerator* generator)
{
    IntLiteral* lIntLiteral = (IntLiteral*)lHand;
    IntLiteral* rIntLiteral = (IntLiteral*)rHand;
    generator->createAdd(lIntLiteral, rIntLiteral);
}

bool ReturnStatement::classof(const Expression *expression)
{
    return expression->getType() == NT_RET;
}

void ReturnStatement::walk(CodeGenerator* generator)
{
    Expression* expression = this->getExpression();
    IntLiteral* intLiteral = llvm::dyn_cast<IntLiteral>(expression);
    llvm::Value* value = generator->codeGen(intLiteral);
    generator->createReturn(value);
}