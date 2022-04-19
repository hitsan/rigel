#ifndef DECLARATOR_H
#define DECLARATOR_H
#include <map> 
#include "llvm/ADT/StringRef.h"
#include "Token.h"

namespace rigel {

static std::map<llvm::StringRef, TokenType> declaratorMap
{
    { "let", TokenType::LET },
    { "return", TokenType::RETURN }
};

static TokenType findTokenType(llvm::StringRef key)
{
    if(declaratorMap.find(key) == declaratorMap.end()) {
        return TokenType::IDENT;
    }
    return declaratorMap[key];
}

static std::map<llvm::StringRef, TokenType> operatorMap
{
    { "+", TokenType::PLUS },
    { "-", TokenType::MINUS },
    { "*", TokenType::ASTERISK },
    { "/", TokenType::SLASH },
    { "!", TokenType::BANG },
    { "=", TokenType::ASSIGN },
    { "\n", TokenType::NEWLINE }
};

static TokenType findOperatorType(llvm::StringRef key)
{
    if(operatorMap.find(key) == operatorMap.end()) {
        return TokenType::ILLEGAL;
    }
    return operatorMap[key];
}

};

#endif