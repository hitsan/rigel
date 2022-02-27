#ifndef CODEGEN_H
#define CODEGEN_H
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"
#include "Ast.h"

namespace rigel {

class CodeGenerator
{
public:
    CodeGenerator();
    void codeGen(ReturnStatement* retState);
};

};

#endif