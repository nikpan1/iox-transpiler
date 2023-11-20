#include "Core.cpp"
#include <any>
#include <iostream>
#include <sstream>
#include <string>

class Token {

  TokenType type;
  std::string lexeme;
  std::string literal;
  int line;

public:
  Token(TokenType type, std::string lexeme, int line);
  // I used to use std::any for the literal, but for simplicity I will stick
  // with string
  Token(TokenType type, std::string lexeme, std::string literal, int line);

  friend std::ostream &operator<<(std::ostream &os, const Token &obj);
};
