#ifndef DECLARATOR_H
#define DECLARATOR_H
#include <map> 
#include "llvm/ADT/StringRef.h"
#include "./Token.h"

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

};

#endif