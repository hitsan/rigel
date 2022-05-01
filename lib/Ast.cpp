#include <iostream>
#include "include/rigel/Ast.h"
#include "llvm/IR/IRBuilder.h"

using namespace rigel;

NodeType Expression::getType() const
{
    return type;
}

// llvm::Value* Expression::walk(CodeGenerator* generator) {}

Expression* BinaryExpression::getLHand() { return lHand; };
Expression* BinaryExpression::getRHand() { return rHand; };

int IntLiteral::getValue() { return this->value; };

llvm::Value* IntLiteral::walk(CodeGenerator* generator)
{
    return generator->createInteger(this);
}

bool BinaryExpression::classof(const Expression *expression) {
    return (expression->getType() == NodeType::PLUS ||
            expression->getType() == NodeType::MUL);
}

llvm::Value* StrLiteral::walk(CodeGenerator* generator) {};

llvm::Value* BinaryExpression::walk(CodeGenerator* generator)
{
    llvm::Value * lIntLiteral = lHand->walk(generator);
    llvm::Value * rIntLiteral = rHand->walk(generator);
    llvm::Value* expressionValue;
    const NodeType type = getType();
    switch (type)
    {
    case NodeType::PLUS:
        expressionValue = generator->createAdd(lIntLiteral, rIntLiteral);
        break;
    case NodeType::MUL:
        expressionValue = generator->createMul(lIntLiteral, rIntLiteral);
        break;
    default:
        expressionValue = NULL;
        break;
    }
    return expressionValue;
}

Expression* ReturnStatement::getExpression()
{
    return expression;
}

// bool ReturnStatement::equals(Statement* state);