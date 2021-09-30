#ifndef AST_H
#define AST_H
#include <string>
#include "Token/Token.h"
#include "llvm/ADT/StringRef.h"
namespace rigel {

class Ast
{
protected:
    TOKEN_PTR token;
    Ast* lHand;
    Ast* rHand;
public:
    TokenType getType() { return token->getTokenType(); };
    llvm::StringRef getLiteral() { return token->getLiteral(); };
    virtual void setLHand(Ast* lHand) = 0;
    virtual void setRHand(Ast* rHand) = 0;
    virtual Ast* getLHand(void) = 0;
    virtual Ast* getRHand(void) = 0;
};

class IntegerLiteral : public Ast
{
protected:
    int value;
public:
    IntegerLiteral(llvm::StringRef value) { this->value = std::stoi(value.str()); };
};

class InfixExpression : public Ast
{
protected:
    TokenType oprator;
    // Ast* lHand;
    // Ast* rHand;
public:
    InfixExpression(TokenType oprator) { this->oprator = oprator; };
    void setLHand(Ast* lHand) override { this->lHand = lHand; };
    void setRHand(Ast* rHand) override { this->rHand = rHand; };
    Ast* getLHand(void) override { return lHand; };
    Ast* getRHand(void) override { return rHand; };
};

};

#endif