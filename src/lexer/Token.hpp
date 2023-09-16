#include "Core.cpp"
#include <iostream>
#include <sstream>
#include <string>

#define Object std::string

class Token {

  TokenType type;
  std::string lexeme;
  Object literal;
  int line;

public:
  Token(TokenType tp, std::string le, Object lit, int lin);

  friend std::ostream &operator<<(std::ostream &os, const Token &obj);
};
