#ifndef DECLARATOR_H
#define DECLARATOR_H
#include <map> 
#include "llvm/ADT/StringRef.h"
#include "Token/Token.h"

namespace rigel {

class Declarator
{
private:
    std::map<llvm::StringRef, TokenType> declaratorMap;
public:
    Declarator();
};

Declarator::Declarator()
{
    declaratorMap["let"] = TokenType::LET;
}

};

#endif