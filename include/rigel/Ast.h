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

enum class NodeType
{
    PLUS,
    MUL,
    INT,
    STR,
    RET,
};

enum class StatementType
{
    RET,
    ILLEGAL,
};

class Expression
{
protected:
    const NodeType type;
public:
    Expression(NodeType type) : type(type) {};
    NodeType getType() const;
    virtual llvm::Value* walk(CodeGenerator* generator) = 0;
    // for test
    virtual bool testParse(std::vector<std::tuple<NodeType, int>> test) = 0;
};

class IntLiteral : public Expression
{
private:
    int value;
public:
    IntLiteral(int value) : Expression(NodeType::INT), value(value) {};
    int getValue();
    static bool classof(const Expression *expression) {
        return expression->getType() == NodeType::INT;
    }
    llvm::Value* walk(CodeGenerator* generator);
    bool testParse(std::vector<std::tuple<NodeType, int>> test);
};

class StrLiteral : public Expression
{
private:
    std::string value;
public:
    StrLiteral(std::string value) : Expression(NodeType::STR), value(value) {};
    std::string getValue() { return this->value; };
    static bool classof(const Expression *expression) {
        return expression->getType() == NodeType::STR;
    }
    llvm::Value* walk(CodeGenerator* generator);
    bool testParse(std::vector<std::tuple<NodeType, int>> test);
};

class BinaryExpression : public Expression
{
protected:
    std::unique_ptr<Expression> lHand;
    std::unique_ptr<Expression> rHand;
public:
    BinaryExpression(NodeType type, std::unique_ptr<Expression> lHand, std::unique_ptr<Expression> rHand) : Expression(type), lHand(std::move(lHand)), rHand(std::move(rHand)) {};
    std::unique_ptr<Expression> getLHand();
    std::unique_ptr<Expression> getRHand();
    static bool classof(const Expression *expression);
    llvm::Value* walk(CodeGenerator* generator);
    bool testParse(std::vector<std::tuple<NodeType, int>> test);
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

class Statement
{
protected:
    const StatementType type;
public:
    Statement(StatementType type) : type(type) {};
    StatementType getType() const;
    virtual std::unique_ptr<Expression> getExpression() = 0;
    // virtual void walk(CodeGenerator* generator);
};

class ReturnStatement : public Statement
{
protected:
    std::unique_ptr<Expression> expression;
public:
    ReturnStatement(std::unique_ptr<Expression> expression) : Statement(StatementType::RET), expression(std::move(expression)) {};
    std::unique_ptr<Expression> getExpression();
    // bool equals(Statement* state);
    // void walk(CodeGenerator* generator);
};

};

#endif