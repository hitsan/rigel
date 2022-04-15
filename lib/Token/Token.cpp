#include "include/rigel/Token/Token.h"
using namespace rigel;

Token::Token(TokenType type, llvm::StringRef literal) : type(type), literal(literal) {};
TokenType Token::getTokenType() { return type; }
std::string Token::getLiteral() { return literal.str(); }