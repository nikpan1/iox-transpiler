#include "Core.cpp"
#include <any>
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
  Token(TokenType type, std::string lexeme, int line);
  Token(TokenType type, std::string lexeme, std::any literal, int line);

  friend std::ostream &operator<<(std::ostream &os, const Token &obj);
};
