#ifndef AST_H
#define AST_H
#include <string>
#include "Token/Token.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/StringRef.h"
#include "CodeGen.h"
#define EXPR_PTR std::unique_ptr<Expression>
namespace rigel {

class CodeGenerator;

enum NodeType
{
    NT_BIN,
    NT_INT,
    NT_STR,
    NT_RET,
};

enum class StatementType
{
    RET,
};

enum OpType
{
    OP_PLUS,
    OP_MUL,
};

class Expression
{
protected:
    const NodeType type;
public:
    Expression(NodeType type) : type(type) {};
    NodeType getType() const;
    virtual llvm::Value* walk(CodeGenerator* generator) = 0;
};

class IntLiteral : public Expression
{
private:
    int value;
public:
    IntLiteral(int value) : Expression(NT_INT), value(value) {};
    int getValue();
    static bool classof(const Expression *expression) {
        return expression->getType() == NT_INT;
    }
    llvm::Value* walk(CodeGenerator* generator);
};

class StrLiteral : public Expression
{
private:
    std::string value;
public:
    StrLiteral(std::string value) : Expression(NT_STR), value(value) {};
    std::string getValue() { return this->value; };
    static bool classof(const Expression *expression) {
        return expression->getType() == NT_STR;
    }
    llvm::Value* walk(CodeGenerator* generator);
};

class Identifier
{
private:
    std::string name;
public:
    Identifier(std::string name) : name(name) {};
    std::string getName() { return this->name; };
};

class LetStatement
{
private:
    Identifier ident;
    Expression* expression;
public:
    LetStatement(Identifier ident, Expression* expression) : ident(ident), expression(expression) {};
    std::string getName() { return ident.getName(); };
    Expression* getExpression() { return expression; };
};

class BinaryExpression : public Expression
{
protected:
    OpType opType;
    Expression* lHand;
    Expression* rHand;
public:
    BinaryExpression(OpType opType, Expression* lHand, Expression* rHand) : Expression(NT_BIN), opType(opType), lHand(lHand), rHand(rHand) {};
    Expression* getLHand();
    Expression* getRHand();
    OpType getOpType();
    static bool classof(const Expression *expression);
    llvm::Value* walk(CodeGenerator* generator);
};

class Statement
{
protected:
    const StatementType type;
public:
    Statement(StatementType type) : type(type) {};
    // StatementType getType() const;
    virtual Expression* getExpression() = 0;
    // virtual void walk(CodeGenerator* generator);
};

class ReturnStatement : public Statement
{
protected:
    Expression* expression;
public:
    ReturnStatement(Expression* expression) : Statement(StatementType::RET), expression(expression) {};
    Expression* getExpression();
    // bool equals(Statement* state);
    // void walk(CodeGenerator* generator);
};

};

#endif