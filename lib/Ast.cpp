#include <iostream>
#include "include/rigel/Ast.h"
#include "llvm/IR/IRBuilder.h"

using namespace rigel;

NodeType Expression::getType() const
{
    return type;
}

std::unique_ptr<Expression> BinaryExpression::getLHand() { return std::move(lHand); };
std::unique_ptr<Expression> BinaryExpression::getRHand() { return std::move(rHand); };

int IntLiteral::getValue() { return this->value; };

llvm::Value* IntLiteral::walk(CodeGenerator* generator)
{
    return generator->createInteger(this);
}

bool IntLiteral::testParse(std::vector<std::tuple<NodeType, int>> test)
{
    std::tuple<NodeType, int> aaa = test.front();
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

StatementType Statement::getType() const
{
    return this->type;
}

std::unique_ptr<Expression> ReturnStatement::getExpression()
{
    return std::move(this->expression);
}

// bool ReturnStatement::equals(Statement* state);