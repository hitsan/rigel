#include "include/rigel/Token/Token.h"
using namespace rigel;

Token::Token(TokenType type, llvm::StringRef literal) : type(type), literal(literal) {};
bool Token::equalsTokenType(TokenType type)
{
    return (type == this->type) ? true : false;
}
TokenType Token::getTokenType()
{
    return this->type;
}
std::string Token::getLiteral() { return literal.str(); }