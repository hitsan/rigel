#ifndef TOKEN_H
#define TOKEN_H 
#include <string>
#include "llvm/ADT/StringRef.h"
#define TOKEN_PTR std::unique_ptr<Token>

namespace rigel {

enum TokenType
{
    EOI,
    ILLEGAL,
    IDENT,
    NEWLINE,
    INT,
    STR,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    BOOL,
    BANG,
    ASSIGN,
    LET,
    RETURN
};

enum NumType
{
    NUM_INT
};

enum OpType
{
    OP_PLUS,
    OP_MINUS,
    OP_MUL,
    OP_SLASH,
    OP_BANG
};

class Token
{
private:
    TokenType type;
    llvm::StringRef literal;
public:
    Token(TokenType type, llvm::StringRef literal) : type(type), literal(literal) {};
    TokenType getTokenType() { return type; }
    std::string getLiteral() { return literal.str(); }
};

class Number : public Token
{
private:
    NumType type;
    int num;
public:
    Number(NumType type, int num) : Token(TokenType::INT, "0"), type(type), num(num) {};
    NumType getTokenType() { return type; }
    int getLiteral() { return num; }
};

class Operator : public Token
{
private:
    OpType type;
public:
    Operator(OpType type) : Token(TokenType::INT, "0"), type(type) {};
    OpType getTokenType() { return type; }
};

class Identifier : public Token
{
private:
    std::string literal;
public:
    Identifier(llvm::StringRef literal) : Token(TokenType::INT, "0"), literal(literal) {};
    std::string getLiteral() { return literal; }
};

};

#endif