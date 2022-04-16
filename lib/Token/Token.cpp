#include "include/rigel/Token/Token.h"
using namespace rigel;

Token::Token(TokenType type, llvm::StringRef literal) : type(type), literal(literal) {};
bool Token::isType(TokenType type)
{
    return (type == this->type) ? true : false;
}
std::string Token::getLiteral() { return literal.str(); }