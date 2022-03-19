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
    auto type = this->getType();
    switch (type) {
        case NT_BIN:
            {
                BinaryExpression* binariyExpression = llvm::dyn_cast<BinaryExpression>(this);
                binariyExpression->walk(generator);
            }
            break;
        case NT_RET:
            {
                ReturnStatement* returnExpression = llvm::dyn_cast<ReturnStatement>(this);
                returnExpression->walk(generator);
            }
            break;
        default:
            break;
    }
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
    // llvm::IRBuilder<>* builder =  generator->getBuilder();

    IntLiteral* lIntLiteral = (IntLiteral*)lHand;
    IntLiteral* rIntLiteral = (IntLiteral*)rHand;
    generator->createAdd(lIntLiteral, rIntLiteral);

    // int lIntValue = lIntLiteral->getValue();
    // int rIntValue = rIntLiteral->getValue();
    // llvm::Value* lValue = builder->getInt32(lIntValue);
    // llvm::Value* rValue = builder->getInt32(rIntValue);

    // builder->CreateAdd(lValue, rValue, "addtmp");
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