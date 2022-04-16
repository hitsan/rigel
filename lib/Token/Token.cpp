#include "include/rigel/Token/Token.h"
using namespace rigel;

Token::Token(TokenType type, llvm::StringRef literal) : type(type), literal(literal) {};
bool Token::isTokenType(TokenType type)
{
    return (type == this->type) ? true : false;
}
std::string Token::getLiteral() { return literal.str(); }